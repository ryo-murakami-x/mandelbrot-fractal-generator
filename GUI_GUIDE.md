# Mandelbrot GUI Quick Start Guide

## Two GUI Options Available

### Option 1: Web-Based GUI (Recommended - Works Now!)

The web-based GUI requires no additional installations and works immediately.

**Steps:**

1. **Start the Python web server:**
   ```bash
   cd /path/to/mandelbrot-fractal-generator
   python3 mandelbrot_server.py
   ```

2. **Open your browser to:**
   ```
   http://localhost:8080
   ```

3. **Features:**
   - 🎨 Beautiful, modern interface
   - 📍 6 preset regions (Standard, Spiral, Deep Zoom, Very Deep, Seahorse Valley, Mini Mandelbrot)
   - ⚙️ Real-time parameter adjustment
   - 📐 Customizable resolution (320×240 to 4096×3072)
   - 🔢 Adjustable iterations (16 to 4096)
   - 📊 Live preview of generated fractals
   - 💾 Automatic save to PNG files

**How to use:**
1. Select a preset or adjust parameters manually
2. Click "Generate Fractal"
3. View the result in the display area
4. Generated PNGs are saved in the `build/` directory

---

### Option 2: Qt5 Desktop GUI (Advanced - Requires Installation)

For a native desktop application with more advanced features.

**Prerequisites:**
```bash
brew install qt5
```

**Building:**
```bash
cd /path/to/mandelbrot-fractal-generator
mkdir -p build
cd build
cmake ..
make
./mandelbrot_gui
```

**Features:**
- Native desktop application
- Multi-threaded generation (keeps UI responsive)
- Scrollable image viewer
- Parameter spinboxes for fine control
- Open output folder button
- Progress bar during generation

---

## Using Existing Generated Fractals

Pre-generated fractals are available in the `build/` directory:

- `mandelbrot_standard.png` (199 KB) - Standard full view
- `mandelbrot_zoom.png` (539 KB) - 100x zoom
- `mandelbrot_deep.png` (2.3 MB) - 1000x zoom  
- `mandelbrot_spiral.png` (583 KB) - Spiral region

---

## Command-Line Interface

For batch generation without a GUI:

```bash
cd /path/to/mandelbrot-fractal-generator/build
./mandelbrot_example
```

This generates all preset images automatically.

---

## Calling from Your Own C++ Code

```cpp
#include "mandelbrot.h"

int main() {
    // Generate a custom fractal
    draw_mandelbrot("my_fractal.png", 1920, 1440, 50.0, -0.8, -0.156, 512);
    return 0;
}
```

Link against `mandelbrot_lib` using CMake:
```cmake
target_link_libraries(my_app PRIVATE mandelbrot_lib)
```

---

## Interesting Coordinates to Explore

| Region | X | Y | Zoom | Description |
|--------|---|---|------|-------------|
| Standard | -0.7 | 0.0 | 1.0 | Full Mandelbrot set |
| Spiral | -0.8 | -0.156 | 50 | Beautiful spiral |
| Seahorse Valley | -0.75 | 0.1 | 200 | Intricate structures |
| Mini Mandelbrot | -0.16 | 1.036 | 1000 | Recursive self-similarity |
| Dragon Curve Area | -0.768 | 0.088 | 300 | Dragon-like patterns |
| Julia-Mandelbrot Junction | -0.748 | 0.099 | 500 | Complex borders |

---

## Tips for Best Results

1. **Resolution**: Higher resolution = better detail but slower rendering
   - Preview: 1280×960 with 256 iterations
   - High quality: 1920×1440 with 512 iterations
   - Ultra: 2560×1920 with 1024+ iterations

2. **Zoom levels**:
   - 1.0 = standard view
   - 10-100 = explore interesting regions
   - 1000+ = deep zoom into fractal structure

3. **Iterations**: 
   - 256 = fast preview
   - 512-1024 = good balance
   - 2048+ = very detailed (slow)

---

## Troubleshooting

**Web GUI not loading?**
- Ensure Python 3 is installed: `python3 --version`
- Check port 8080 is not in use: `lsof -i :8080`
- Try a different port: `python3 mandelbrot_server.py --port 8081`

**Qt GUI build fails?**
- Qt5 installation may still be in progress
- Check: `brew list qt@5`
- Reinstall: `brew reinstall qt@5`
- Set CMAKE_PREFIX_PATH: 
  ```bash
  cmake .. -DCMAKE_PREFIX_PATH=$(brew --prefix qt@5)
  ```

**PNG generation fails?**
- Ensure write permissions in `build/` directory
- Check disk space: `df -h`
- Verify zlib is installed: `brew list zlib`

---

## File Structure

```
mandelbrot-fractal-generator/
├── mandelbrot_calc.cpp      # Core algorithm
├── mandelbrot.h             # Public API
├── mandelbrot_gui.h/cpp     # Qt5 GUI (optional)
├── mandelbrot_gui.html      # Web GUI interface
├── mandelbrot_server.py     # Python web server
├── example_usage.cpp        # CLI demo
├── CMakeLists.txt           # Build configuration
└── build/                   # Compiled executables & output
    ├── mandelbrot_example
    ├── mandelbrot_gui       # (if Qt5 available)
    └── *.png                # Generated fractals
```

---

## Performance Notes

**Generation times (approximate):**
- 1920×1440 @ 256 iterations: 1-2 seconds
- 1920×1440 @ 512 iterations: 2-4 seconds
- 2560×1920 @ 512 iterations: 4-8 seconds
- 4096×3072 @ 1024 iterations: 20-40 seconds

**Rendering is CPU-bound** - higher iteration counts significantly increase time.

---

For more details, see [README.md](README.md)
