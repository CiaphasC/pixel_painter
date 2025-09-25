#include "app/AndroidPattern.hpp"

#include <array>
#include <cstddef>
#include <memory>
#include <stdexcept>

namespace app {

namespace {

constexpr std::size_t kWidth = 16;
constexpr std::size_t kHeight = 18;

constexpr std::array<const char*, kHeight> kPattern = {
    // Marco superior y antenas (filas 1-4)
    "BBWWWWWWWWWWWWBB", // 1: borde exterior superior
    "BGBWWWWWWWWWWBGB", // 2: antenas y remates
    "WBGBWBBBBBBWBGBW", // 3: union antenas-casco
    "WWBGBBGGGGBBGBWW", // 4: frente curvado

    // Craneo y ojos (filas 5-9)
    "WWBBGGGGGGGGBBWW", // 5: parte alta de la cabeza
    "WBBGGGGGGGGGGBBW", // 6: domo central
    "WBGGGBGGGGBGGGBW", // 7: ojos (celdas negras)
    "BBGGGGGGGGGGGGBB", // 8: pomulos
    "BGGGGGGGGGGGGGGB", // 9: mejillas y contorno

    // Franja divisoria y torso (filas 10-12)
    "BBBBBBBBBBBBBBBB", // 10: franja negra horizontal
    "BGGGGGGGGGGGGGGB", // 11: pecho superior
    "BGGGGGGGGGGGGGGB", // 12: pecho inferior

    // Boca y mandibula (filas 13-16)
    "BGGBBBBBBBBBBGGB", // 13: borde superior de la boca
    "BBBBWWBWWBWWBBBB", // 14: dientes (fila 1)
    "WBBWWWBWWBWWWBBW", // 15: dientes (fila 2)
    "WWBWWWWWWWWWWBWW", // 16: base interior blanca

    // Base y sombra inferior (filas 17-18)
    "WWBBWWWWWWWWBBWW", // 17: contorno inferior
    "WWWBBBBBBBBBBWWW"  // 18: sombra final
};

static_assert(kPattern.size() == kHeight, "El patron debe declarar kHeight filas");

inline ColorId decode(char token) {
    switch (token) {
        case 'B': return ColorId::Outline;
        case 'G': return ColorId::Body;
        case 'W': return ColorId::Background;
        default: throw std::runtime_error("Token de patron desconocido");
    }
}

}  // namespace

PixelGrid make_android_pattern() {
    auto cells = std::make_unique<ColorId[]>(kWidth * kHeight);
    ColorId* cursor = cells.get();

    for (const auto row : kPattern) {
        for (std::size_t col = 0; col < kWidth; ++col) {
            *cursor++ = decode(row[col]);
        }
    }

    return PixelGrid{kWidth, kHeight, std::move(cells)};
}

}  // namespace app
