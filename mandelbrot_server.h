#ifndef MANDELBROT_SERVER_H
#define MANDELBROT_SERVER_H

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <map>

/**
 * Simple HTTP Server for Mandelbrot Fractal Generator
 * Provides REST API endpoints for generating fractals
 * 
 * Usage:
 *   MandelbrotServer server(8080);
 *   server.start();
 *   // Open browser to http://localhost:8080
 */
class MandelbrotServer {
public:
    explicit MandelbrotServer(int port = 8080);
    ~MandelbrotServer();
    
    void start();
    void stop();
    bool isRunning() const { return running; }
    int getPort() const { return port; }
    
private:
    int port;
    bool running;
    int serverSocket;
    
    void run();
    void handleClient(int clientSocket);
    std::string handleRequest(const std::string &request);
    std::string parseParameter(const std::string &query, const std::string &param);
    std::string getHTMLPage();
    std::string generateJSON(bool success, const std::string &message);
};

#endif // MANDELBROT_SERVER_H
