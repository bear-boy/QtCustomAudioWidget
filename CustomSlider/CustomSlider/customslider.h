#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QSlider>
#include <QPainter>
#include <QMouseEvent>
#include <QSizePolicy>

class CustomSlider : public QSlider
{
public:
    CustomSlider();
    CustomSlider(QWidget *parent);
    QSize minimumSizeHint() const override;

protected:
    void paintEvent(QPaintEvent *pe) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

private:
    const int scHandleSideLength = 11;
    const int scSliderBarHeight = 5;
    const int scLeftRightMargin = 8;
    int delta;
    bool handlePressed = false;
    QRectF calcHandleRect(int val);
};

#endif // CUSTOMSLIDER_H
