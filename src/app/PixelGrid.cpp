#include "app/PixelGrid.hpp"

#include "miniwin.h"

namespace app {

PixelGrid::PixelGrid(std::size_t width, std::size_t height, std::unique_ptr<ColorId[]> cells) noexcept
    : m_width(width), m_height(height), m_cells(std::move(cells)) {}

void PixelGrid::draw(int originX, int originY, int cellSize) const {
    using namespace miniwin;

    // Recorremos el buffer con un puntero crudo para minimizar saltos de memoria.
    const ColorId* cursor = m_cells.get();
    for (std::size_t row = 0; row < m_height; ++row) {
        const int top = originY + static_cast<int>(row) * cellSize;
        const int bottom = top + cellSize;
        for (std::size_t col = 0; col < m_width; ++col, ++cursor) {
            const int left = originX + static_cast<int>(col) * cellSize;
            const int right = left + cellSize;
            const auto& rgb = color_for(*cursor);
            color_rgb(rgb.r, rgb.g, rgb.b);
            rectangulo_lleno(left, top, right, bottom);
        }
    }
}

void PixelGrid::drawGridLines(int originX, int originY, int cellSize, int lineWidth) const {
    using namespace miniwin;

    // Dibujamos las lineas de la cuadricula en un segundo paso para no mezclar colores.
    color(NEGRO);
    const int fullWidth = static_cast<int>(m_width) * cellSize;
    const int fullHeight = static_cast<int>(m_height) * cellSize;

    for (std::size_t col = 0; col <= m_width; ++col) {
        const int x = originX + static_cast<int>(col) * cellSize;
        rectangulo_lleno(x, originY, x + lineWidth, originY + fullHeight);
    }
    for (std::size_t row = 0; row <= m_height; ++row) {
        const int y = originY + static_cast<int>(row) * cellSize;
        rectangulo_lleno(originX, y, originX + fullWidth, y + lineWidth);
    }
}

}  // namespace app
