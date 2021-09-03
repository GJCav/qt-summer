#include "util/QPixmapGirdSplitter.h"
#include "util/QPixmapAutoSplitter.h"
#include "util/QPixmapFileSeq.h"

#include <QApplication>
#include <QtCore>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmapFileSeq seq(":/picture/asset/Meow Knight/blue-idle", 1, 7, ".png");
    seq.preview()->show();

    return a.exec();
}
