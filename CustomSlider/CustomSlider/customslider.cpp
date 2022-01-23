#include "customslider.h"

CustomSlider::CustomSlider()
{
    if (this->orientation() == Qt::Horizontal) {
        QSizePolicy sliderPolicy = sizePolicy();
        sliderPolicy.transpose();
        setSizePolicy(sliderPolicy);
    }
    setMouseTracking(true);
}

CustomSlider::CustomSlider(QWidget *parent) :
    QSlider(parent)
{
    if (this->orientation() == Qt::Horizontal) {
        QSizePolicy sliderPolicy = sizePolicy();
        sliderPolicy.transpose();
        setSizePolicy(sliderPolicy);
    }
    setMouseTracking(true);
}

QSize CustomSlider::minimumSizeHint() const
{
    return QSize(scHandleSideLength * 2 + scLeftRightMargin * 2, scHandleSideLength);
}

void CustomSlider::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED(pe);

    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();

    QRectF br;
    if (this->orientation() == Qt::Horizontal) {
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

    QRectF handleRect = calcHandleRect(value());
    painter->setBrush(QColor("#ECAB14"));
    painter->drawRoundedRect(handleRect, 1, 1);

    QBrush valueBrush(QColor("#1E90FF"));
    QRectF selectedRect(br);
    if (this->orientation() == Qt::Horizontal) {
        selectedRect.setRight(handleRect.left());
    } else {
        selectedRect.setTop(handleRect.bottom());
    }
    painter->setBrush(valueBrush);
    painter->drawRect(selectedRect);
}

void CustomSlider::mousePressEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton) {
        int posCheck = (this->orientation() == Qt::Horizontal) ? ev->pos().y() :
                                                         ev->pos().x();
        int posMax = (this->orientation() == Qt::Horizontal) ? this->width() :
                                                       this->height();
        int posValue = (this->orientation() == Qt::Horizontal) ? ev->pos().x() :
                                                         ev->pos().y();
        int handlePos = (this->orientation() == Qt::Horizontal) ? calcHandleRect(value()).x() :
                                                          calcHandleRect(value()).y();
        if (calcHandleRect(value()).contains(ev->pos())) {
            handlePressed = true;
            delta = posValue - handlePos - scHandleSideLength / 2;
        }

        if (posCheck >= 2 && posCheck <= posMax - 2) {
            // press event in legal region
            int interval = maximum() - minimum();
            int step = interval / 10 < 1 ? 1 : interval / 10;
            if (posValue < handlePos) {
                if (this->orientation() == Qt::Vertical)
                    setValue(value() + step);
                else
                    setValue(value() - step);
            } else if (posValue > handlePos + scHandleSideLength) {
                if (this->orientation() == Qt::Vertical)
                    setValue(value() - step);
                else
                    setValue(value() + step);
            }
        }
    }
}

void CustomSlider::mouseMoveEvent(QMouseEvent *ev)
{
    if (ev->buttons() & Qt::LeftButton) {
        int posValue = (this->orientation() == Qt::Horizontal) ? ev->pos().x() :
                                                         ev->pos().y();
        int len = (this->orientation() == Qt::Horizontal) ? width() : height();
        int validSection = len - scHandleSideLength - 2*scLeftRightMargin;
        int interval = maximum() - minimum();
        int transValue;
        if (this->orientation() == Qt::Vertical) {
            transValue = maximum() - (posValue - delta - scLeftRightMargin - scHandleSideLength / 2)
                                      * 1.0 / validSection * interval;
        } else {
            transValue = minimum() + (posValue - delta - scLeftRightMargin - scHandleSideLength / 2)
                                     * 1.0 / validSection * interval;
        }
        if (handlePressed) {
            setValue(transValue);
        }
    }
}

void CustomSlider::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    handlePressed = false;
}

QRectF CustomSlider::calcHandleRect(int val)
{
    float percentage = (val - minimum()) * 1.0 / (maximum() - minimum());
    int len = this->orientation() == Qt::Orientation::Horizontal ? this->width() : this->height();
    int validSection = len - this->scHandleSideLength - 2*this->scLeftRightMargin;
    int position = validSection * percentage;
    if (this->orientation() == Qt::Orientation::Horizontal) {
         return QRectF(position + scLeftRightMargin, (height() - this->scHandleSideLength)/2,
                         this->scHandleSideLength, this->scHandleSideLength);
    } else {
         return QRectF((width() - this->scHandleSideLength)/2, validSection - position + scLeftRightMargin,
                       this->scHandleSideLength, this->scHandleSideLength);
    }
}
