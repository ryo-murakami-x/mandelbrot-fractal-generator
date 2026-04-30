#ifndef MANDELBROT_H
#define MANDELBROT_H

/**
 * Draw the Mandelbrot set and save it as a PNG file
 * 
 * @param filename Output PNG filename (e.g., "mandelbrot.png")
 * @param width Image width in pixels (recommended: 1920 or higher for better quality)
 * @param height Image height in pixels (recommended: 1440 or higher for better quality)
 * @param zoom Zoom level (1.0 = standard view, higher values = more zoomed in)
 * @param centerReal Center X coordinate in complex plane (typically -0.7 to 0.0)
 * @param centerImag Center Y coordinate in complex plane (typically -0.5 to 0.5)
 * @param maxIterations Maximum iterations for escape test (higher = more detail but slower, default 256)
 * 
 * @return true if the PNG file was successfully written, false otherwise
 * 
 * EXAMPLE USAGE:
 *   // Standard view of the Mandelbrot set
 *   draw_mandelbrot("mandelbrot_standard.png", 1920, 1440, 1.0, -0.7, 0.0, 256);
 *   
 *   // Zoomed-in view of an interesting region
 *   draw_mandelbrot("mandelbrot_zoom.png", 1920, 1440, 100.0, -0.747, 0.1107, 512);
 *   
 *   // High-resolution zoomed view
 *   draw_mandelbrot("mandelbrot_deep_zoom.png", 4096, 3072, 1000.0, -0.7469, 0.1102, 1024);
 */
bool draw_mandelbrot(const char* filename, int width, int height, double zoom,
                     double centerReal, double centerImag, int maxIterations = 256);

#endif // MANDELBROT_H
