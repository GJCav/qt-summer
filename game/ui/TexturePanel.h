#ifndef TEXTUREPANEL_H
#define TEXTUREPANEL_H

#include <QWidget>
#include <QPixmap>
#include <QString>

class TexturePanel : public QWidget
{
    Q_OBJECT
public:
    explicit TexturePanel(QWidget *parent = nullptr);

    const QPixmap &cnrLeftTop() const;
    void setCnrLeftTop(const QPixmap &newCnrLeftTop);
    const QPixmap &cnrRithtTop() const;
    void setCnrRithtTop(const QPixmap &newCnrRithtTop);
    const QPixmap &cnrLeftBottom() const;
    void setCnrLeftBottom(const QPixmap &newCnrLeftBottom);
    const QPixmap &cnrRightBottom() const;
    void setCnrRightBottom(const QPixmap &newCnrRightBottom);
    const QPixmap &bdrTop() const;
    void setBdrTop(const QPixmap &newBdrTop);
    const QPixmap &bdrLeft() const;
    void setBdrleft(const QPixmap &newBdrleft);
    const QPixmap &bdrRight() const;
    void setBdrRight(const QPixmap &newBdrRight);
    const QPixmap &bdrBottom() const;
    void setBdrBottom(const QPixmap &newBdrBottom);
    const QPixmap &backgroundPixmap() const;
    void setBackgroundPixmap(const QPixmap &newBkg);


    // convenience methods
    void setCornerPixmap(const QPixmap &newCnrLeftTop);
    void setBorderPixmap(const QPixmap &newBdrLeft);
    void addWidget(QWidget *widget);

signals:

private:
    QPixmap mCnrLeftTop;
    QPixmap mCnrRightTop;
    QPixmap mCnrLeftBottom;
    QPixmap mCnrRightBottom;
    QPixmap mBdrTop;
    QPixmap mBdrLeft;
    QPixmap mBdrRight;
    QPixmap mBdrBottom;
    QPixmap mBkg;

    int mMarginLeft;
    int mMarginTop;
    int mMarginRight;
    int mMarginBottom;

    void recalculateSize();

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // TEXTUREPANEL_H
