#ifndef HUDDESIGN_H
#define HUDDESIGN_H

#include <QWidget>

namespace Ui {
class HUDDesign;
}

class HUDDesign : public QWidget
{
    Q_OBJECT

public:
    explicit HUDDesign(QWidget *parent = nullptr);
    ~HUDDesign();

private:
    Ui::HUDDesign *ui;
};

#endif // HUDDESIGN_H
