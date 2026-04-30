#include "mandelbrot_gui.h"
#include "mandelbrot.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPixmap>
#include <QScrollArea>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QCoreApplication>
#include <QDir>
#include <thread>
#include <iostream>

MandelbrotGUI::MandelbrotGUI(QWidget *parent)
    : QMainWindow(parent) {
    
    setWindowTitle("Mandelbrot Set Fractal Generator");
    setGeometry(100, 100, 1400, 900);
    
    // Initialize presets
    presets = {
        {"Standard View", -0.7, 0.0, 1.0, 256},
        {"Spiral Region", -0.8, -0.156, 50.0, 512},
        {"Deep Zoom", -0.747, 0.1107, 100.0, 512},
        {"Very Deep Zoom", -0.7469, 0.1102, 1000.0, 1024},
        {"Seahorse Valley", -0.75, 0.1, 200.0, 768},
        {"Mini Mandelbrot", -0.16, 1.036, 1000.0, 1024}
    };
    
    setupUI();
}

MandelbrotGUI::~MandelbrotGUI() {
}

void MandelbrotGUI::setupUI() {
    // Central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    
    // Left side - Image display
    QVBoxLayout *leftLayout = new QVBoxLayout();
    
    imageLabel = new QLabel();
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setMinimumSize(800, 600);
    imageLabel->setStyleSheet("border: 2px solid #cccccc; background-color: #f0f0f0;");
    imageLabel->setText("Click 'Generate Fractal' to create an image");
    
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(imageLabel);
    scrollArea->setWidgetResizable(true);
    
    leftLayout->addWidget(new QLabel("<b>Fractal Display:</b>"));
    leftLayout->addWidget(scrollArea);
    
    // Status and progress
    progressBar = new QProgressBar();
    progressBar->setVisible(false);
    progressBar->setRange(0, 0); // Indeterminate progress
    
    statusLabel = new QLabel("Ready");
    statusLabel->setStyleSheet("color: #555555; font-size: 10pt;");
    
    leftLayout->addWidget(progressBar);
    leftLayout->addWidget(statusLabel);
    
    // Right side - Controls
    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->setSpacing(15);
    
    // Preset selection
    QGroupBox *presetGroup = new QGroupBox("Preset Regions");
    QVBoxLayout *presetLayout = new QVBoxLayout(presetGroup);
    presetCombo = new QComboBox();
    for (const auto &preset : presets) {
        presetCombo->addItem(preset.name);
    }
    connect(presetCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MandelbrotGUI::onPresetChanged);
    presetLayout->addWidget(presetCombo);
    rightLayout->addWidget(presetGroup);
    
    // Resolution
    QGroupBox *resolutionGroup = new QGroupBox("Image Resolution");
    QGridLayout *resGridLayout = new QGridLayout(resolutionGroup);
    
    resGridLayout->addWidget(new QLabel("Width:"), 0, 0);
    widthSpinBox = new QSpinBox();
    widthSpinBox->setRange(320, 4096);
    widthSpinBox->setValue(1920);
    widthSpinBox->setSingleStep(160);
    resGridLayout->addWidget(widthSpinBox, 0, 1);
    
    resGridLayout->addWidget(new QLabel("Height:"), 1, 0);
    heightSpinBox = new QSpinBox();
    heightSpinBox->setRange(240, 3072);
    heightSpinBox->setValue(1440);
    heightSpinBox->setSingleStep(120);
    resGridLayout->addWidget(heightSpinBox, 1, 1);
    
    rightLayout->addWidget(resolutionGroup);
    
    // Fractal Parameters
    QGroupBox *paramGroup = new QGroupBox("Fractal Parameters");
    QGridLayout *paramGridLayout = new QGridLayout(paramGroup);
    
    paramGridLayout->addWidget(new QLabel("Zoom Level:"), 0, 0);
    zoomSpinBox = new QDoubleSpinBox();
    zoomSpinBox->setRange(0.1, 100000.0);
    zoomSpinBox->setValue(1.0);
    zoomSpinBox->setSingleStep(1.0);
    zoomSpinBox->setDecimals(1);
    paramGridLayout->addWidget(zoomSpinBox, 0, 1);
    
    paramGridLayout->addWidget(new QLabel("Center X:"), 1, 0);
    centerRealSpinBox = new QDoubleSpinBox();
    centerRealSpinBox->setRange(-3.0, 2.0);
    centerRealSpinBox->setValue(-0.7);
    centerRealSpinBox->setSingleStep(0.01);
    centerRealSpinBox->setDecimals(6);
    paramGridLayout->addWidget(centerRealSpinBox, 1, 1);
    
    paramGridLayout->addWidget(new QLabel("Center Y:"), 2, 0);
    centerImagSpinBox = new QDoubleSpinBox();
    centerImagSpinBox->setRange(-2.0, 2.0);
    centerImagSpinBox->setValue(0.0);
    centerImagSpinBox->setSingleStep(0.01);
    centerImagSpinBox->setDecimals(6);
    paramGridLayout->addWidget(centerImagSpinBox, 2, 1);
    
    paramGridLayout->addWidget(new QLabel("Max Iterations:"), 3, 0);
    iterationsSpinBox = new QSpinBox();
    iterationsSpinBox->setRange(16, 4096);
    iterationsSpinBox->setValue(256);
    iterationsSpinBox->setSingleStep(16);
    paramGridLayout->addWidget(iterationsSpinBox, 3, 1);
    
    rightLayout->addWidget(paramGroup);
    
    // Buttons
    QGroupBox *buttonGroup = new QGroupBox("Actions");
    QVBoxLayout *buttonLayout = new QVBoxLayout(buttonGroup);
    
    generateButton = new QPushButton("Generate Fractal");
    generateButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #4CAF50;"
        "  color: white;"
        "  border: none;"
        "  padding: 10px;"
        "  border-radius: 5px;"
        "  font-weight: bold;"
        "  font-size: 12pt;"
        "}"
        "QPushButton:hover {"
        "  background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #3d8b40;"
        "}"
    );
    connect(generateButton, &QPushButton::clicked, this, &MandelbrotGUI::onGenerateClicked);
    buttonLayout->addWidget(generateButton);
    
    openFolderButton = new QPushButton("Open Output Folder");
    openFolderButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #2196F3;"
        "  color: white;"
        "  border: none;"
        "  padding: 8px;"
        "  border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #0b7dda;"
        "}"
    );
    connect(openFolderButton, &QPushButton::clicked, [this]() {
        QString outputDir = QCoreApplication::applicationDirPath();
        outputDir = QDir(outputDir).absoluteFilePath(".");
        QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromStdString(
            outputDir.toStdString()
        )));
    });
    buttonLayout->addWidget(openFolderButton);
    
    rightLayout->addWidget(buttonGroup);
    
    // Add stretch to fill space
    rightLayout->addStretch();
    
    // Add layouts to main layout
    mainLayout->addLayout(leftLayout, 3);
    mainLayout->addLayout(rightLayout, 1);
    
    // Load default image
    loadImage("mandelbrot_standard.png");
}

void MandelbrotGUI::onGenerateClicked() {
    generateButton->setEnabled(false);
    progressBar->setVisible(true);
    statusLabel->setText("Generating fractal...");
    
    // Get parameters from UI
    int width = widthSpinBox->value();
    int height = heightSpinBox->value();
    double zoom = zoomSpinBox->value();
    double centerReal = centerRealSpinBox->value();
    double centerImag = centerImagSpinBox->value();
    int iterations = iterationsSpinBox->value();
    
    // Run generation in a separate thread
    std::thread([this, width, height, zoom, centerReal, centerImag, iterations]() {
        try {
            bool success = draw_mandelbrot(
                "mandelbrot_output.png",
                width,
                height,
                zoom,
                centerReal,
                centerImag,
                iterations
            );
            
            // Update UI in main thread
            QApplication::postEvent(this, new QEvent(QEvent::User), Qt::HighEventPriority);
            
            if (success) {
                statusLabel->setText(QString("✓ Fractal generated successfully! (%1×%2, %3 iterations)")
                    .arg(width).arg(height).arg(iterations));
                loadImage("mandelbrot_output.png");
            } else {
                QMessageBox::critical(this, "Error", "Failed to generate fractal image");
                statusLabel->setText("Error: Failed to generate fractal");
            }
        } catch (const std::exception &e) {
            statusLabel->setText(QString("Error: %1").arg(e.what()));
        }
        
        progressBar->setVisible(false);
        generateButton->setEnabled(true);
    }).detach();
}

void MandelbrotGUI::onPresetChanged(int index) {
    if (index >= 0 && index < presets.size()) {
        const auto &preset = presets[index];
        centerRealSpinBox->setValue(preset.centerReal);
        centerImagSpinBox->setValue(preset.centerImag);
        zoomSpinBox->setValue(preset.zoom);
        iterationsSpinBox->setValue(preset.iterations);
    }
}

void MandelbrotGUI::loadImage(const QString &filename) {
    QPixmap pixmap(filename);
    if (!pixmap.isNull()) {
        // Scale to fit label while maintaining aspect ratio
        QPixmap scaledPixmap = pixmap.scaledToWidth(imageLabel->width() - 10, Qt::SmoothTransformation);
        imageLabel->setPixmap(scaledPixmap);
    } else {
        imageLabel->setText("Image not found: " + filename);
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    MandelbrotGUI window;
    window.show();
    
    return app.exec();
}
