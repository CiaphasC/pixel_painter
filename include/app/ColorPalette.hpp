#pragma once

#include <cstdint>

namespace app {

enum class ColorId : std::uint8_t {
    Background,
    Outline,
    Body
};

struct RgbColor {
    int r;
    int g;
    int b;
};

const RgbColor& color_for(ColorId id) noexcept;

} // namespace app
