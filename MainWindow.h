#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WaveformWidget.h"

class QLabel;

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void ouvrirFichier();

private:
    WaveformWidget* waveformWidget;
    QLabel*         infoLabel;
};

#endif