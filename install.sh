#!/bin/bash

#=============================================================================
# Mandelbrot Fractal Generator - Installation Script for macOS/Linux
#=============================================================================
# This script automates the installation and setup of the Mandelbrot
# Fractal Generator for macOS and Linux systems.
#=============================================================================

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Functions
print_header() {
    echo -e "\n${BLUE}═══════════════════════════════════════════════════════════${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}═══════════════════════════════════════════════════════════${NC}\n"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠ $1${NC}"
}

print_info() {
    echo -e "${BLUE}ℹ $1${NC}"
}

# Main installation
main() {
    print_header "Mandelbrot Fractal Generator - Installation"
    
    # Detect OS
    if [[ "$OSTYPE" == "darwin"* ]]; then
        OS="macOS"
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        OS="Linux"
    else
        print_error "Unsupported operating system: $OSTYPE"
        exit 1
    fi
    
    print_info "Detected OS: $OS"
    
    # Check dependencies
    print_header "Checking Dependencies"
    
    # Check Python
    if command -v python3 &> /dev/null; then
        PYTHON_VERSION=$(python3 --version 2>&1 | awk '{print $2}')
        print_success "Python 3 found: $PYTHON_VERSION"
    else
        print_error "Python 3 not found"
        print_warning "Please install Python 3 and try again"
        if [[ "$OS" == "macOS" ]]; then
            print_info "Run: brew install python3"
        else
            print_info "Run: sudo apt-get install python3 (Ubuntu/Debian)"
            print_info "     or sudo dnf install python3 (Fedora/RHEL)"
        fi
        exit 1
    fi
    
    # Check CMake
    if command -v cmake &> /dev/null; then
        CMAKE_VERSION=$(cmake --version | head -1 | awk '{print $3}')
        print_success "CMake found: $CMAKE_VERSION"
    else
        print_error "CMake not found"
        print_warning "Please install CMake and try again"
        if [[ "$OS" == "macOS" ]]; then
            print_info "Run: brew install cmake"
        else
            print_info "Run: sudo apt-get install cmake (Ubuntu/Debian)"
            print_info "     or sudo dnf install cmake (Fedora/RHEL)"
        fi
        exit 1
    fi
    
    # Check C++ compiler
    if command -v g++ &> /dev/null || command -v clang++ &> /dev/null; then
        if command -v clang++ &> /dev/null; then
            CXX_VERSION=$(clang++ --version 2>&1 | head -1)
        else
            CXX_VERSION=$(g++ --version 2>&1 | head -1)
        fi
        print_success "C++ compiler found: $CXX_VERSION"
    else
        print_error "C++ compiler not found"
        print_warning "Please install build tools and try again"
        if [[ "$OS" == "macOS" ]]; then
            print_info "Run: xcode-select --install"
        else
            print_info "Run: sudo apt-get install build-essential (Ubuntu/Debian)"
            print_info "     or sudo dnf groupinstall 'Development Tools' (Fedora/RHEL)"
        fi
        exit 1
    fi
    
    # Check zlib
    if [[ "$OS" == "macOS" ]]; then
        if pkg-config --exists zlib 2>/dev/null; then
            print_success "zlib found"
        else
            print_warning "zlib not found, attempting to install..."
            brew install zlib || true
        fi
    else
        if pkg-config --exists zlib 2>/dev/null; then
            print_success "zlib found"
        else
            print_warning "zlib development files not found"
            print_info "Run: sudo apt-get install zlib1g-dev (Ubuntu/Debian)"
            print_info "     or sudo dnf install zlib-devel (Fedora/RHEL)"
            exit 1
        fi
    fi
    
    # Build project
    print_header "Building Project"
    
    PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
    cd "$PROJECT_DIR"
    
    if [ -d "build" ]; then
        print_warning "Build directory already exists, cleaning..."
        rm -rf build
    fi
    
    print_info "Creating build directory..."
    mkdir -p build
    
    print_info "Running CMake..."
    cd build
    cmake .. || {
        print_error "CMake configuration failed"
        exit 1
    }
    
    print_info "Compiling (this may take a moment)..."
    CPU_COUNT=$(sysctl -n hw.ncpu 2>/dev/null || nproc 2>/dev/null || echo 1)
    make -j"$CPU_COUNT" || {
        print_error "Build failed"
        exit 1
    }
    
    cd "$PROJECT_DIR"
    print_success "Build completed successfully!"
    
    # Verify executables
    print_header "Verifying Installation"
    
    if [ -f "build/mandelbrot_example" ]; then
        print_success "CLI executable found"
    else
        print_warning "CLI executable not found"
    fi
    
    if [ -f "build/mandelbrot_wrapper" ]; then
        print_success "Wrapper executable found"
    else
        print_warning "Wrapper executable not found"
    fi
    
    if [ -f "build/libmandelbrot_lib.a" ]; then
        print_success "Static library found"
    else
        print_warning "Static library not found"
    fi
    
    # Success message
    print_header "Installation Complete!"
    
    echo -e "${GREEN}🎉 Mandelbrot Fractal Generator is ready!${NC}\n"
    
    echo "Next steps:"
    echo "1. Start the web server:"
    echo -e "   ${YELLOW}python3 mandelbrot_server.py${NC}"
    echo ""
    echo "2. Open your browser to:"
    echo -e "   ${YELLOW}http://localhost:8080${NC}"
    echo ""
    echo "3. Or use the convenience script:"
    echo -e "   ${YELLOW}./run_gui.sh${NC}"
    echo ""
    echo "For more information, see:"
    echo -e "   ${YELLOW}README.md${NC} - General information"
    echo -e "   ${YELLOW}GUI_GUIDE.md${NC} - GUI usage guide"
    echo -e "   ${YELLOW}START_HERE.md${NC} - Quick start guide"
    echo ""
}

# Run main function
main "$@"
