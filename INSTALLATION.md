# Installation Guide - Mandelbrot Fractal Generator

This guide will help you install and run the Mandelbrot Fractal Generator on your computer.

## Quick Summary

**Windows:**
```bash
install.bat
```

**macOS/Linux:**
```bash
bash install.sh
```

Then open your browser to **http://localhost:8081**

---

## Prerequisites

Choose the installation method that matches your system:

### Windows Users

1. **Install Python 3** (if you don't have it):
   - Download from: https://www.python.org/downloads/
   - **Important**: Check "Add Python to PATH" during installation
   - Verify installation: Open Command Prompt and type `python --version`

2. **Install Visual C++ Build Tools** (needed for C++ compilation):
   - Download: https://visualstudio.microsoft.com/visual-cpp-build-tools/
   - Run the installer and select "Desktop development with C++"
   - This is a large download (~2-3 GB)

3. **Install CMake** (build system):
   - Download: https://cmake.org/download/
   - Download "Windows x86-64 Installer"
   - Run installer, selecting "Add CMake to PATH"
   - Verify: Open Command Prompt and type `cmake --version`

**OR just run the installer:**
```bash
install.bat
```

### macOS Users

1. **Install Homebrew** (if you don't have it):
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```

2. **Install required tools**:
   ```bash
   brew install python3 cmake
   ```

3. **Verify installations**:
   ```bash
   python3 --version
   cmake --version
   ```

**OR just run the installer:**
```bash
bash install.sh
```

### Linux Users (Ubuntu/Debian)

1. **Install required packages**:
   ```bash
   sudo apt-get update
   sudo apt-get install -y python3 python3-pip cmake build-essential zlib1g-dev
   ```

2. **Verify installations**:
   ```bash
   python3 --version
   cmake --version
   ```

**OR just run the installer:**
```bash
bash install.sh
```

### Linux Users (Fedora/RHEL)

1. **Install required packages**:
   ```bash
   sudo dnf groupinstall -y "Development Tools"
   sudo dnf install -y python3 python3-pip cmake zlib-devel
   ```

2. **Verify installations**:
   ```bash
   python3 --version
   cmake --version
   ```

---

## Automated Installation

### Windows

1. Extract the downloaded ZIP file
2. Open Command Prompt in the project folder
3. Run:
   ```bash
   install.bat
   ```
4. Follow the prompts

### macOS/Linux

1. Extract the downloaded TAR.GZ file
2. Open Terminal in the project folder
3. Run:
   ```bash
   bash install.sh
   ```
4. Follow the prompts

---

## Manual Installation (If Script Fails)

### Step 1: Navigate to Project Directory

**Windows:**
```bash
cd path\to\mandelbrot_project
```

**macOS/Linux:**
```bash
cd /path/to/mandelbrot_project
```

### Step 2: Build the Project

**Windows:**
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
cd ..
```

**macOS/Linux:**
```bash
mkdir -p build
cd build
cmake ..
make -j$(nproc)
cd ..
```

### Step 3: Run the Application

**Windows:**
```bash
python mandelbrot_server.py
```

**macOS/Linux:**
```bash
python3 mandelbrot_server.py
```

Then open: **http://localhost:8081**

---

## Troubleshooting

### Problem: "Python not found"
**Solution:** 
- Windows: Reinstall Python and check "Add Python to PATH"
- macOS/Linux: Try `python3 --version` instead of `python --version`

### Problem: "CMake not found"
**Solution:**
- Windows: Reinstall CMake and select "Add to PATH"
- macOS: Run `brew install cmake`
- Linux: Run `sudo apt-get install cmake` (Ubuntu) or `sudo dnf install cmake` (Fedora)

### Problem: "C++ compiler not found"
**Solution:**
- Windows: Install Visual C++ Build Tools
- macOS: Run `xcode-select --install`
- Linux: Run `sudo apt-get install build-essential` (Ubuntu) or `sudo dnf groupinstall "Development Tools"` (Fedora)

### Problem: "Port 8081 already in use"
**Solution:**
- The app will try port 8082, 8083, etc. automatically
- Or kill the process using that port
- Or specify a custom port: `python mandelbrot_server.py --port 9000`

### Problem: "Permission denied" (macOS/Linux)
**Solution:**
```bash
chmod +x install.sh
bash install.sh
```

---

## First Run

1. **Build and run** using the automated scripts or manual steps above
2. **Open your browser** to: http://localhost:8081
3. **Click "Generate Fractal"** to create your first image
4. **Explore presets** like "Deep Zoom" or "Spiral"
5. **Enjoy!** 🎨

---

## Getting Help

- Check [README.md](README.md) for general information
- Check [GUI_GUIDE.md](GUI_GUIDE.md) for GUI usage
- Report issues on GitHub

---

## What Gets Installed?

- ✅ C++ Mandelbrot algorithm library
- ✅ Web server for GUI
- ✅ Python environment setup
- ✅ Build files (can be deleted after first run)
- ✅ Sample fractals in `build/` directory

---

## Uninstallation

Simply delete the project folder. There are no system-wide files installed.

For a clean build:
```bash
rm -rf build/  # macOS/Linux
rmdir /s build # Windows
```

---

## System Requirements

| Component | Minimum | Recommended |
|-----------|---------|-------------|
| RAM | 2 GB | 4+ GB |
| Disk Space | 500 MB | 1+ GB |
| Python | 3.6+ | 3.8+ |
| Internet | No | Yes (for installation) |
| Browser | Any modern browser | Chrome, Firefox, Safari, Edge |

---

## Performance Tips

- **Better Performance**: Disable iterations over 1024 unless needed
- **Faster Generation**: Use smaller resolution (640x480) for testing
- **High Quality**: Use 2560x1920 with 2048 iterations for beautiful images

---

## Next Steps

After installation:
1. Read [README.md](README.md) for features
2. Check [GUI_GUIDE.md](GUI_GUIDE.md) for GUI features
3. Explore the presets in the web interface
4. Customize parameters for your own fractals!

Enjoy exploring the infinite beauty of the Mandelbrot set! 🎨✨
