#include "MainWindow.h"
#include "AudioReader.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent) {

    setWindowTitle("Audio Analyser");
    resize(900, 350);
    setStyleSheet("background-color: #1e1e1e; color: white;");

    QWidget*     central = new QWidget(this);
    QVBoxLayout* layout  = new QVBoxLayout(central);

    // barre du haut : bouton + infos
    QHBoxLayout* topBar = new QHBoxLayout();

    QPushButton* bouton = new QPushButton("Ouvrir un fichier WAV", this);
    bouton->setStyleSheet(
            "QPushButton {"
            "  background-color: #00d4ff; color: #1e1e1e;"
            "  border: none; padding: 8px 16px; font-weight: bold;"
            "}"
            "QPushButton:hover { background-color: #00a8cc; }"
    );

    infoLabel = new QLabel("Aucun fichier chargé", this);
    infoLabel->setStyleSheet("color: #aaaaaa; padding-left: 12px;");

    topBar->addWidget(bouton);
    topBar->addWidget(infoLabel);
    topBar->addStretch();

    // waveform
    waveformWidget = new WaveformWidget(this);

    layout->addLayout(topBar);
    layout->addWidget(waveformWidget);
    layout->setContentsMargins(10, 10, 10, 10);
    layout->setSpacing(10);

    setCentralWidget(central);

    connect(bouton, &QPushButton::clicked, this, &MainWindow::ouvrirFichier);
}

void MainWindow::ouvrirFichier() {
    QString chemin = QFileDialog::getOpenFileName(
            this,
            "Ouvrir un fichier audio",
            QString(),
            "Fichiers WAV (*.wav)"
    );

    if (chemin.isEmpty()) return;

    AudioReader reader(chemin.toStdString());
    if (!reader.load()) {
        infoLabel->setText("Erreur : fichier invalide");
        return;
    }

    infoLabel->setText(
            QString("Sample Rate: %1 Hz  |  Channels: %2  |  Frames: %3")
                    .arg(reader.getSampleRate())
                    .arg(reader.getChannels())
                    .arg(reader.getNumFrames())
    );

    waveformWidget->setSamples(reader.getSamples());
}