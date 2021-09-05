#include "TestWindow.h"
#include "ui_TestWindow.h"
#include "ui/LightWoodPanel.h"

TestWindow::TestWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    ui->tp->addWidget(new QPushButton("asdf"));
    ui->tp->addWidget(new QPushButton("5555"));

    ui->ld->layout()->addWidget(new LightWoodPanel);
    ui->ld->layout()->addWidget(new LightDarkPanel);
}

TestWindow::~TestWindow()
{
    delete ui;
}
