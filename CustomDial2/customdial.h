#ifndef CUSTOMDIAL_H
#define CUSTOMDIAL_H

#include <QWidget>
#include <QDial>
#include <QPainter>
#include <qmath.h>
#include <QSlider>
#include <QStyleOptionSlider>

class CustomDial : public QDial
{
public:
    CustomDial();
    CustomDial(QWidget *widget);

    void setValueColor(QColor val);
    QColor getValueColor();
    void setDialColor(QColor val);
    QColor getDialColor();

protected:
    void paintEvent(QPaintEvent *pe) override;

private:
    QColor valueColor = QColor(0,153,0,255);
    QColor dialColor = QColor(48,62,81);
};

#endif // CUSTOMDIAL_H
