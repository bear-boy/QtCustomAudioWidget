#include "widget.h"
#include "ui_widget.h"
#include <QHBoxLayout>
#include "customslider.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    ui->uiCSlider->setMinimumWidth(582);
//    ui->uiCSlider->setMinimumHeight(22);

}

Widget::~Widget()
{
    delete ui;
}

