# Droid Pixel Painter

Proyecto en C++17 que utiliza la libreria MiniWin para renderizar, pixel a pixel, un sprite del logo de Android. El flujo completo pasa por transformar un patron textual en memoria, asignar colores predefinidos y dibujar cada celda sobre una ventana nativa de Windows.

## Contenidos

1. [Resumen rapido](#resumen-rapido)
2. [Arquitectura y flujo](#arquitectura-y-flujo)
3. [Definicion del patron](#definicion-del-patron)
4. [Requisitos](#requisitos)
5. [Compilacion y ejecucion](#compilacion-y-ejecucion)
6. [Estructura del repositorio](#estructura-del-repositorio)
7. [Personalizacion](#personalizacion)
8. [Solucion de problemas](#solucion-de-problemas)
9. [Licencia y creditos](#licencia-y-creditos)

## Resumen rapido

- **Lenguaje**: C++17
- **Framework de ventana**: MiniWin (incluido en `vendor/miniwin/`)
- **Salida**: Ventana GDI con sprite cuadriculado, cuadrilla opcional y salida por teclado (ESC para cerrar)
- **Automatizacion**: `scripts/run.ps1` prepara build, compila y puede ejecutar

## Arquitectura y flujo

```
+---------------------------+
|  Patron textual (B,G,W)   |
+-----------+---------------+
            | decode()
            v
+---------------------------+
|  Buffer contiguo ColorId  |
|  (std::unique_ptr[])      |
+-----------+---------------+
            | PixelGrid::draw()
            v
+---------------------------+
|  MiniWin (color_rgb,      |
|  rectangulo_lleno, etc.)  |
+-----------+---------------+
            | ventana GDI
            v
+---------------------------+
|  Usuario: ESC para salir  |
+---------------------------+
```

Componentes principales:

- `AndroidPattern.cpp`: convierten cadenas semanticas en IDs de color. Comentarios por bloque indican cabeza, ojos, boca, base.
- `PixelGrid.cpp`: itera el buffer, consulta la paleta y dibuja cuadrados; tambien pinta lineas de la cuadrilla.
- `ColorPalette.cpp`: mapa de `ColorId` -> `RgbColor` con tonos blanco, negro y verde.
- `main.cpp`: define tamanos `cellSize`, `margin`, prepara ventana MiniWin y mantiene un bucle de 60 FPS.

## Definicion del patron

Cada fila de `kPattern` usa caracteres:

| Token | Significado | Color predeterminado |
|-------|-------------|----------------------|
| `B`   | Contorno / detalle negro | `(0,0,0)`
| `G`   | Cuerpo del androide      | `(173,255,47)`
| `W`   | Fondo                    | `(255,255,255)`

El patron es de `kHeight = 18` filas por `kWidth = 16` columnas. Si agregas filas o modificas el ancho, recuerda mantener estas constantes sincronizadas para evitar asserts durante la construccion del grid.

## Requisitos

- Windows + SDK para que MiniWin pueda invocar GDI.
- Compilador con soporte C++17 (MSVC recomendado).
- CMake 3.16 o superior.
- PowerShell 5.0+ si quieres usar el script de ayuda.

## Compilacion y ejecucion

### Ruta recomendada (PowerShell)

```
# Compila en Release
pwsh -ExecutionPolicy Bypass -File scripts/run.ps1

# Compila y lanza el ejecutable
pwsh -ExecutionPolicy Bypass -File scripts/run.ps1 -Run

# Cambia configuracion o limpia
pwsh -ExecutionPolicy Bypass -File scripts/run.ps1 -Configuration Debug
pwsh -ExecutionPolicy Bypass -File scripts/run.ps1 -Reconfigure
```

El ejecutable queda en `build/Release/droid_pixel_painter.exe` (o `build/Debug/...` segun la configuracion).

### Ruta manual con CMake

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
build/Release/droid_pixel_painter.exe
```

## Estructura del repositorio

```
?? CMakeLists.txt
?? CMakePresets.json
?? scripts/
?   ?? run.ps1
?? include/
?   ?? app/
?       ?? AndroidPattern.hpp
?       ?? ColorPalette.hpp
?       ?? PixelGrid.hpp
?? src/
?   ?? main.cpp
?   ?? app/
?       ?? AndroidPattern.cpp
?       ?? ColorPalette.cpp
?       ?? PixelGrid.cpp
?? vendor/
?   ?? miniwin/
?? build/          # Artefactos generados (ignorado por git)
?? scripts/bin/    # (opcional) salida de run.ps1
```

## Personalizacion

- **Sprite**: edita `src/app/AndroidPattern.cpp` respetando la matriz 16x18. Usa comentarios de seccion para ubicar cabeza, ojos, boca y base.
- **Escala y margenes**: modifica `cellSize` y `margin` en `src/main.cpp`.
- **Paleta**: actualiza `kPalette` en `src/app/ColorPalette.cpp` para nuevos colores.
- **Cuadricula**: ajusta `lineWidth` en `PixelGrid::drawGridLines` o llama a `grid.drawGridLines(..., lineWidth = 0)` para ocultar la malla.

## Solucion de problemas

| Sintoma | Causa comun | Solucion |
|---------|-------------|----------|
| `cmake` no reconocido | CMake no instalado o PATH sin actualizar | `winget install Kitware.CMake` o agregalo manualmente a PATH |
| Warnings C4244 (int -> float) | Conversion de coord a float | El codigo ya castea explicitamente; si aparecen, revisa cambios propios |
| Ventana sin sprite | Patron invalido (caracter distinto de B/G/W) | El `decode` lanza `std::runtime_error`; revisa la consola |
| Texto ilegible en README | Guardar en UTF-8/ASCII | Este repositorio usa ASCII plano para evitar problemas |

## Licencia y creditos

- MiniWin (Pau Fernandez) bajo licencia MIT, incluido dentro de `vendor/miniwin/`.
- Codigo restante del proyecto se publica tambien bajo licencia MIT.
- Basado en el sprite clasico del logo de Android representado como pixel art.

