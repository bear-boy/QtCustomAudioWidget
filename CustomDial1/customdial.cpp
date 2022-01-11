#include "customdial.h"

static const qreal Q_PI   = qreal(M_PI);     // pi

CustomDial::CustomDial()
{

}

CustomDial::CustomDial(QWidget *widget)
{
    Q_UNUSED(widget);
}

void CustomDial::setValueColor(QColor val)
{
    this->valueColor = val;
}

QColor CustomDial::getValueColor()
{
    return this->valueColor;
}

void CustomDial::setDialColor(QColor val)
{
    this->dialColor = val;
}

QColor CustomDial::getDialColor()
{
    return this->dialColor;
}

static QPointF calcRadialPos(const QStyleOptionSlider *dial, QRectF rectF, qreal offset)
{
    const int width = dial->rect.width();
    const int height = dial->rect.height();
    const int r = qMin(rectF.width(), rectF.height()) / 2;
    const int currentSliderPosition = dial->upsideDown ? dial->sliderPosition : (dial->maximum - dial->sliderPosition);
    qreal a = 0;
    if (dial->maximum == dial->minimum)
        a = Q_PI / 2;
    else if (dial->dialWrapping)
        a = Q_PI * 3 / 2 - (currentSliderPosition - dial->minimum) * 2 * Q_PI
            / (dial->maximum - dial->minimum);
    else
        a = (Q_PI * 8 - (currentSliderPosition - dial->minimum) * 10 * Q_PI
            / (dial->maximum - dial->minimum)) / 6;
    qreal xc = width / 2.0;
    qreal yc = height / 2.0;
    qreal len = r;
    qreal back = offset * len;
    QPointF pos(QPointF(xc + back * qCos(a), yc - back * qSin(a)));
    return pos;
}

static int calcArcAngle(const QStyleOptionSlider *dial)
{
    qreal a = 0;
    const int currentSliderPosition = dial->upsideDown ? dial->sliderPosition : (dial->maximum - dial->sliderPosition);
    if (dial->maximum == dial->minimum)
        a = Q_PI / 2;
    else if (dial->dialWrapping)
        a = Q_PI * 3 / 2 - (currentSliderPosition - dial->minimum) * 2 * Q_PI
            / (dial->maximum - dial->minimum);
    else
        a = (Q_PI * 8 - (currentSliderPosition - dial->minimum) * 10 * Q_PI
            / (dial->maximum - dial->minimum)) / 6;
    qreal deg = qRadiansToDegrees(a);
    if (deg > 0)
        return qCeil(deg);
    else
        return qFloor(deg);
}

void CustomDial::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED(pe);

    QPainter *painter = new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing);

    QStyleOptionSlider option;
    initStyleOption(&option);

    const int width = this->rect().width();
    const int height = this->rect().height();
    qreal r = qMin(width, height) / 2;

    const qreal d_ = r / 6;
    const qreal penSize = r/20.0;
    const qreal dx = this->rect().x() + d_ + (width - 2 * r) / 2 + 1;
    const qreal dy = this->rect().y() + d_ + (height - 2 * r) / 2 + 1;
    QRectF br = QRectF(dx + 0.5, dy + 0.5,
                       int(r * 2 - 2 * d_ - 2),
                       int(r * 2 - 2 * d_ - 2));
    painter->setPen(QPen(QColor(64,64,64),penSize*1.4));
    painter->drawArc(br, -60*16, 300*16);

    // inner solid circle
    qreal circleX = br.center().x();
    qreal circleY = br.center().y();
    qreal circleWidth = br.width()*0.8;
    qreal circleHeight = br.height()*0.8;
    QRectF brCircle = QRectF(circleX - circleWidth/2,
                             circleY - circleHeight/2,
                             circleWidth,
                             circleHeight);

    painter->setPen(QPen(QColor(48,62,81).lighter(120),penSize));
    QRadialGradient solidCircle(brCircle.center().x(),
                                brCircle.center().y(),
                                brCircle.width()/2,
                                brCircle.center().x(),
                                brCircle.center().y());
    solidCircle.setColorAt(0, QColor(48,62,81).lighter(110));
    solidCircle.setColorAt(0.5,QColor(48,62,81));
    solidCircle.setColorAt(1.0,QColor(48,62,81).lighter(115));
    painter->setBrush(solidCircle);
    painter->drawEllipse(brCircle);

    // outer hollow circle
    qreal hollowCircleWidth = circleWidth*0.96;
    qreal hollowCircleHeight = circleHeight*0.96;
    QRectF brHollowCircle = QRectF(circleX - hollowCircleWidth/2,
                                   circleY - hollowCircleHeight/2,
                                   hollowCircleWidth,
                                   hollowCircleHeight);
    painter->setPen(QPen(QColor(224,224,224).darker(105),penSize*0.6));
    painter->drawEllipse(brHollowCircle);

    // pointer(line)
    painter->setPen(QPen(this->valueColor,penSize*1.4));
    painter->drawLine(calcRadialPos(&option, brHollowCircle, qreal(0.65)),
                      calcRadialPos(&option, brHollowCircle, qreal(0.912)));

    // outer arc
    int arcDegree = calcArcAngle(&option);
    if (this->value() != this->minimum()) {
        painter->setPen(QPen(this->valueColor,penSize*1.4));
        painter->drawArc(br, 240*16, (arcDegree-240)*16);
    }
}
