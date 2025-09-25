#include "app/AndroidPattern.hpp"

#include <array>
#include <cstddef>
#include <stdexcept>

namespace app {

namespace {

constexpr std::size_t kWidth = 17;
constexpr std::size_t kHeight = 19;

constexpr std::array<const char*, kHeight> kPattern = {
    "WWWWWWWWWWWWWWWWW",  // 1 - Fondo
    "WWWWGGWWWWWGGWWWW",  // 2 - Antenas superiores (L invertida)
    "WWWBGGBWWWBGGBWWW",  // 3 - Antenas con base negra
    "WWBBBGGGGGGGBBBWW",  // 4 - Cabeza superior con contorno
    "WBBGGGGGGGGGGGBBW",  // 5 - Cabeza
    "WBBGGGGGGGGGGGBBW",  // 6 - Cabeza
    "WBBGGGBBGGGGBGGBBW", // 7 - Cabeza con ojos negros
    "WBBGGGBBGGGGBGGBBW", // 8 - Cabeza con ojos negros
    "WBBGGGGGGGGGGGBBW",  // 9 - Cabeza inferior
    "WBBBBBBBBBBBBBBBW",  // 10 - Separación negra
    "WBBBBBBBBBBBBBBBW",  // 11 - Separación negra
    "WBBGGGGGGGGGGGBBW",  // 12 - Cuerpo superior
    "WBBGGGGGGGGGGGBBW",  // 13 - Cuerpo
    "WBBBGGGGGGGGGBBBW",  // 14 - Cuerpo inferior
    "WBBGBWWBWWBWWBGBBW", // 15 - Boca con 5 dientes blancos
    "WBBGBWWBWWBWWBGBBW", // 16 - Boca con 5 dientes blancos
    "WBBGBWWBWWBWWBGBBW", // 17 - Boca con 5 dientes blancos
    "WBBGBBBBBBBBBGBBW",  // 18 - Base con contorno
    "WBBBBBBBBBBBBBBBW"   // 19 - Base negra
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
