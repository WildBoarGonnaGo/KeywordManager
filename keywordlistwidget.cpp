#include "keywordlistwidget.h"
#include <QSize>
#include <QFocusEvent>
#include <QColor>
#include <QDebug>
#include <iostream>
vector<int> KeywordListWidget::colorVector = { Qt::red, Qt::blue, Qt::yellow, Qt::cyan,
                                               Qt::magenta, Qt::green, Qt::gray};

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
    paletteList = list<unique_ptr<QPalette>>();
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
			//ClickLabel* labelAddr = static_cast<ClickLabel*>(layoutSeek->itemAt(indexWidget)->widget());
			qDebug() << "Recycle bin label clicked";
			deleteProhibList(layoutSeek, i);
			return true;
		}
	}
	i = -1;
	return false;
}

void KeywordListWidget::addNewProhibList() {
    int rNumber = uniformRange(rEngine);

    userProhibLabel.push_back(make_unique<QLabel>());
    userProhibLabel.back()->setTextInteractionFlags(Qt::TextEditorInteraction);
	userProhibLabel.back()->setFixedWidth(300);
    userProhibLabel.back()->setText("cписок");

    checkBoxList.push_back(make_unique<QCheckBox>());
    checkBoxList.back()->setTristate(false);

    deleteLabelSquad.push_back(make_unique<ClickLabel>());
    deleteLabelSquad.back()->setPixmap(*recycleBinPixmap);
	deleteLabelSquad.back()->installEventFilter(this);

    colorBox.push_back(make_unique<QLabel>());
    paletteList.push_back(make_unique<QPalette>());
    paletteList.back()->setColor(colorBox.back()->backgroundRole(), colorVector[rNumber]);
    colorBox.back()->setPalette(*(paletteList.back()));
    colorBox.back()->resize(14, 14);
	//colorBox.back()->setFrameShape(QFrame::Box);
    colorBox.back()->setAlignment(Qt::AlignCenter);
	colorBox.back()->setAutoFillBackground(true);

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
	deleteLabelSquad.back()->setVisible(false);
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

	connect(listWidget.get(), SIGNAL(listWidget->itemEntered(prohibUserListItem.front().get())), SLOT(showRecycleBin(*(deleteLabelSquad.back()))));
}

void KeywordListWidget::showRecycleBin(ClickLabel& recycleBin) {
	recycleBin.setVisible(true);
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
