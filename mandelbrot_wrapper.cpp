#include "mandelbrot.h"
#include <iostream>
#include <cstdlib>
#include <string>

/**
 * Wrapper program to generate Mandelbrot fractals with command-line parameters
 * Called by the Python web server
 * 
 * Usage:
 *   mandelbrot_wrapper <output_file> <width> <height> <zoom> <centerReal> <centerImag> <iterations>
 */

int main(int argc, char* argv[]) {
    if (argc != 8) {
        std::cerr << "Usage: " << argv[0] 
                  << " <output_file> <width> <height> <zoom> <centerReal> <centerImag> <iterations>"
                  << std::endl;
        return 1;
    }
    
    try {
        // Parse command-line arguments
        const char* output_file = argv[1];
        int width = std::stoi(argv[2]);
        int height = std::stoi(argv[3]);
        double zoom = std::stod(argv[4]);
        double centerReal = std::stod(argv[5]);
        double centerImag = std::stod(argv[6]);
        int iterations = std::stoi(argv[7]);
        
        // Validate parameters
        if (width < 320 || width > 4096) {
            std::cerr << "Width must be between 320 and 4096" << std::endl;
            return 1;
        }
        if (height < 240 || height > 3072) {
            std::cerr << "Height must be between 240 and 3072" << std::endl;
            return 1;
        }
        if (zoom < 0.1 || zoom > 100000) {
            std::cerr << "Zoom must be between 0.1 and 100000" << std::endl;
            return 1;
        }
        if (iterations < 16 || iterations > 4096) {
            std::cerr << "Iterations must be between 16 and 4096" << std::endl;
            return 1;
        }
        
        // Generate the fractal
        std::cout << "Generating Mandelbrot fractal..." << std::endl;
        std::cout << "  Output: " << output_file << std::endl;
        std::cout << "  Resolution: " << width << "x" << height << std::endl;
        std::cout << "  Zoom: " << zoom << "x" << std::endl;
        std::cout << "  Center: (" << centerReal << ", " << centerImag << ")" << std::endl;
        std::cout << "  Iterations: " << iterations << std::endl;
        
        if (draw_mandelbrot(output_file, width, height, zoom, centerReal, centerImag, iterations)) {
            std::cout << "✓ Fractal generated successfully!" << std::endl;
            return 0;
        } else {
            std::cerr << "✗ Failed to generate fractal" << std::endl;
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
