# Droid Pixel Painter

Proyecto de referencia que renderiza un sprite del logo de Android empleando MiniWin.
Incluye una cuadricula estatica definida mediante un buffer dinamico sin perdidas de memoria.

## Requisitos

- Compilador C++17 (MSVC, MinGW-w64 o Clang).
- CMake >= 3.16 para la instalacion principal.
- Windows SDK (MiniWin se apoya en GDI).

## Compilacion con CMake (recomendada para VSCode)

```bash
cmake -S . -B build
cmake --build build --config Release
```

Si usas la extension *CMake Tools* de VSCode basta con abrir la carpeta y seleccionar el kit.
El ejecutable `droid_pixel_painter` quedara disponible en `build/`.

## Ejecucion rapida desde PowerShell

1. Instala CMake 3.16+ si aun no lo tienes (por ejemplo: `winget install Kitware.CMake`).
2. Abre una terminal en la carpeta del repositorio.
3. Ejecuta el script de ayuda:

```powershell
pwsh -ExecutionPolicy Bypass -File scripts/run.ps1 -Run
```

El script comprueba la presencia de CMake, configura la carpeta `build/` si es necesario y compila el proyecto. Con `-Run` lanza el ejecutable al terminar. Puedes anadir `-Configuration Debug` para una build de depuracion o `-Reconfigure` para regenerar la carpeta `build/` desde cero.

## Configuracion manual en Code::Blocks

1. Crea un proyecto "Console application" vacio.
2. Anade los siguientes archivos existentes al proyecto:
   - `src/main.cpp`
   - `src/app/AndroidPattern.cpp`
   - `src/app/ColorPalette.cpp`
   - `src/app/PixelGrid.cpp`
   - `vendor/miniwin/miniwin.cpp`
3. Configura las rutas de cabecera en *Project -> Build options -> Search directories -> Compiler*:
   - `include`
   - `vendor/miniwin`
4. En la pestana *Linker* anade las librerias del sistema: `gdi32` y `user32`.
5. Compila y ejecuta. El programa abre la ventana de MiniWin; pulsa `Esc` para salir.

## Estructura del codigo

- `app::PixelGrid` gestiona el buffer mediante `std::unique_ptr` y expone un recorrido basado en punteros para evitar copias.
- `app::make_android_pattern` transforma la representacion textual de la figura en datos densos.
- `main.cpp` controla el ciclo de pintado y mantiene limpio el fondo en cada cuadro.

Las zonas comentadas estan en espanol con terminologia habitual en equipos de desarrollo, cuidando que sean breves y utiles.

## Personalizacion

- Ajusta `cellSize` y `margin` en `src/main.cpp` para escalar el sprite.
- Puedes editar el patron en `src/app/AndroidPattern.cpp` cambiando los tokens `B`, `G` y `W`.

## Creditos y licencia

MiniWin es propiedad de Pau Fernandez (licencia MIT). Se ha incluido la version original en `vendor/miniwin/`.
El codigo adicional del proyecto se entrega bajo la misma licencia MIT.
