#include "app/PixelGrid.hpp"

#include "miniwin.h"

#include <utility>

namespace app {

PixelGrid::PixelGrid(std::size_t width, std::size_t height, std::unique_ptr<ColorId[]> cells) noexcept
    : m_width(width), m_height(height), m_cells(std::move(cells)) {}

void PixelGrid::draw(int originX, int originY, int cellSize) const {
    using namespace miniwin;

    // Recorremos cada celda del patrón y la dibujamos como un rectángulo
    const ColorId* cursor = m_cells.get();
    for (std::size_t row = 0; row < m_height; ++row) {
        const int top = originY + static_cast<int>(row) * cellSize;
        const int bottom = top + cellSize;

        for (std::size_t col = 0; col < m_width; ++col) {
            const int left = originX + static_cast<int>(col) * cellSize;
            const int right = left + cellSize;

            // Obtenemos el color de la paleta y lo aplicamos
            const auto& rgb = color_for(*cursor++);
            color_rgb(rgb.r, rgb.g, rgb.b);
            
            // Dibujamos el rectángulo de la celda
            rectangulo_lleno(
                static_cast<float>(left),
                static_cast<float>(top),
                static_cast<float>(right),
                static_cast<float>(bottom));
        }
    }
}

void PixelGrid::drawGridLines(int originX, int originY, int cellSize, int lineWidth) const {
    using namespace miniwin;

    // Configuramos el color negro para las líneas de la cuadrícula
    color(NEGRO);
    const int fullWidth = static_cast<int>(m_width) * cellSize;
    const int fullHeight = static_cast<int>(m_height) * cellSize;

    // Dibujamos las líneas verticales de la cuadrícula
    for (std::size_t col = 0; col <= m_width; ++col) {
        const int x = originX + static_cast<int>(col) * cellSize;
        rectangulo_lleno(
            static_cast<float>(x),
            static_cast<float>(originY),
            static_cast<float>(x + lineWidth),
            static_cast<float>(originY + fullHeight));
    }

    // Dibujamos las líneas horizontales de la cuadrícula
    for (std::size_t row = 0; row <= m_height; ++row) {
        const int y = originY + static_cast<int>(row) * cellSize;
        rectangulo_lleno(
            static_cast<float>(originX),
            static_cast<float>(y),
            static_cast<float>(originX + fullWidth),
            static_cast<float>(y + lineWidth));
    }
}

}  // namespace app
