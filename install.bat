@echo off
REM =============================================================================
REM Mandelbrot Fractal Generator - Installation Script for Windows
REM =============================================================================
REM This script automates the installation and setup of the Mandelbrot
REM Fractal Generator for Windows systems.
REM =============================================================================

setlocal enabledelayedexpansion

set "RED=[91m"
set "GREEN=[92m"
set "YELLOW=[93m"
set "BLUE=[94m"
set "NC=[0m"

REM Colors for Windows (simplified - cmd.exe doesn't support ANSI colors natively)
REM Using title and echo instead

cls
title Mandelbrot Fractal Generator - Installation

echo.
echo ===================================================================
echo Mandelbrot Fractal Generator - Windows Installation
echo ===================================================================
echo.

REM Check dependencies
echo [*] Checking Dependencies...
echo.

REM Check Python
python --version >nul 2>&1
if %errorlevel% equ 0 (
    for /f "tokens=2" %%i in ('python --version 2^>^&1') do set PYTHON_VER=%%i
    echo [OK] Python found: !PYTHON_VER!
) else (
    echo [ERROR] Python not found
    echo.
    echo Please install Python 3 from:
    echo https://www.python.org/downloads/
    echo.
    echo Important: Check "Add Python to PATH" during installation
    echo.
    pause
    exit /b 1
)

REM Check CMake
cmake --version >nul 2>&1
if %errorlevel% equ 0 (
    echo [OK] CMake found
) else (
    echo [ERROR] CMake not found
    echo.
    echo Please install CMake from:
    echo https://cmake.org/download/
    echo.
    echo Download: "Windows x86-64 Installer"
    echo Select: "Add CMake to PATH" during installation
    echo.
    pause
    exit /b 1
)

REM Check Visual C++ Build Tools
REM Try to find MSVC compiler
cl >nul 2>&1
if %errorlevel% equ 0 (
    echo [OK] Visual C++ compiler found
) else (
    echo [ERROR] Visual C++ Build Tools not found
    echo.
    echo Please install Visual C++ Build Tools from:
    echo https://visualstudio.microsoft.com/visual-cpp-build-tools/
    echo.
    echo During installation, select: "Desktop development with C++"
    echo This is a large download (2-3 GB)
    echo.
    pause
    exit /b 1
)

echo.
echo [*] Building Project...
echo.

REM Set project directory
set PROJECT_DIR=%~dp0

REM Check if build directory exists
if exist "%PROJECT_DIR%build" (
    echo [*] Cleaning old build directory...
    rmdir /s /q "%PROJECT_DIR%build"
)

REM Create build directory
echo [*] Creating build directory...
mkdir "%PROJECT_DIR%build"
cd /d "%PROJECT_DIR%build"

REM Run CMake
echo [*] Running CMake...
cmake .. || (
    echo [ERROR] CMake configuration failed
    pause
    exit /b 1
)

REM Build project
echo [*] Compiling (this may take a moment)...
cmake --build . --config Release || (
    echo [ERROR] Build failed
    pause
    exit /b 1
)

cd /d "%PROJECT_DIR%"

echo.
echo [OK] Build completed successfully!
echo.
echo [*] Verifying Installation...
echo.

REM Check executables
if exist "%PROJECT_DIR%build\Release\mandelbrot_example.exe" (
    echo [OK] CLI executable found
) else if exist "%PROJECT_DIR%build\mandelbrot_example.exe" (
    echo [OK] CLI executable found
) else (
    echo [WARN] CLI executable not found
)

if exist "%PROJECT_DIR%build\Release\mandelbrot_wrapper.exe" (
    echo [OK] Wrapper executable found
) else if exist "%PROJECT_DIR%build\mandelbrot_wrapper.exe" (
    echo [OK] Wrapper executable found
) else (
    echo [WARN] Wrapper executable not found
)

echo.
echo ===================================================================
echo Installation Complete!
echo ===================================================================
echo.
echo 🎉 Mandelbrot Fractal Generator is ready!
echo.
echo Next steps:
echo.
echo 1. Start the web server:
echo    python mandelbrot_server.py
echo.
echo 2. Open your browser to:
echo    http://localhost:8080
echo.
echo 3. Or use the convenience script:
echo    run_gui.sh
echo.
echo For more information, see:
echo    README.md - General information
echo    GUI_GUIDE.md - GUI usage guide
echo    START_HERE.md - Quick start guide
echo.
echo ===================================================================
echo.

pause
