#!/usr/bin/env python3
"""
Mandelbrot Set Fractal Generator - Web GUI Server

This script provides a web-based interface to the Mandelbrot fractal generator.
It serves an HTML GUI and handles requests to generate fractals by calling
the compiled C++ executable.

Usage:
    python3 mandelbrot_server.py --port 8080
    
Then open your browser to http://localhost:8080
"""

import http.server
import socketserver
import json
import subprocess
import os
import argparse
import threading
from pathlib import Path
from urllib.parse import urlparse, parse_qs

class MandelbrotHTTPHandler(http.server.SimpleHTTPRequestHandler):
    """HTTP Request Handler for Mandelbrot GUI"""
    
    def do_GET(self):
        """Handle GET requests"""
        parsed_path = urlparse(self.path)
        path = parsed_path.path
        query = parse_qs(parsed_path.query)
        
        # Serve the HTML GUI
        if path == '/' or path == '/index.html':
            self.serve_html_gui()
        
        # API endpoint to generate fractal
        elif path == '/api/generate':
            self.generate_fractal(query)
        
        # Serve static files from build directory
        elif path.startswith('/images/'):
            self.serve_image(path)
        
        else:
            self.send_error(404, "Not Found")
    
    def serve_html_gui(self):
        """Serve the HTML GUI"""
        html_file = Path(__file__).parent / 'mandelbrot_gui.html'
        
        if html_file.exists():
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.send_header('Cache-Control', 'no-cache')
            self.end_headers()
            
            with open(html_file, 'rb') as f:
                self.wfile.write(f.read())
        else:
            self.send_error(404, "GUI file not found")
    
    def generate_fractal(self, query):
        """Generate a Mandelbrot fractal"""
        try:
            # Parse parameters with defaults
            width = int(query.get('width', ['1920'])[0])
            height = int(query.get('height', ['1440'])[0])
            zoom = float(query.get('zoom', ['1.0'])[0])
            center_real = float(query.get('centerReal', ['-0.7'])[0])
            center_imag = float(query.get('centerImag', ['0.0'])[0])
            iterations = int(query.get('iterations', ['256'])[0])
            
            # Validate parameters
            width = max(320, min(4096, width))
            height = max(240, min(3072, height))
            zoom = max(0.1, min(100000, zoom))
            iterations = max(16, min(4096, iterations))
            
            # Get the build directory
            build_dir = Path(__file__).parent / 'build'
            output_file = build_dir / 'mandelbrot_output.png'
            
            # Find the executable
            executable = build_dir / 'mandelbrot_example'
            if not executable.exists():
                raise FileNotFoundError(f"Executable not found: {executable}")
            
            # Create a custom C++ program to generate with specific parameters
            # For now, we'll use the mandelbrot_lib through a simple wrapper
            result = self.call_mandelbrot_cpp(
                str(output_file), width, height, zoom, 
                center_real, center_imag, iterations
            )
            
            if result:
                response = {
                    'success': True,
                    'message': f'Fractal generated: {width}×{height}, Zoom: {zoom}x',
                    'image_url': '/images/mandelbrot_output.png',
                    'parameters': {
                        'width': width,
                        'height': height,
                        'zoom': zoom,
                        'centerReal': center_real,
                        'centerImag': center_imag,
                        'iterations': iterations
                    }
                }
            else:
                response = {'success': False, 'message': 'Failed to generate fractal'}
            
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps(response).encode())
        
        except Exception as e:
            response = {'success': False, 'message': str(e)}
            self.send_response(500)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps(response).encode())
    
    def call_mandelbrot_cpp(self, output_file, width, height, zoom, center_real, center_imag, iterations):
        """
        Call the C++ Mandelbrot wrapper to generate a fractal.
        The wrapper executable takes parameters as command-line arguments.
        """
        try:
            build_dir = Path(__file__).parent / 'build'
            wrapper_exe = build_dir / 'mandelbrot_wrapper'
            
            if not wrapper_exe.exists():
                raise FileNotFoundError(f"Wrapper executable not found: {wrapper_exe}")
            
            # Call the wrapper with parameters
            cmd = [
                str(wrapper_exe),
                str(output_file),
                str(width),
                str(height),
                str(zoom),
                str(center_real),
                str(center_imag),
                str(iterations)
            ]
            
            print(f"[Server] Executing: {' '.join(cmd)}")
            result = subprocess.run(cmd, capture_output=True, text=True, timeout=60)
            
            if result.returncode == 0:
                print(f"[Server] Success: {output_file}")
                print(result.stdout)
                return True
            else:
                print(f"[Server] Error generating fractal:")
                print(result.stderr)
                return False
            
        except subprocess.TimeoutExpired:
            print(f"[Server] Error: Generation timed out")
            return False
        except Exception as e:
            print(f"[Server] Error: {e}")
            return False
    
    def serve_image(self, path):
        """Serve image files from the build directory"""
        try:
            # Remove '/images/' prefix properly (not using lstrip which strips characters)
            if path.startswith('/images/'):
                filename = path[8:]  # len('/images/') == 8
            else:
                filename = path
            
            image_file = Path(__file__).parent / 'build' / filename
            
            if image_file.exists() and image_file.is_file():
                self.send_response(200)
                self.send_header('Content-type', 'image/png')
                self.send_header('Cache-Control', 'no-cache')
                self.end_headers()
                
                with open(image_file, 'rb') as f:
                    self.wfile.write(f.read())
            else:
                self.send_error(404, "Image not found")
        except Exception as e:
            print(f"[Server] Error serving image: {e}")
            self.send_error(500, "Server Error")
    
    def log_message(self, format, *args):
        """Suppress default logging"""
        print(f"[{self.log_date_time_string()}] {format % args}")


def run_server(port=8080):
    """Run the HTTP server"""
    
    # Change to the project directory
    project_dir = Path(__file__).parent
    os.chdir(project_dir)
    
    handler = MandelbrotHTTPHandler
    
    try:
        with socketserver.TCPServer(("", port), handler) as httpd:
            print(f"🚀 Mandelbrot GUI Server Started")
            print(f"📍 Open your browser to: http://localhost:{port}")
            print(f"📁 Serving from: {project_dir}")
            print(f"⚙️  Press Ctrl+C to stop the server\n")
            httpd.serve_forever()
    except KeyboardInterrupt:
        print("\n\n🛑 Server stopped")
    except OSError as e:
        print(f"❌ Error: {e}")
        print(f"   Port {port} might already be in use")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Mandelbrot Fractal Generator - Web GUI Server'
    )
    parser.add_argument(
        '--port', '-p',
        type=int,
        default=8080,
        help='Port to run the server on (default: 8080)'
    )
    
    args = parser.parse_args()
    run_server(args.port)
