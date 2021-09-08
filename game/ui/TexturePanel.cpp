#include "TexturePanel.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

TexturePanel::TexturePanel(QWidget *parent) : QWidget(parent)
{
    //this->setLayout(new QVBoxLayout);
    auto p = this->palette();
    p.setColor(QPalette::Window, QColor(0, 0, 0, 0));
    this->setPalette(p);
}

const QPixmap &TexturePanel::cnrLeftTop() const
{
    return mCnrLeftTop;
}

void TexturePanel::setCnrLeftTop(const QPixmap &newCnrLeftTop)
{
    if(&mCnrLeftTop == &newCnrLeftTop) return;
    mCnrLeftTop = newCnrLeftTop;
    recalculateSize();
}

const QPixmap &TexturePanel::cnrRithtTop() const
{
    return mCnrRightTop;
}

void TexturePanel::setCnrRithtTop(const QPixmap &newCnrRithtTop)
{
    if(&mCnrRightTop == &newCnrRithtTop) return;
    mCnrRightTop = newCnrRithtTop;
    recalculateSize();
}

const QPixmap &TexturePanel::cnrLeftBottom() const
{
    return mCnrLeftBottom;
}

void TexturePanel::setCnrLeftBottom(const QPixmap &newCnrLeftBottom)
{
    if(&mCnrLeftBottom == &newCnrLeftBottom) return;
    mCnrLeftBottom = newCnrLeftBottom;
    recalculateSize();
}

const QPixmap &TexturePanel::cnrRightBottom() const
{
    return mCnrRightBottom;
}

void TexturePanel::setCnrRightBottom(const QPixmap &newCnrRightBottom)
{
    if(&mCnrRightBottom == &newCnrRightBottom) return;
    mCnrRightBottom = newCnrRightBottom;
    recalculateSize();
}

const QPixmap &TexturePanel::bdrTop() const
{
    return mBdrTop;
}

void TexturePanel::setBdrTop(const QPixmap &newBdrTop)
{
    if(&mBdrTop == &newBdrTop) return;
    mBdrTop = newBdrTop;
    recalculateSize();
}

const QPixmap &TexturePanel::bdrLeft() const
{
    return mBdrLeft;
}

void TexturePanel::setBdrleft(const QPixmap &newBdrleft)
{
    if(&mBdrLeft == &newBdrleft) return;
    mBdrLeft = newBdrleft;
    recalculateSize();
}

const QPixmap &TexturePanel::bdrRight() const
{
    return mBdrRight;
}

void TexturePanel::setBdrRight(const QPixmap &newBdrRight)
{
    if(&mBdrRight == &newBdrRight) return;
    mBdrRight = newBdrRight;
    recalculateSize();
}

const QPixmap &TexturePanel::bdrBottom() const
{
    return mBdrBottom;
}

void TexturePanel::setBdrBottom(const QPixmap &newBdrBottom)
{
    if(&mBdrBottom == &newBdrBottom) return;
    mBdrBottom = newBdrBottom;
    recalculateSize();
}

const QPixmap &TexturePanel::backgroundPixmap() const
{
    return mBkg;
}

void TexturePanel::setBackgroundPixmap(const QPixmap &newBkg)
{
    if(&mBkg == &newBkg) return;
    mBkg = newBkg;
    recalculateSize();
}

void TexturePanel::setCornerPixmap(const QPixmap &newCnr)
{
    mCnrLeftTop = newCnr;
    QTransform t;
    t.rotate(90);
    mCnrRightTop = newCnr.transformed(t);
    t.rotate(90);
    mCnrRightBottom = newCnr.transformed(t);
    t.rotate(90);
    mCnrLeftBottom = newCnr.transformed(t);
    recalculateSize();
}

void TexturePanel::setBorderPixmap(const QPixmap &newBdr)
{
    mBdrLeft = newBdr;
    QTransform t;
    t.rotate(90);
    mBdrTop = newBdr.transformed(t);
    t.rotate(90);
    mBdrRight = newBdr.transformed(t);
    t.rotate(90);
    mBdrBottom = newBdr.transformed(t);
}


void TexturePanel::recalculateSize()
{
    // minimum size
    const int minTopSize = mCnrLeftTop.width()+mCnrRightTop.width();
    const int minBtnSize = mCnrLeftBottom.width()+mCnrRightBottom.width();
    const int minHSize = qMax(minTopSize, minBtnSize);
    const int minLeftSize = mCnrLeftTop.height()+mCnrLeftBottom.height();
    const int minRightSize = mCnrRightTop.height()+mCnrRightBottom.height();
    const int minVSize = qMax(minLeftSize, minRightSize);
    setMinimumWidth(minHSize);
    setMinimumHeight(minVSize);

    // layout margins
    mMarginLeft = qMax(mCnrLeftTop.width(), mCnrLeftBottom.width());
    mMarginTop = qMax(mCnrLeftTop.height(), mCnrRightTop.height());
    mMarginRight = qMax(mCnrRightTop.width(), mCnrRightBottom.width());
    mMarginBottom = qMax(mCnrLeftBottom.height(), mCnrRightBottom.width());
    //auto lyt = layout();
    //lyt->setContentsMargins(mMarginLeft, mMarginTop, mMarginRight, mMarginBottom);

    updateGeometry();
    update();
}

void TexturePanel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    auto area = rect();
    painter.drawPixmap(0, 0, mCnrLeftTop);
    painter.drawPixmap(area.width()-mCnrRightTop.width(), 0, mCnrRightTop);
    painter.drawPixmap(0, area.height()-mCnrLeftBottom.height(), mCnrLeftBottom);
    painter.drawPixmap(area.width()-mCnrRightBottom.width(), area.height()-mCnrRightBottom.height(), mCnrRightBottom);

    QBrush brush;

    brush.setTexture(mBkg);
    painter.setBrush(brush);
    painter.drawRect(
        mMarginLeft,
        mMarginTop,
        area.width()-mMarginLeft-mMarginRight,
        area.height()-mMarginTop-mMarginBottom
    );

    brush.setTexture(mBdrLeft);
    painter.setBrush(brush);
    painter.drawRect(
        0,
        mMarginTop,
        mMarginLeft,
        area.height()-mMarginTop-mMarginBottom
    );

    brush.setTexture(mBdrTop);
    painter.setBrush(brush);
    painter.drawRect(
                mCnrLeftTop.width(),
                0,
                area.width()-mCnrLeftTop.width()-mCnrRightTop.width(),
                mMarginTop
            );

    painter.save();
    brush.setTexture(mBdrRight);
    painter.setBrush(brush);
    painter.setBrushOrigin(area.width()-mMarginRight, mMarginTop);
    painter.drawRect(
        area.width()-mMarginRight,
        mMarginTop,
        mMarginRight,
        area.height()-mMarginTop-mMarginBottom
    );
    painter.restore();


    painter.save();
    brush.setTexture(mBdrBottom);
    painter.setBrush(brush);
    painter.setBrushOrigin(mMarginLeft, area.height()-mMarginBottom);
    painter.drawRect(
        mMarginLeft,
        area.height()-mMarginBottom,
        area.width()-mMarginLeft-mMarginRight,
        mMarginBottom
    );
    painter.restore();


//    QBrush redBrush(Qt::red);
//    painter.setBrush(redBrush);
//    painter.drawEllipse(mMarginLeft - 3, mMarginTop - 3, 6, 6);
//    painter.drawEllipse(area.width() - mMarginRight - 3, mMarginTop - 3, 6, 6);
//    painter.drawEllipse(mMarginLeft - 3, area.height()-mMarginBottom-3, 6, 6);
//    painter.drawEllipse(area.width() - mMarginRight - 3, area.height()-mMarginBottom-3, 6, 6);
}























