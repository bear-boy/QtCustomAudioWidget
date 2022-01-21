#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QWidget>
#include <QSlider>
#include <QPainter>

class CustomSlider : public QSlider
{
public:
    CustomSlider();
    CustomSlider(QWidget *parent) : QSlider(parent) {}
    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation getOrientation();

protected:
    void paintEvent(QPaintEvent *pe) override;

private:
    const int scHandleSideLength = 11;
    const int scSliderBarHeight = 5;
    const int scLeftRightMargin = 8;
    Qt::Orientation orientation = Qt::Orientation::Vertical;

    QRectF calcHandleRect(int val);
};

#endif // CUSTOMSLIDER_H
