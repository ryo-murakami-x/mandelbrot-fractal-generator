# 🎨 Mandelbrot Fractal Generator

A beautiful, cross-platform web application to explore and generate stunning Mandelbrot set fractals. Features an intuitive web GUI, real-time parameter adjustment, and multiple zoom presets.

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![Python: 3.6+](https://img.shields.io/badge/Python-3.6+-blue.svg)
![C++: 11](https://img.shields.io/badge/C++-11-brightgreen.svg)
![Platforms: Windows, macOS, Linux](https://img.shields.io/badge/Platforms-Windows%20|%20macOS%20|%20Linux-lightgrey.svg)

## ✨ Features

- 🎨 **Beautiful Web GUI** - Modern, responsive interface with gradient styling
- 📍 **6 Preset Regions** - Explore famous areas: Standard, Spiral, Deep Zoom, Very Deep, Seahorse Valley, Mini Mandelbrot
- ⚙️ **Real-time Controls** - Adjust zoom, resolution, center point, and iteration count
- 💾 **PNG Export** - Generated fractals saved automatically
- ⚡ **High Performance** - C++ algorithm with efficient color mapping
- 🌈 **Beautiful Colors** - HSV to RGB color mapping for stunning visuals
- 📊 **Live Preview** - Instant image display after generation
- 🖥️ **Cross-Platform** - Works on Windows, macOS, and Linux

## 🚀 Quick Start

### Fastest Setup (5 minutes)

**Windows:**
```bash
install.bat
python mandelbrot_server.py
```

**macOS/Linux:**
```bash
bash install.sh
python3 mandelbrot_server.py
```

Then open your browser: **http://localhost:8080**

### Without Installation Scripts

```bash
# Clone or download this project
cd mandelbrot_project

# Build the project
mkdir build
cd build
cmake ..
make  # or: cmake --build . --config Release (Windows)
cd ..

# Run the web server
python3 mandelbrot_server.py  # python on Windows
```

Open: **http://localhost:8080**

## 📋 System Requirements

| Component | Minimum | Recommended |
|-----------|---------|-------------|
| **Python** | 3.6+ | 3.8+ |
| **RAM** | 2 GB | 4+ GB |
| **Disk** | 500 MB | 1+ GB |
| **Browser** | Any modern | Chrome, Firefox, Safari |

### Dependencies

All dependencies can be installed automatically via `install.sh` or `install.bat`:

- Python 3.6+
- CMake 3.10+
- C++ compiler (GCC, Clang, MSVC)
- zlib (for PNG compression)

See [INSTALLATION.md](INSTALLATION.md) for detailed setup instructions for each platform.

## 📖 Usage

### Web GUI

1. **Start the server:**
   ```bash
   python3 mandelbrot_server.py
   ```

2. **Open browser:**
   ```
   http://localhost:8080
   ```

3. **Generate fractals:**
   - Click preset buttons for famous regions
   - Adjust parameters manually
   - Click "Generate Fractal"
   - View the result instantly!

### Command-Line Interface

```bash
./build/mandelbrot_example
```

Generates 4 example fractals:
- `mandelbrot_standard.png` - Classic view
- `mandelbrot_zoom.png` - 100x zoom
- `mandelbrot_deep.png` - 1000x zoom with high iterations
- `mandelbrot_spiral.png` - Spiral region

## 🎯 Features Guide

### Preset Regions

| Preset | Description | Zoom |
|--------|-------------|------|
| **Standard** | Full Mandelbrot set | 1x |
| **Spiral** | Beautiful spiral pattern | 50x |
| **Deep Zoom** | Intricate detail area | 100x |
| **Very Deep** | Ultra-deep zoom | 1000x |
| **Seahorse Valley** | Famous seahorse feature | 200x |
| **Mini Mandelbrot** | Miniature copy of set | 1000x |

### Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| **Width** | 320-4096 | 1920 | Image width in pixels |
| **Height** | 240-3072 | 1440 | Image height in pixels |
| **Zoom** | 0.1-100000 | 1.0 | Magnification level |
| **Center X** | -3 to 2 | -0.7 | Real coordinate of center |
| **Center Y** | -2 to 2 | 0.0 | Imaginary coordinate |
| **Iterations** | 16-4096 | 256 | Max calculation depth |

## 🏗️ Building from Source

### Prerequisites

**Windows:**
- Python 3.6+
- CMake 3.10+
- Visual C++ Build Tools
- (Run `install.bat` to install automatically)

**macOS:**
- Python 3.6+
- CMake 3.10+
- Xcode Command Line Tools
- (Run `bash install.sh` to install automatically)

**Linux:**
- Python 3.6+
- CMake 3.10+
- build-essential (GCC/Clang)
- zlib development files
- (Run `bash install.sh` to install automatically)

### Build Commands

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Compile
make -j$(nproc)      # macOS/Linux
# or
cmake --build . --config Release  # Windows

# Return to project root
cd ..
```

**Output:**
- `build/mandelbrot_example` - CLI executable
- `build/mandelbrot_wrapper` - Web server helper
- `build/libmandelbrot_lib.a` - Static library
- `build/mandelbrot_*.png` - Generated images

## 🌐 Web Server

### Start Server

```bash
# Default port (8080, falls back to 8081, 8082, etc.)
python3 mandelbrot_server.py

# Custom port
python3 mandelbrot_server.py --port 9000

# Using convenience script
./run_gui.sh        # default port
./run_gui.sh 9000   # custom port
```

### Access

- **URL:** http://localhost:8080
- **Stop:** Press Ctrl+C

### Generated Files

Images are saved to: `build/mandelbrot_output.png`

## 📚 Documentation

- **[INSTALLATION.md](INSTALLATION.md)** - Detailed setup guide for all platforms
- **[GUI_GUIDE.md](GUI_GUIDE.md)** - Web GUI usage and features
- **[START_HERE.md](START_HERE.md)** - Quick start guide

## 🧮 Algorithm Details

### Mandelbrot Set Calculation

The algorithm uses the escape-time method:

1. For each pixel, map coordinates to complex plane
2. Iterate: `z = z² + c` until `|z| > 2`
3. Color based on iteration count at escape

### Performance

- **Generation time:** 2-30 seconds (varies by parameters)
- **Resolution:** Up to 4096×3072
- **Iterations:** Up to 4096 for detail
- **Output format:** 24-bit RGB PNG with zlib compression

## 🎓 Interesting Coordinates

Try these coordinates for beautiful views:

| Name | Real | Imaginary | Zoom |
|------|------|-----------|------|
| Standard Set | -0.7 | 0.0 | 1x |
| Seahorse Valley | -0.75 | 0.1 | 200x |
| Spiral | -0.8 | -0.156 | 50x |
| Deep Area | -0.747 | 0.1107 | 100x |
| Mini Set | -0.16 | 1.036 | 1000x |

## 🐛 Troubleshooting

**"Python not found"**
- Windows: Install Python from https://www.python.org and check "Add to PATH"
- macOS/Linux: Use `python3` instead of `python`

**"CMake not found"**
- Install CMake from https://cmake.org/download/
- Ensure it's added to your PATH

**"Port already in use"**
- The app automatically tries alternate ports
- Or specify custom port: `python3 mandelbrot_server.py --port 9000`

**"Build failed"**
- Ensure all dependencies are installed
- Run `install.sh` or `install.bat` to auto-install
- See [INSTALLATION.md](INSTALLATION.md) for detailed help

**"No C++ compiler found"**
- Windows: Install Visual C++ Build Tools
- macOS: Run `xcode-select --install`
- Linux: Run `sudo apt-get install build-essential`

See [INSTALLATION.md](INSTALLATION.md) for more troubleshooting.

## 📄 License

This project is licensed under the MIT License - see [LICENSE](LICENSE) file for details.

### Third-Party Components

- **stb_image_write.h** - PNG writing library by Sean T. Barrett (Public Domain)
- **zlib** - Compression library (Zlib License)

## 🤝 Contributing

Contributions welcome! Areas for improvement:

- Performance optimization
- Additional preset regions
- Mobile app version
- Docker support
- Additional export formats

## ❓ FAQ

**Q: Can I use this commercially?**
A: Yes! MIT license allows commercial use. See [LICENSE](LICENSE).

**Q: Does it work offline?**
A: Yes! After installation, everything runs locally.

**Q: Can I modify the source code?**
A: Yes! Feel free to fork and customize.

**Q: How do I generate high-resolution images?**
A: Increase width/height in web GUI or modify `example_usage.cpp` for CLI.

## 🚀 Getting Started

1. **Install:** Run `install.sh` (macOS/Linux) or `install.bat` (Windows)
2. **Start:** Run `python3 mandelbrot_server.py`
3. **Open:** Visit http://localhost:8080
4. **Explore:** Click preset buttons or adjust parameters
5. **Enjoy:** Beautiful fractals! 🎨

## 📧 Support

- Check [INSTALLATION.md](INSTALLATION.md) for setup help
- See [GUI_GUIDE.md](GUI_GUIDE.md) for usage questions
- Review [START_HERE.md](START_HERE.md) for quick start

---

**Explore the infinite beauty of the Mandelbrot set!** ✨

Made with ❤️ by Mandelbrot Fractal Generator Contributors
