#include "app/AndroidPattern.hpp"

#include <array>
#include <cstddef>
#include <stdexcept>

namespace app {

namespace {

constexpr std::size_t kWidth = 16;
constexpr std::size_t kHeight = 18;

constexpr std::array<const char*, kHeight> kPattern = {
    "WWWWWWWWWWWWWWWW",  // 1 - Fondo
    "WWWWGGWWWWGGWWWW",  // 2 - Antenas superiores (L invertida)
    "WWWBGGBWWWBGGBWW",  // 3 - Antenas con base negra
    "WWBBBGGGGGGGBBBW",  // 4 - Cabeza superior con contorno
    "WBBGGGGGGGGGGGBBW", // 5 - Cabeza
    "WBBGGGGGGGGGGGBBW", // 6 - Cabeza
    "WBBGGGBBGGGGBGGBBW", // 7 - Cabeza con ojos negros
    "WBBGGGBBGGGGBGGBBW", // 8 - Cabeza con ojos negros
    "WBBGGGGGGGGGGGBBW", // 9 - Cabeza inferior
    "WBBBBBBBBBBBBBBBW", // 10 - Separación negra
    "WBBBBBBBBBBBBBBBW", // 11 - Separación negra
    "WBBGGGGGGGGGGGBBW", // 12 - Cuerpo superior
    "WBBGGGGGGGGGGGBBW", // 13 - Cuerpo
    "WBBBGGGGGGGGGBBBW", // 14 - Cuerpo inferior
    "WBBGBWWBWWBWWBGBBW", // 15 - Boca con 5 dientes blancos
    "WBBGBWWBWWBWWBGBBW", // 16 - Boca con 5 dientes blancos
    "WBBGBBBBBBBBBGBBW", // 17 - Base con contorno
    "WBBBBBBBBBBBBBBBW"  // 18 - Base negra
};

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

    // Convertimos el patron textual en un buffer contiguo apto para renderizar.
    for (const auto row : kPattern) {
        for (std::size_t col = 0; col < kWidth; ++col) {
            *cursor++ = decode(row[col]);
        }
    }

    return PixelGrid{kWidth, kHeight, std::move(cells)};
}

}  // namespace app
