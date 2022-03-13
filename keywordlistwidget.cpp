#include "keywordlistwidget.h"
#include <QSize>
#include <QFocusEvent>
#include <QColor>

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
    addListWidget = nullptr;

    QPixmap documentUserPixmapBig(":/KeywordManager/papers_icon.png");
    documentUserPixmap = make_unique<QPixmap>(documentUserPixmapBig.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QPixmap recycleBinPixmapBig(":/KeywordManager/recycle_bin.png");
    recycleBinPixmap = make_unique<QPixmap>(recycleBinPixmapBig.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    recycleBinLabel = make_unique<QLabel>();
    recycleBinLabel->setPixmap(*recycleBinPixmap);

    QPixmap pixmapBig(":/KeywordManager/plus_icon.png");
    plusPixmap = make_unique<QPixmap>(pixmapBig.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    plusLabel = make_unique<QLabel>();

    documentUserLabel = make_unique<QLabel>();
    documentUserLabel->setPixmap(*documentUserPixmap);

    addListLabel = make_unique<ClickLabel>("Введите имя нового списка");
    addListLabel->setFixedWidth(500);
    addListLabel->setFontSize(14);
    addListLabel->installEventFilter(this);

    plusLabel->setPixmap(*plusPixmap);
    addListHBoxLayout = make_unique<QHBoxLayout>(this);
    addListHBoxLayout->addWidget(plusLabel.get());
    addListHBoxLayout->addWidget(addListLabel.get());
    addListHBoxLayout->setSpacing(13);
    addListHBoxLayout->setAlignment(Qt::AlignLeft);

    prohibUserList.push_back(make_unique<QWidget>());
    prohibUserList.back()->setLayout(addListHBoxLayout.get());
    prohibUserListItem.push_back(make_unique<QListWidgetItem>(listWidget.get()));
    prohibUserListItem.back()->setSizeHint(QSize(400, 40));

    listWidget->setItemWidget(prohibUserListItem.back().get(), prohibUserList.back().get());
    listWidget->setMinimumSize(600, 500);
    prohibUserList.back()->installEventFilter(this);
    listWidget->show();
}

bool KeywordListWidget::eventFilter(QObject* watcher, QEvent* event) {
    if (!watcher && !event) return false;
    if (watcher == addListLabel.get() && event->type() == QEvent::MouseButtonPress) {
        qDebug() << "Link is clicked!";
        addNewProhibList();
        return true;
    } else return false;
}

void KeywordListWidget::addNewProhibList() {
    int rNumber = uniformRange(rEngine);

    userProhibLabel.push_back(make_unique<QLabel>());
    userProhibLabel.back()->setTextInteractionFlags(Qt::TextEditorInteraction);
    userProhibLabel.back()->setFixedWidth(400);
    userProhibLabel.back()->setText("cписок");

    checkBoxList.push_back(make_unique<QCheckBox>());
    checkBoxList.back()->setTristate(false);

    deleteLabelSquad.push_back(make_unique<ClickLabel>());
    deleteLabelSquad.back()->setPixmap(*recycleBinPixmap);

    colorBox.push_back(make_unique<QLabel>());
    paletteList.push_back(make_unique<QPalette>());
    paletteList.back()->setColor(colorBox.back()->backgroundRole(), colorVector[rNumber]);
    colorBox.back()->setPalette(*(paletteList.back()));
    colorBox.back()->resize(14, 14);
    colorBox.back()->setFrameShape(QFrame::Box);
    colorBox.back()->setAlignment(Qt::AlignCenter);



    userProhibHBoxLayout.push_back(make_unique<QHBoxLayout>());
    userProhibHBoxLayout.back()->addWidget(checkBoxList.back().get());
    userProhibHBoxLayout.back()->setAlignment(checkBoxList.back().get(), Qt::AlignLeft);
    userProhibHBoxLayout.back()->addStretch(2);
    userProhibHBoxLayout.back()->addWidget(documentUserLabel.get());
    userProhibHBoxLayout.back()->setAlignment(documentUserLabel.get(), Qt::AlignLeft);
    userProhibHBoxLayout.back()->addWidget(userProhibLabel.back().get());
    userProhibHBoxLayout.back()->setAlignment(userProhibLabel.back().get(), Qt::AlignLeft);
    userProhibHBoxLayout.back()->addWidget(deleteLabelSquad.back().get());
    userProhibHBoxLayout.back()->setAlignment(deleteLabelSquad.back().get(), Qt::AlignRight);
    userProhibHBoxLayout.back()->addWidget(colorBox.back().get());
    userProhibHBoxLayout.back()->addWidget(colorBox.back().get(), Qt::AlignRight);

    prohibUserList.push_front(make_unique<QWidget>());
    prohibUserList.front()->setLayout(userProhibHBoxLayout.back().get());
    prohibUserListItem.push_front(make_unique<QListWidgetItem>(listWidget.get()));
    prohibUserListItem.front()->setSizeHint(QSize(400, 40));

    listWidget->setItemWidget(prohibUserListItem.front().get(), prohibUserList.front().get());
}

KeywordListWidget::~KeywordListWidget() {
    /*prohibUserList.clear();
    prohibUserListItem.clear();
    userProhibHBoxLayout.clear();
    userProhibLabel.clear();
    deleteLabelSquad.clear();
    colorBox.clear();
    checkBoxList.clear();
    paletteList.clear();*/
}
