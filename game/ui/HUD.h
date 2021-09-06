#ifndef HUD_H
#define HUD_H

#include <QWidget>
#include <QLabel>
#include <QVector>

namespace Ui {
class HUD;
}

class HUD : public QWidget
{
    Q_OBJECT

public:
    explicit HUD(QWidget *parent = nullptr);
    ~HUD();

    void setIcons(const QVector<QPixmap*> list);

    static QLabel* createIconLabel(const QPixmap& icon);


private:
    Ui::HUD *ui;
};

#endif // HUD_H
