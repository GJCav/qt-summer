#ifndef LIGHTDARKPANEL_H
#define LIGHTDARKPANEL_H

#include "TexturePanel.h"
#include <QWidget>

class LightDarkPanel : public TexturePanel
{
    Q_OBJECT
public:
    LightDarkPanel(QWidget *parent = nullptr);
};

#endif // LIGHTDARKPANEL_H
