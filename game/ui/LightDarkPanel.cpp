#include "LightDarkPanel.h"
#include "R.h"

#include <QtWidgets>
#include <QtGui>

LightDarkPanel::LightDarkPanel(QWidget* parent) : TexturePanel(parent)
{
    const int ratio = 4;

    QPixmap cnrLT = R::GUIPixmap->copy(81, 97, 6, 6);
    cnrLT = cnrLT.scaled(cnrLT.width()*ratio, cnrLT.height()*ratio);
    this->setCnrLeftTop(cnrLT);

    QPixmap cnrRT = R::GUIPixmap->copy(105, 97, 6, 6);
    cnrRT = cnrRT.scaled(cnrRT.width()*ratio, cnrRT.height()*ratio);
    this->setCnrRithtTop(cnrRT);

    QPixmap cnrLB = R::GUIPixmap->copy(81, 121, 6, 6);
    cnrLB = cnrLB.scaled(cnrLB.width()*ratio, cnrLB.height()*ratio);
    this->setCnrLeftBottom(cnrLB);

    QPixmap cnrRB = R::GUIPixmap->copy(105, 121, 6, 6);
    cnrRB = cnrRB.scaled(cnrRB.width()*ratio, cnrRB.height()*ratio);
    this->setCnrRightBottom(cnrRB);

    QPixmap bdr = R::GUIPixmap->copy(81, 103, 6, 6);
    bdr = bdr.scaled(bdr.width()*ratio, bdr.height()*ratio);
    this->setBorderPixmap(bdr);

    QPixmap bkg = R::GUIPixmap->copy(87, 103, 6, 6);
    bkg = bkg.scaled(bkg.width()*ratio, bkg.height()*ratio);
    this->setBackgroundPixmap(bkg);
}
