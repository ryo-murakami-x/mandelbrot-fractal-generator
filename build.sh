#!/bin/bash

# Mandelbrot Project Build Script
# Builds the C++ Mandelbrot fractal generator

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_DIR="$SCRIPT_DIR"
BUILD_DIR="$PROJECT_DIR/build"

echo "🏗️  Building Mandelbrot Fractal Generator"
echo "=========================================="
echo ""

# Check if cmake is available
if ! command -v cmake &> /dev/null; then
    echo "❌ Error: CMake is not installed"
    echo "   Install with: brew install cmake"
    exit 1
fi

echo "✓ CMake found: $(cmake --version | head -1)"

# Check if a C++ compiler is available
if ! command -v clang++ &> /dev/null && ! command -v g++ &> /dev/null; then
    echo "❌ Error: No C++ compiler found"
    echo "   Install Xcode: xcode-select --install"
    exit 1
fi

echo "✓ C++ compiler found"

# Check for zlib
if ! pkg-config --exists zlib 2>/dev/null && ! brew list zlib &>/dev/null 2>&1; then
    echo "⚠️  Warning: zlib not found, attempting to install..."
    brew install zlib
fi

echo "✓ zlib found"
echo ""

# Create build directory
if [ ! -d "$BUILD_DIR" ]; then
    echo "📁 Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

cd "$BUILD_DIR"

# Configure with CMake
echo "⚙️  Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
echo ""
echo "🔨 Building..."
make -j$(sysctl -n hw.ncpu)

echo ""
echo "✅ Build complete!"
echo ""
echo "📦 Build outputs:"
echo "   - Executable: $BUILD_DIR/mandelbrot_example"

if [ -f "$BUILD_DIR/mandelbrot_gui" ]; then
    echo "   - GUI (Qt5): $BUILD_DIR/mandelbrot_gui"
else
    echo "   - GUI (Qt5): Not built (Qt5 not installed)"
fi

echo "   - Library: $BUILD_DIR/libmandelbrot_lib.a"
echo ""
echo "🎨 Generated fractals:"
for png in "$BUILD_DIR"/*.png; do
    if [ -f "$png" ]; then
        size=$(du -h "$png" | cut -f1)
        echo "   - $(basename "$png") ($size)"
    fi
done

echo ""
echo "🚀 Next steps:"
echo "   1. Run CLI: ./build/mandelbrot_example"
echo "   2. Run Web GUI: ./run_gui.sh"
echo "   3. Run Qt GUI: ./build/mandelbrot_gui  (if Qt5 available)"
