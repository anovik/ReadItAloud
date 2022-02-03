#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textToSpeech = new QTextToSpeech();

    setFixedSize(800, 260);

    QVector<QLocale> locales = textToSpeech->availableLocales();
    QVector<QVoice> voices = textToSpeech->availableVoices();

    // fill combos with locales and voices    
    foreach (const QLocale& l, locales) {
        ui->localesCombo->addItem(l.name());
    }

    defaultVolume = textToSpeech->volume();
    ui->volumeSlider->setValue(defaultVolume * 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_browseButton_clicked()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, "Open text file", "directoryToOpen",
            "Text files (*.txt)");

    ui->lineEdit->setText(fileName);

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&file);
    in.setCodec("UTF-8");
    text = in.readAll();
    file.close();
}


void MainWindow::on_readButton_clicked()
{
    textToSpeech->say(text);
    ui->pauseButton->setText("Pause");
    paused = false;
}


void MainWindow::on_pauseButton_clicked()
{
    if (paused)
    {
        ui->pauseButton->setText("Pause");
        textToSpeech->resume();
        paused = false;
    }
    else
    {
        ui->pauseButton->setText("Resume");
        textToSpeech->pause();
        paused = true;
    }
}


void MainWindow::on_stopButton_clicked()
{
    textToSpeech->stop();
}


void MainWindow::on_volumeSlider_valueChanged(int value)
{
    textToSpeech->setVolume(double(value) / 100);
}


void MainWindow::on_pitchSlider_valueChanged(int value)
{
    textToSpeech->setPitch(double(value) / 100);
}


void MainWindow::on_rateSlider_valueChanged(int value)
{
    textToSpeech->setRate(double(value) / 100);
}


void MainWindow::on_resetVolumeButton_clicked()
{
  ui->volumeSlider->setValue(defaultVolume * 100);
}


void MainWindow::on_resetPitchButton_clicked()
{
    ui->pitchSlider->setValue(0);
}


void MainWindow::on_resetRateButton_clicked()
{
    ui->rateSlider->setValue(0);
}


void MainWindow::on_localesCombo_currentTextChanged(const QString &localeName)
{
    textToSpeech->setLocale(QLocale(localeName));

    ui->voicesCombo->clear();

    QVector<QVoice> voices = textToSpeech->availableVoices();

    foreach (const QVoice& v, voices) {
        ui->voicesCombo->addItem(v.name());
    }
}


void MainWindow::on_voicesCombo_currentTextChanged(const QString &voiceName)
{
    QVector<QVoice> voices = textToSpeech->availableVoices();
    foreach (const QVoice& v, voices) {
        if (v.name() == voiceName){
            textToSpeech->setVoice(v);
            return;
        }
    }
}

