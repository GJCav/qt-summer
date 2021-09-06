#include "HUD.h"
#include "ui_HUD.h"
#include "R.h"
#include <QtGui>

HUD::HUD(QWidget *parent) :
QWidget(parent),
ui(new Ui::HUD)
{
    ui->setupUi(this);
}

HUD::~HUD()
{
    delete ui;
}

void HUD::setIcons(const QVector<QPixmap *> list)
{
    QBoxLayout *lyt = static_cast<QBoxLayout*>(ui->iconBar->layout());
    while(lyt->count()){
        auto child = lyt->takeAt(lyt->count()-1);
        delete child->widget();
        delete child;
    }
    foreach(QPixmap *pix, list){
        auto label = createIconLabel(*pix);
        lyt->addWidget(label);
    }
    lyt->addStretch(1);
}

QLabel *HUD::createIconLabel(const QPixmap& icon)
{
    QLabel *label = new QLabel();
    qDebug() << label->size();
    label->setContentsMargins(0, 0, 0, 0);
    icon.scaled(label->size(), Qt::KeepAspectRatio);
    //label->setScaledContents(true);
    label->setPixmap(icon);
    return label;
}
