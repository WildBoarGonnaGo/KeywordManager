#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPixmap>
#include <QIcon>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QList>
#include <QImage>
#include <QLabel>
//#include "keywordtablemodel.h"
#include "keywordlistwidget.h"

using std::unique_ptr;
using std::make_unique;
using std::make_shared;

class MainWindow : public QWidget {

    Q_OBJECT;

    unique_ptr<QPixmap> abcPixmap;
    unique_ptr<QIcon> abcIcon;
    unique_ptr<KeywordListWidget> keywordListWidget;
    unique_ptr<QVBoxLayout> mainVBox;
public:
    MainWindow(QWidget *widget = nullptr);
    void addList(const QMap<QString, QVariant>& item);
    void addList(QMap<QString, QVariant>&& item);
};

#endif
