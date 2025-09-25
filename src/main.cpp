 #include "app/AndroidPattern.hpp"
#include "app/PixelGrid.hpp"

#include "miniwin.h"

int main() {
    using namespace miniwin;

    // Tamaño de cada celda del patrón en píxeles
    constexpr int cellSize = 24;
    // Margen alrededor del patrón para que no se vea pegado a los bordes
    constexpr int margin = 30;

    // Cargamos el patrón del robot Android
    auto grid = app::make_android_pattern();
    
    // Calculamos el tamaño total de la ventana basado en el patrón
    const int canvasWidth = static_cast<int>(grid.width()) * cellSize + margin * 2;
    const int canvasHeight = static_cast<int>(grid.height()) * cellSize + margin * 2;

    vredimensiona(canvasWidth, canvasHeight);

    bool running = true;
    while (running) {
        borra();

        // Limpiamos la pantalla con el color de fondo
        const auto& bg = app::color_for(app::ColorId::Background);
        color_rgb(bg.r, bg.g, bg.b);
        rectangulo_lleno(0, 0, canvasWidth, canvasHeight);

        // Dibujamos el patrón y las líneas de la cuadrícula
        grid.draw(margin, margin, cellSize);
        grid.drawGridLines(margin, margin, cellSize);

        refresca();

        // Manejo básico de teclas
        switch (tecla()) {
            case ESCAPE:
                running = false;
                break;
            default:
                break;
        }

        // Mantenemos ~60 FPS
        espera(16);
    }

    vcierra();
    return 0;
}
