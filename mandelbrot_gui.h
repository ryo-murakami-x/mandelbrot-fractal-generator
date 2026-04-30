#ifndef MANDELBROT_GUI_H
#define MANDELBROT_GUI_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QProgressBar>

class MandelbrotGUI : public QMainWindow {
    Q_OBJECT

public:
    MandelbrotGUI(QWidget *parent = nullptr);
    ~MandelbrotGUI();

private slots:
    void onGenerateClicked();
    void onPresetChanged(int index);
    void updatePresetValues();

private:
    void setupUI();
    void createMenuBar();
    void loadImage(const QString &filename);

    // UI Components
    QLabel *imageLabel;
    QPushButton *generateButton;
    QPushButton *openFolderButton;
    QComboBox *presetCombo;
    
    // Parameter controls
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QDoubleSpinBox *zoomSpinBox;
    QDoubleSpinBox *centerRealSpinBox;
    QDoubleSpinBox *centerImagSpinBox;
    QSpinBox *iterationsSpinBox;
    
    QProgressBar *progressBar;
    QLabel *statusLabel;

    // Current parameters
    struct PresetRegion {
        QString name;
        double centerReal;
        double centerImag;
        double zoom;
        int iterations;
    };
    
    QVector<PresetRegion> presets;
};

#endif // MANDELBROT_GUI_H
