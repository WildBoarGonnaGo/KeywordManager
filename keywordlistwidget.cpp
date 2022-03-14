#include "keywordlistwidget.h"
#include <QSize>
#include <QFocusEvent>
#include <QColor>
#include <QDebug>
#include <iostream>
vector<QString> KeywordListWidget::colorVector = { "red", "blue", "cyan", "magenta", "green", "yellow", "white" };

KeywordListWidget::KeywordListWidget(QWidget *parent)
{
    setFixedSize(600, 500);
    setVisible(true);

    listWidget = make_unique<QListWidget>(this);
    prohibUserList = list<unique_ptr<QWidget>>();
    prohibUserListItem = list<unique_ptr<QListWidgetItem>>();
	userProhibHBoxLayout = list<unique_ptr<QHBoxLayout>>();
    userProhibLabel = list<unique_ptr<QLabel>>();
    deleteLabelSquad = list<unique_ptr<ClickLabel>>();
    colorBox = list<unique_ptr<QLabel>>();
    checkBoxList = list<unique_ptr<QCheckBox>>();
    rEngine = default_random_engine(rDevice());
    uniformRange = uniform_int_distribution<int>(0, colorVector.size() - 1);
	paperIconLabelList = list<unique_ptr<QLabel>>();
	//addListWidget = nullptr;

    QPixmap documentUserPixmapBig(":/KeywordManager/papers_icon.png");
    documentUserPixmap = make_unique<QPixmap>(documentUserPixmapBig.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap recycleBinPixmapBig(":/KeywordManager/recycle_bin.png");
	recycleBinPixmap = make_unique<QPixmap>(recycleBinPixmapBig.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    recycleBinLabel = make_unique<QLabel>();
    recycleBinLabel->setPixmap(*recycleBinPixmap);

    QPixmap pixmapBig(":/KeywordManager/plus_icon.png");
    plusPixmap = make_unique<QPixmap>(pixmapBig.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    plusLabel = make_unique<QLabel>();

	//documentUserLabel = make_unique<QLabel>();
	//documentUserLabel->setPixmap(*documentUserPixmap);

    addListLabel = make_unique<ClickLabel>("Введите имя нового списка");
    addListLabel->setFixedWidth(500);
    addListLabel->setFontSize(14);
    addListLabel->installEventFilter(this);

    plusLabel->setPixmap(*plusPixmap);

	userProhibHBoxLayout.push_back(make_unique<QHBoxLayout>(this));
	userProhibHBoxLayout.back()->addWidget(plusLabel.get());
	userProhibHBoxLayout.back()->addWidget(addListLabel.get());
	userProhibHBoxLayout.back()->setSpacing(13);
	userProhibHBoxLayout.back()->setAlignment(Qt::AlignLeft);

    prohibUserList.push_back(make_unique<QWidget>());
	prohibUserList.back()->setLayout(userProhibHBoxLayout.back().get());
    prohibUserListItem.push_back(make_unique<QListWidgetItem>(listWidget.get()));
    prohibUserListItem.back()->setSizeHint(QSize(400, 40));

    listWidget->setItemWidget(prohibUserListItem.back().get(), prohibUserList.back().get());
	listWidget->setMinimumSize(500, 500);
    prohibUserList.back()->installEventFilter(this);
    listWidget->show();
	listWidget->setSortingEnabled(true);
}

bool KeywordListWidget::eventFilter(QObject* watcher, QEvent* event) {
    if (!watcher && !event) return false;
    if (watcher == addListLabel.get() && event->type() == QEvent::MouseButtonPress) {
        qDebug() << "Link is clicked!";
        addNewProhibList();
        return true;
	}
	int i = -1;
	while (++i < listWidget->count()) {
		QListWidgetItem* item = listWidget->item(i);
		if (!item) continue;
		QWidget *widgetSeek = listWidget->itemWidget(item);
		if (!widgetSeek) continue;
		QLayout* layoutSeek = widgetSeek->layout();
		if (!layoutSeek) continue;
		int indexWidget = layoutSeek->indexOf(static_cast<QWidget*>(watcher));
		if (indexWidget != -1 && event->type() == QEvent::MouseButtonPress) {
			deleteProhibList(layoutSeek, i);
			return true;
		}
	}
	return false;
}

void KeywordListWidget::addNewProhibList() {
    int rNumber = uniformRange(rEngine);

    userProhibLabel.push_back(make_unique<QLabel>());
    userProhibLabel.back()->setTextInteractionFlags(Qt::TextEditorInteraction);
    userProhibLabel.back()->setFixedWidth(380);
    userProhibLabel.back()->setText("cписок");

    checkBoxList.push_back(make_unique<QCheckBox>());
    checkBoxList.back()->setTristate(false);

    deleteLabelSquad.push_back(make_unique<ClickLabel>());
    deleteLabelSquad.back()->setPixmap(*recycleBinPixmap);
	deleteLabelSquad.back()->installEventFilter(this);

    colorBox.push_back(make_unique<QLabel>());
    colorBox.back()->resize(14, 14);
    colorBox.back()->setFrameShape(QFrame::Box);
    colorBox.back()->setAlignment(Qt::AlignCenter);
	colorBox.back()->setAutoFillBackground(true);
    colorBox.back()->setStyleSheet(QString("QLabel { background-color: %1 }").arg(colorVector[rNumber]));

	paperIconLabelList.push_back(make_unique<QLabel>());
	paperIconLabelList.back()->setPixmap(*documentUserPixmap);

	userProhibHBoxLayout.push_back(make_unique<QHBoxLayout>(this));
    userProhibHBoxLayout.back()->addWidget(checkBoxList.back().get());
    userProhibHBoxLayout.back()->setAlignment(checkBoxList.back().get(), Qt::AlignLeft);
	userProhibHBoxLayout.back()->addWidget(paperIconLabelList.back().get());
	userProhibHBoxLayout.back()->setAlignment(paperIconLabelList.back().get(), Qt::AlignLeft);
    userProhibHBoxLayout.back()->addWidget(userProhibLabel.back().get());
    userProhibHBoxLayout.back()->setAlignment(userProhibLabel.back().get(), Qt::AlignLeft);
    userProhibHBoxLayout.back()->addWidget(deleteLabelSquad.back().get());
    userProhibHBoxLayout.back()->setAlignment(deleteLabelSquad.back().get(), Qt::AlignRight);
    deleteLabelSquad.back()->setVisible(true);
    userProhibHBoxLayout.back()->addWidget(colorBox.back().get());
    userProhibHBoxLayout.back()->addWidget(colorBox.back().get(), Qt::AlignRight);
	userProhibHBoxLayout.back()->setAlignment(Qt::AlignLeft);
	userProhibHBoxLayout.back()->setSpacing(10);

    prohibUserList.push_front(make_unique<QWidget>());
	prohibUserList.front()->setLayout(userProhibHBoxLayout.back().get());
	prohibUserList.front()->installEventFilter(this);
    prohibUserListItem.push_front(make_unique<QListWidgetItem>(listWidget.get()));
    prohibUserListItem.front()->setSizeHint(QSize(400, 40));

    listWidget->setItemWidget(prohibUserListItem.front().get(), prohibUserList.front().get());
	listWidget->sortItems();

    connect(listWidget.get(), SIGNAL(listWidget->itemEntered(QListWidgetItem*)), SLOT(showRecycleBin(ClickLabel&)));
}

void KeywordListWidget::showRecycleBin(ClickLabel& recycleBin) {
    qDebug() << "Eneterd list widget item";
    for (int i = 0; i < listWidget->count() - 1; ++i) {
          QListWidgetItem* widgetItemTmp = listWidget->item(i);
          if (!widgetItemTmp) continue ;
          QWidget *widgetSeek = listWidget->itemWidget(widgetItemTmp);
          if (!widgetSeek) continue;
          QLayout* layoutSeek = widgetSeek->layout();
          if (!layoutSeek) continue;

          list<unique_ptr<ClickLabel>>::iterator it = deleteLabelSquad.begin();
          while (it != deleteLabelSquad.end()) {
            ClickLabel* watch = it->get();
            if (watch == static_cast<ClickLabel*>(layoutSeek->itemAt(4)->widget())) watch->setVisible(false);
            else watch->setVisible(true);
            ++it;
          }
    }

}

void KeywordListWidget::deleteProhibList(QLayout* layout, const int& count) {

	listWidget->takeItem(count);
	int i = count;

	listWidget->sortItems();
}

KeywordListWidget::~KeywordListWidget() {
	addListLabel.release();
	plusLabel.release();
	list<unique_ptr<ClickLabel>>::iterator it = deleteLabelSquad.begin();
	while (it != deleteLabelSquad.end()) {
		list<unique_ptr<ClickLabel>>::iterator prev = it;
		it->release();
		++it;
		deleteLabelSquad.remove(*prev);
	}
}
