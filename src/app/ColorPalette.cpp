#include "app/ColorPalette.hpp"

#include <array>
#include <cstddef>

namespace app {

namespace {

// Paleta unica para toda la aplicacion. Valores en formato RGB de 0 a 255.
constexpr std::array<RgbColor, 3> kPalette{{
    {245, 245, 245}, // Fondo claro para evitar el brillo puro del blanco.
    {24, 24, 24},    // Contorno: negro profundo.
    {164, 255, 0}    // Verde caracteristico del personaje.
}};

}  // namespace

const RgbColor& color_for(ColorId id) noexcept {
    const auto index = static_cast<std::size_t>(id);
    return kPalette.at(index);
}

}  // namespace app
