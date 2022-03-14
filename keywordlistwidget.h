#ifndef KEYWORDLISTWIDGET_H
#define KEYWORDLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QFocusEvent>
#include <memory>
#include "clicklabel.h"
#include <list>
#include <vector>
#include <QCheckBox>
#include <QPalette>
#include <random>

using std::unique_ptr;
using std::make_unique;
using std::list;
using std::vector;
using std::random_device;
using std::uniform_int_distribution;
using std::default_random_engine;

class KeywordListWidget : public QWidget
{
    Q_OBJECT
    unique_ptr<QListWidget> listWidget;
    unique_ptr<QListWidgetItem> addWidgetMessage;
    unique_ptr<QLabel> plusLabel;
    unique_ptr<ClickLabel> addListLabel;
    unique_ptr<QPixmap> plusPixmap;
    unique_ptr<QPixmap> documentUserPixmap;
    unique_ptr<QPixmap> recycleBinPixmap;
    unique_ptr<QLabel> recycleBinLabel;
    list<unique_ptr<QWidget>> prohibUserList;
    list<unique_ptr<QListWidgetItem>> prohibUserListItem;
    QWidget* addListWidget;
	list<unique_ptr<QHBoxLayout>> userProhibHBoxLayout;
    list<unique_ptr<QLabel>> userProhibLabel;
    list<unique_ptr<ClickLabel>> deleteLabelSquad;
    list<unique_ptr<QLabel>> colorBox;
    list<unique_ptr<QCheckBox>> checkBoxList;
	list<unique_ptr<QLabel>> paperIconLabelList;
    random_device rDevice;
    default_random_engine rEngine;
    uniform_int_distribution<int> uniformRange;
    static vector<QString> colorVector;
public:
    explicit KeywordListWidget(QWidget *parent = nullptr);
    void addNewProhibList();
	void deleteProhibList(QLayout* layout, const int& count);
    virtual bool eventFilter(QObject* watcher, QEvent* event);
    ~KeywordListWidget();
public slots:
	void showRecycleBin(ClickLabel& recycleBin);
};

#endif // KEYWORDLISTWIDGET_H
