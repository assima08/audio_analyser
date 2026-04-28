//
// Created by faba on 2026-04-28.
//

#ifndef AUDIOANALYSER_MAINWINDOW_H
#define AUDIOANALYSER_MAINWINDOW_H

#include <QMainWindow>
#include "WaveformWidget.h"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    WaveformWidget* waveformWidget;
};



#endif //AUDIOANALYSER_MAINWINDOW_H
