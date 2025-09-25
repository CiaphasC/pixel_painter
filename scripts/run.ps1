[CmdletBinding()]
param(
    [ValidateSet("Debug", "Release", "RelWithDebInfo", "MinSizeRel")]
    [string]$Configuration = "Release",
    [switch]$Reconfigure,
    [switch]$Run
)

$ErrorActionPreference = "Stop"

$root = (Resolve-Path (Join-Path $PSScriptRoot "..")).ProviderPath
$buildDir = Join-Path $root "build"

function Require-Command {
    param(
        [Parameter(Mandatory = $true)]
        [string]$Name,
        [string]$InstallHint = ""
    )

    if (-not (Get-Command $Name -ErrorAction SilentlyContinue)) {
        $message = "No se encontro el comando '$Name'."
        if ($InstallHint) {
            $message += " $InstallHint"
        }
        throw $message
    }
}

$cmakeDefault = 'C:\Program Files\CMake\bin\cmake.exe'
if (-not (Get-Command 'cmake' -ErrorAction SilentlyContinue)) {
    if (Test-Path $cmakeDefault) {
        $env:Path = (Split-Path $cmakeDefault -Parent) + ';' + $env:Path
    }
}

Require-Command -Name "cmake" -InstallHint "Instala CMake 3.16+ (ejemplo: 'winget install Kitware.CMake')."

if ($Reconfigure -and (Test-Path $buildDir)) {
    Write-Host "Limpiando la carpeta de compilacion $buildDir..."
    Remove-Item -Recurse -Force -LiteralPath $buildDir
}

if (-not (Test-Path $buildDir)) {
    Write-Host "Configurando CMake..."
    $configureArgs = @("-S", $root, "-B", $buildDir)

    if (-not (Test-Path (Join-Path $buildDir "CMakeCache.txt"))) {
        $configureArgs += @("-DCMAKE_BUILD_TYPE=$Configuration")
    }

    cmake @configureArgs
}

if (-not (Test-Path (Join-Path $buildDir "CMakeCache.txt"))) {
    throw "La configuracion de CMake no se completo correctamente."
}

Write-Host "Compilando en configuracion $Configuration..."
$buildArgs = @("--build", $buildDir)
if ($Configuration) {
    $buildArgs += @("--config", $Configuration)
}
cmake @buildArgs

if ($Run) {
    $candidates = @(
        Join-Path $buildDir "droid_pixel_painter.exe"
        Join-Path (Join-Path $buildDir $Configuration) "droid_pixel_painter.exe"
    )

    $executable = $null
    foreach ($candidate in $candidates) {
        if (Test-Path $candidate) {
            $executable = $candidate
            break
        }
    }

    if (-not $executable) {
        throw "No se encontro el ejecutable generado."
    }

    Write-Host ""
    Write-Host "Ejecutando $executable ..."
    & $executable
}
