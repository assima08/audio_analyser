//
// Created by faba on 2026-04-28.
//

#ifndef AUDIOANALYSER_WAVEFORMWIDGET_H
#define AUDIOANALYSER_WAVEFORMWIDGET_H
#include "QWidget"
#include "vector"

class WaveformWidget : public QWidget{
public:
    explicit WaveformWidget(QWidget* parent = nullptr);
    void setSamples(const std::vector<double>& samples);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<double> samples;
};


#endif //AUDIOANALYSER_WAVEFORMWIDGET_H
