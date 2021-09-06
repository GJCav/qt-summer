#include "HUDDesign.h"
#include "ui_HUDDesign.h"

HUDDesign::HUDDesign(QWidget *parent) :
QWidget(parent),
ui(new Ui::HUDDesign)
{
    ui->setupUi(this);
}

HUDDesign::~HUDDesign()
{
    delete ui;
}
