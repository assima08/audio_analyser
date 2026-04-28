//
// Created by faba on 2026-04-28.
//

#include "WaveformWidget.h"
#include <QPainter>

WaveformWidget::WaveformWidget(QWidget* parent)
        : QWidget(parent) {
    setMinimumSize(800, 200);
    setStyleSheet("background-color: #1e1e1e;");
}

void WaveformWidget::setSamples(const std::vector<double>& s) {
    samples = s;
    update(); // redessine le widget
}

void WaveformWidget::paintEvent(QPaintEvent*) {
    if (samples.empty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor("#00d4ff"), 1));

    int w = width();
    int h = height();
    int mid = h / 2;

    // on sous-échantillonne pour ne pas dessiner 1M de points
    size_t step = std::max((size_t)1, samples.size() / (size_t)w);

    for (int x = 0; x < w - 1; x++) {
        size_t i1 = x * step;
        size_t i2 = (x + 1) * step;

        if (i2 >= samples.size()) break;

        int y1 = mid - static_cast<int>(samples[i1] * mid);
        int y2 = mid - static_cast<int>(samples[i2] * mid);

        painter.drawLine(x, y1, x + 1, y2);
    }
}
