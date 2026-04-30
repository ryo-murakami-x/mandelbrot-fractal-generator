#!/bin/bash

# Mandelbrot GUI Launcher
# This script launches the web-based GUI for the Mandelbrot fractal generator

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PROJECT_DIR="$SCRIPT_DIR"
PORT=${1:-8080}

echo "🎨 Mandelbrot Set Fractal Generator - Web GUI"
echo "=============================================="
echo ""

# Check if Python 3 is available
if ! command -v python3 &> /dev/null; then
    echo "❌ Error: Python 3 is not installed"
    echo "   Install with: brew install python3"
    exit 1
fi

echo "✓ Python 3 found"

# Check if the server script exists
if [ ! -f "$PROJECT_DIR/mandelbrot_server.py" ]; then
    echo "❌ Error: mandelbrot_server.py not found"
    exit 1
fi

echo "✓ Server script found"
echo ""

# Check if pre-built executables exist
BUILD_DIR="$PROJECT_DIR/build"
if [ ! -d "$BUILD_DIR" ]; then
    echo "⚠️  Warning: build directory not found"
    echo "   Run './build_project.sh' first to compile the project"
    exit 1
fi

if [ ! -f "$BUILD_DIR/mandelbrot_example" ]; then
    echo "⚠️  Warning: mandelbrot_example executable not found"
    echo "   Run './build_project.sh' first to compile the project"
    exit 1
fi

echo "✓ Build directory found"
echo ""

# Check if port is available
if lsof -i :$PORT > /dev/null 2>&1; then
    echo "⚠️  Port $PORT is already in use"
    echo "   Using alternate port $(($PORT + 1))"
    PORT=$(($PORT + 1))
fi

echo "🚀 Starting Mandelbrot GUI Server"
echo "📍 Open your browser to: http://localhost:$PORT"
echo "📁 Project: $PROJECT_DIR"
echo "⚙️  Port: $PORT"
echo ""
echo "Press Ctrl+C to stop the server"
echo ""

cd "$PROJECT_DIR"
python3 mandelbrot_server.py --port $PORT
