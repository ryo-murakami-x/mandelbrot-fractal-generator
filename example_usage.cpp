#include "mandelbrot.h"
#include <iostream>

int main() {
    std::cout << "Generating Mandelbrot set fractals...\n";
    
    // Example 1: Standard view of the entire Mandelbrot set
    std::cout << "1. Generating standard view..." << std::endl;
    if (draw_mandelbrot("mandelbrot_standard.png", 1920, 1440, 1.0, -0.7, 0.0, 256)) {
        std::cout << "   ✓ Saved to: mandelbrot_standard.png" << std::endl;
    } else {
        std::cerr << "   ✗ Failed to generate mandelbrot_standard.png" << std::endl;
    }
    
    // Example 2: Zoomed view of an interesting region
    std::cout << "2. Generating zoomed view (100x zoom)..." << std::endl;
    if (draw_mandelbrot("mandelbrot_zoom.png", 1920, 1440, 100.0, -0.747, 0.1107, 512)) {
        std::cout << "   ✓ Saved to: mandelbrot_zoom.png" << std::endl;
    } else {
        std::cerr << "   ✗ Failed to generate mandelbrot_zoom.png" << std::endl;
    }
    
    // Example 3: Deep zoom with higher iterations for more detail
    std::cout << "3. Generating deep zoom (1000x zoom)..." << std::endl;
    if (draw_mandelbrot("mandelbrot_deep.png", 2560, 1920, 1000.0, -0.7469, 0.1102, 1024)) {
        std::cout << "   ✓ Saved to: mandelbrot_deep.png" << std::endl;
    } else {
        std::cerr << "   ✗ Failed to generate mandelbrot_deep.png" << std::endl;
    }
    
    // Example 4: Different region - another beautiful area
    std::cout << "4. Generating alternate region..." << std::endl;
    if (draw_mandelbrot("mandelbrot_spiral.png", 1920, 1440, 50.0, -0.8, -0.156, 512)) {
        std::cout << "   ✓ Saved to: mandelbrot_spiral.png" << std::endl;
    } else {
        std::cerr << "   ✗ Failed to generate mandelbrot_spiral.png" << std::endl;
    }
    
    std::cout << "\nAll Mandelbrot fractals generated successfully!" << std::endl;
    return 0;
}
