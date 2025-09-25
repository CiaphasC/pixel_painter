#include "app/AndroidPattern.hpp"
#include "app/PixelGrid.hpp"

#include "miniwin.h"

int main() {
    using namespace miniwin;

    constexpr int cellSize = 24;
    constexpr int margin = 30;

    auto grid = app::make_android_pattern();
    const int canvasWidth = static_cast<int>(grid.width()) * cellSize + margin * 2;
    const int canvasHeight = static_cast<int>(grid.height()) * cellSize + margin * 2;

    vredimensiona(canvasWidth, canvasHeight);

    bool running = true;
    while (running) {
        borra();

        // Repintamos el fondo en blanco cada cuadro para evitar ghosting.
        const auto& bg = app::color_for(app::ColorId::Background);
        color_rgb(bg.r, bg.g, bg.b);
        rectangulo_lleno(0, 0, canvasWidth, canvasHeight);

        grid.draw(margin, margin, cellSize);
        grid.drawGridLines(margin, margin, cellSize);

        refresca();

        switch (tecla()) {
            case ESCAPE:
                running = false;
                break;
            default:
                break;
        }

        espera(16); // ~60 FPS, suficiente para animaciones futuras.
    }

    vcierra();
    return 0;
}
