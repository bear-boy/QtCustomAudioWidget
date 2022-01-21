#include "customslider.h"

CustomSlider::CustomSlider()
{

}

void CustomSlider::setOrientation(Qt::Orientation orientation)
{
    this->orientation = orientation;
}

Qt::Orientation CustomSlider::getOrientation()
{
    return this->orientation;
}

void CustomSlider::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED(pe);

    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);

    const int width = this->width();
    const int height = this->height();

    QRectF br;
    if (this->orientation == Qt::Horizontal) {
        br = QRectF(scLeftRightMargin, (height - scSliderBarHeight) / 2,
                    width - scLeftRightMargin * 2, scSliderBarHeight);
    } else{
        br = QRectF((width - scSliderBarHeight) / 2, scLeftRightMargin,
                    scSliderBarHeight, height - scLeftRightMargin*2);
    }
    QPen pen(Qt::black);
    painter->setPen(pen);
    painter->setBrush(QColor("#525252"));
    painter->drawRoundedRect(br, 1, 1);

    QRectF handleRect = calcHandleRect(99);
    painter->setBrush(QColor("#ECAB14"));
    painter->drawRoundedRect(handleRect, 1, 1);
}

QRectF CustomSlider::calcHandleRect(int val)
{
    float percentage = (val - this->minimum()) * 1.0 / (this->maximum() - this->minimum());
    int len = this->orientation == Qt::Orientation::Horizontal ? this->width() : this->height();
    int validSection = len - this->scHandleSideLength - 2*this->scLeftRightMargin;
    int position = validSection * percentage;
    if (this->orientation == Qt::Orientation::Horizontal) {
         return QRectF(position + scLeftRightMargin, (height() - this->scHandleSideLength)/2,
                         this->scHandleSideLength, this->scHandleSideLength);
    } else {
         return QRectF((width() - this->scHandleSideLength)/2, validSection - position + scLeftRightMargin,
                       this->scHandleSideLength, this->scHandleSideLength);
    }
}
