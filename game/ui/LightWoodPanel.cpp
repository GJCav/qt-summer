#include "LightWoodPanel.h"
#include "R.h"
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

LightWoodPanel::LightWoodPanel(QWidget* parent)
    : TexturePanel(parent)
{
    const int ratio = 4;

    QPixmap cnr = R::GUIPixmap->copy(49, 97, 3, 3);
    cnr = cnr.scaled(cnr.width()*ratio, cnr.height()*ratio);
    this->setCornerPixmap(cnr);

    QPixmap bdr = R::GUIPixmap->copy(49, 100, 3, 3);
    bdr = bdr.scaled(bdr.width()*ratio, bdr.height()*ratio);
    this->setBorderPixmap(bdr);

    QPixmap bkg = R::GUIPixmap->copy(52, 100, 3, 3);
    bkg = bkg.scaled(bdr.width()*ratio, bdr.height()*ratio);
    this->setBackgroundPixmap(bkg);
}
