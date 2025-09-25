#include "app/ColorPalette.hpp"

#include <array>
#include <cstddef>

namespace app {

namespace {

// Paleta de colores para el robot Android
// Los valores RGB van de 0 a 255
constexpr std::array<RgbColor, 3> kPalette{{
    {255, 255, 255}, // Blanco para el fondo
    {0, 0, 0},       // Negro para contornos y ojos
    {173, 255, 47}   // Verde lima para el cuerpo del robot
}};

}  // namespace

const RgbColor& color_for(ColorId id) noexcept {
    // Convertimos el ID de color en un índice para acceder a la paleta
    const auto index = static_cast<std::size_t>(id);
    return kPalette.at(index);
}

}  // namespace app
