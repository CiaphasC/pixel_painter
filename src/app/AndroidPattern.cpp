#include "app/AndroidPattern.hpp"

#include <array>
#include <cstddef>
#include <stdexcept>

namespace app {

namespace {

constexpr std::size_t kWidth = 16;
constexpr std::size_t kHeight = 18;

constexpr std::array kPattern = {
    "BBWWWWWWWWWWWWBB",
    "BGBWWWWWWWWWWBGB",
    "WBGBWBBBBBBWBGBW",
    "WWBGBBGGGGBBGBWW",
    "WWBBGGGGGGGGBBWW",
    "WBBGGGGGGGGGGBBW",
    "WBGGGBGGGGBGGGBW",
    "BBGGGGGGGGGGGGBB",
    "BGGGGGGGGGGGGGGB",
    "BBBBBBBBBBBBBBBB",
    "BGGGGGGGGGGGGGGB",
    "BGGGGGGGGGGGGGGB",
    "BGGBBBBBBBBBBGGB",
    "BBBBWWBWWBWWBBBB",
    "WBBWWWBWWBWWWBBW",
    "WWBWWWWWWWWWWBWW",
    "WWBBWWWWWWWWBBWW",
    "WWWBBBBBBBBBBWWW",
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
