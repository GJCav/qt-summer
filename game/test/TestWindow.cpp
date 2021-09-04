#include "TestWindow.h"
#include "ui_TestWindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    ui->tp->addWidget(new QPushButton("asdf"));
    ui->tp->addWidget(new QPushButton("5555"));
}

TestWindow::~TestWindow()
{
    delete ui;
}
