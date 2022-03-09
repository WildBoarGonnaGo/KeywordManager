#include "mainwindow.h"
#include <memory>
#include <QLabel>
#include <QPixmap>
#include <QSize>

MainWindow::MainWindow(QWidget *widget) : icon(make_unique<QIcon>(":/KeywordManager/abc_icon.png")),
    stdItemModel(make_unique<QStandardItemModel>(1, 4)),
    user_document_icon(make_unique<QIcon>(":/KeywordManager/document_user.png"))
    //list(QList<QMap<QString, QVariant> >()),
    //plus_icon(make_shared<QIcon>(":/KeywordManager/plus_icon.png")),
    //listWidget(QListWidget())
{
    setFixedSize(1024, 768);
    setWindowTitle("Диспетчер списков ключевых слов");
    setWindowIcon(*icon);
    setVisible(true);

    //QListWidget listWidget;
    //addListMap["checkIcon"] = move(*plus_icon);
    //addListMap["text"] = QLabel("Введите имя нового списка");
    addLink = make_unique<QLabel>(QString("<a href = \"\">Введите имя нового списка<\a>"));
    QPixmap bigTmp(":/KeywordManager/plus_icon.png");
    QPixmap scaledTmp = bigTmp.scaled(QSize(10, 10), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    plus_icon = make_shared<QIcon>(scaledTmp);
    plusIconItem = make_unique<QStandardItem>(*plus_icon, "");
    plusTextItem = make_unique<QStandardItem>("<a href = \"\">Введите имя нового списка<\a>");
    //listWidget.addItem(plusIconItem.get());
    //listWidget.addItem(plusTextItem.get());
    //listWidget.setItemWidget(plusTextItem.get(), addLink.get());

    stdItemModel->setItem(0, 0, plusIconItem.get());
    stdItemModel->setItem(0, 1, plusTextItem.get());

    tableView = make_unique<QTableView>(stdItemModel.get());

}

void    MainWindow::addList(const QMap<QString, QVariant> &item) {

}
