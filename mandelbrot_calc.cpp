#include <cmath>
#include <vector>
#include <algorithm>

// STB Image Write - single header library for PNG output
// Define the implementation in this file
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/**
 * Calculate the number of iterations for a complex number to escape the Mandelbrot set
 * @param real The real part of the complex number
 * @param imag The imaginary part of the complex number
 * @param maxIterations Maximum number of iterations to test
 * @return Number of iterations before escape (or maxIterations if it doesn't escape)
 */
int mandelbrot_iteration(double real, double imag, int maxIterations) {
    double zReal = 0.0;
    double zImag = 0.0;
    
    for (int i = 0; i < maxIterations; i++) {
        double zReal2 = zReal * zReal;
        double zImag2 = zImag * zImag;
        
        // Check if the magnitude exceeds 2 (escape condition)
        if (zReal2 + zImag2 > 4.0) {
            return i;
        }
        
        // z = z^2 + c
        double temp = zReal2 - zImag2 + real;
        zImag = 2.0 * zReal * zImag + imag;
        zReal = temp;
    }
    
    return maxIterations;
}

/**
 * Convert HSV color to RGB
 * @param h Hue (0-360)
 * @param s Saturation (0-1)
 * @param v Value (0-1)
 * @param r Output red component (0-255)
 * @param g Output green component (0-255)
 * @param b Output blue component (0-255)
 */
void hsv_to_rgb(double h, double s, double v, unsigned char& r, unsigned char& g, unsigned char& b) {
    double c = v * s;
    double hh = h / 60.0;
    double x = c * (1 - std::fabs(std::fmod(hh, 2) - 1));
    double m = v - c;
    
    double rf = 0, gf = 0, bf = 0;
    
    if (hh < 1) { rf = c; gf = x; bf = 0; }
    else if (hh < 2) { rf = x; gf = c; bf = 0; }
    else if (hh < 3) { rf = 0; gf = c; bf = x; }
    else if (hh < 4) { rf = 0; gf = x; bf = c; }
    else if (hh < 5) { rf = x; gf = 0; bf = c; }
    else { rf = c; gf = 0; bf = x; }
    
    r = static_cast<unsigned char>((rf + m) * 255);
    g = static_cast<unsigned char>((gf + m) * 255);
    b = static_cast<unsigned char>((bf + m) * 255);
}

/**
 * Draw the Mandelbrot set and save it as a PNG file
 * @param filename Output PNG filename
 * @param width Image width in pixels
 * @param height Image height in pixels
 * @param zoom Zoom level (higher = more zoomed in)
 * @param centerReal Center X coordinate in complex plane
 * @param centerImag Center Y coordinate in complex plane
 * @param maxIterations Maximum iterations for escape test
 * @return true if successful, false if file couldn't be written
 */
bool draw_mandelbrot(const char* filename, int width, int height, double zoom, 
                     double centerReal, double centerImag, int maxIterations) {
    
    // Create image buffer (RGB format: 3 bytes per pixel)
    std::vector<unsigned char> imageData(width * height * 3);
    
    // Calculate the scale of the complex plane
    double scale = 3.5 / zoom;
    double minReal = centerReal - scale / 2;
    double maxReal = centerReal + scale / 2;
    double minImag = centerImag - (scale * height / width) / 2;
    double maxImag = centerImag + (scale * height / width) / 2;
    
    // Generate the Mandelbrot set
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Map pixel coordinates to complex plane
            double real = minReal + (maxReal - minReal) * x / width;
            double imag = minImag + (maxImag - minImag) * y / height;
            
            // Calculate iterations for this point
            int iterations = mandelbrot_iteration(real, imag, maxIterations);
            
            // Convert iteration count to color
            unsigned char r, g, b;
            if (iterations == maxIterations) {
                // Points in the Mandelbrot set are black
                r = g = b = 0;
            } else {
                // Color based on escape time using HSV
                double hue = (iterations * 360.0) / maxIterations;
                double saturation = 0.8;
                double value = 0.9;
                hsv_to_rgb(hue, saturation, value, r, g, b);
            }
            
            // Store RGB values in the image buffer
            int pixelIndex = (y * width + x) * 3;
            imageData[pixelIndex] = r;
            imageData[pixelIndex + 1] = g;
            imageData[pixelIndex + 2] = b;
        }
    }
    
    // Write the image to a PNG file
    int success = stbi_write_png(filename, width, height, 3, imageData.data(), width * 3);
    
    return success != 0;
}
