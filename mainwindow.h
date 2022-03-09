#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QIcon>
#include <memory>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QList>
#include <QImage>
#include <QListWidgetItem>
#include <QLabel>
#include <QTableView>

using std::unique_ptr;
using std::make_unique;
using std::make_shared;
using std::shared_ptr;
using std::move;

class MainWindow : public QWidget {

    Q_OBJECT;

    unique_ptr<QIcon> icon;
    unique_ptr<QStandardItemModel> stdItemModel;
    unique_ptr<QIcon> user_document_icon;
    shared_ptr<QIcon> plus_icon;
    //QList<QMap<QString, QVariant>> list;
    QListWidget listWidget;
    unique_ptr<QStandardItem> plusIconItem;
    unique_ptr<QStandardItem> plusTextItem;
    unique_ptr<QLabel> addLink;
    unique_ptr<QTableView> tableView;
public:
    MainWindow(QWidget *widget = nullptr);
    void addList(const QMap<QString, QVariant>& item);
    void addList(QMap<QString, QVariant>&& item);
};

#endif
