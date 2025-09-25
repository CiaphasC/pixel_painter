#include "app/ColorPalette.hpp"

#include <array>
#include <cstddef>

namespace app {

namespace {

// Paleta unica para toda la aplicacion. Valores en formato RGB de 0 a 255.
constexpr std::array<RgbColor, 3> kPalette{{
    {255, 255, 255}, // Fondo blanco puro como en la imagen.
    {0, 0, 0},       // Contorno: negro puro para los ojos y contornos.
    {173, 255, 47}   // Verde lima brillante del Android (LimeGreen).
}};

}  // namespace

const RgbColor& color_for(ColorId id) noexcept {
    const auto index = static_cast<std::size_t>(id);
    return kPalette.at(index);
}

}  // namespace app
