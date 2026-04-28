//
// Created by faba on 2026-04-28.
//

#include "MainWindow.h"
#include "AudioReader.h"
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent) {

    setWindowTitle("Audio Analyser");
    resize(900, 300);

    // charger le fichier audio
    AudioReader reader("C:/Users/faba/Documents/portefolio/audioAnalyser/91BPM_DMaj_BRKTHRU_Horn_Loop.wav");
    reader.load();

    // widget central
    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);

    QLabel* label = new QLabel(
            QString("Sample Rate: %1 Hz  |  Channels: %2  |  Frames: %3")
                    .arg(reader.getSampleRate())
                    .arg(reader.getChannels())
                    .arg(reader.getNumFrames())
    );
    label->setStyleSheet("color: white; background: #1e1e1e; padding: 5px;");

    waveformWidget = new WaveformWidget(this);
    waveformWidget->setSamples(reader.getSamples());

    layout->addWidget(label);
    layout->addWidget(waveformWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setCentralWidget(central);
    setStyleSheet("background-color: #1e1e1e;");
}