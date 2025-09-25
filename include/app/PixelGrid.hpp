#pragma once

#include "app/ColorPalette.hpp"

#include <cstddef>
#include <memory>

namespace app {

class PixelGrid {
public:
    PixelGrid(std::size_t width, std::size_t height, std::unique_ptr<ColorId[]> cells) noexcept;

    std::size_t width() const noexcept { return m_width; }
    std::size_t height() const noexcept { return m_height; }
    const ColorId* data() const noexcept { return m_cells.get(); }

    void draw(int originX, int originY, int cellSize) const;
    void drawGridLines(int originX, int originY, int cellSize, int lineWidth = 1) const;

private:
    std::size_t m_width;
    std::size_t m_height;
    std::unique_ptr<ColorId[]> m_cells;
};

}  // namespace app
