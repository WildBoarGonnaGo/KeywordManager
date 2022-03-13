#include "mainwindow.h"
#include <memory>
#include <QLabel>
#include <QPixmap>
#include <QSize>
#include <QHBoxLayout>
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *widget) : QWidget(widget) {
    QPixmap tmpAbcPixmap(":/KeywordManager/abc_icon.png");
    abcPixmap = make_unique<QPixmap>(tmpAbcPixmap.scaled(14, 14, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    abcIcon = make_unique<QIcon>(*abcPixmap);

    setFixedSize(1024, 768);
    setWindowTitle("Диспетчер из списка ключевых слов");
    setWindowIcon(*abcIcon);
    keywordListWidget = make_unique<KeywordListWidget>(this);

    mainVBox = make_unique<QVBoxLayout>();
    mainVBox->addWidget(keywordListWidget.get());

    //qDebug() << "keywordListWidget width :" << keywordListWidget->width();
    //qDebug() << "keywordListWidget height: " << keywordListWidget->height();

    setLayout(mainVBox.get());
}
