#include "DarkPanel.h"
#include "R.h"

DarkPanel::DarkPanel(QWidget *parent) : TexturePanel(parent)
{
    const int ratio = 4;

    QPixmap cnr = R::GUIPixmap->copy(2, 34, 13, 13);
    cnr = cnr.scaled(cnr.width()*ratio, cnr.height()*ratio);
    this->setCornerPixmap(cnr);

    QPixmap bdr = R::GUIPixmap->copy(2, 47, 13, 13);
    bdr = bdr.scaled(bdr.width()*ratio, bdr.height()*ratio);
    this->setBorderPixmap(bdr);

    QPixmap bkg = R::GUIPixmap->copy(15, 47, 13, 13);
    bkg = bkg.scaled(bkg.width()*ratio, bkg.height()*ratio);
    this->setBackgroundPixmap(bkg);

    const int margin = 7 * ratio;
    layout()->setContentsMargins(margin, margin, margin, margin);
}
