#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextToSpeech>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_browseButton_clicked();

    void on_readButton_clicked();

    void on_pauseButton_clicked();

    void on_stopButton_clicked();

    void on_volumeSlider_valueChanged(int value);

    void on_pitchSlider_valueChanged(int value);

    void on_rateSlider_valueChanged(int value);

    void on_resetVolumeButton_clicked();

    void on_resetPitchButton_clicked();

    void on_resetRateButton_clicked();

    void on_localesCombo_currentTextChanged(const QString &arg1);

    void on_voicesCombo_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QTextToSpeech *textToSpeech;
    QString text;
    bool paused = false;
    double defaultVolume;
};
#endif // MAINWINDOW_H
