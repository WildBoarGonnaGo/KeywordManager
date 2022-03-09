#include "keywordtablemodel.h"
#include <QCheckBox>

const QVector<int> KeywordTableModel::colorList = { stdColors.blue(), stdColors.red(), stdColors.green(),
                                  stdColors.yellow(), stdColors.cyan(), stdColors.magenta(),
                                  stdColors.black() };

KeywordTableModel::KeywordTableModel() : mapLabel(QList<QMap<int, unique_ptr<QLabel>>>()),
    stackPal(QStack<unique_ptr<QPalette>>()) {
    stackPal = QStack<unique_ptr<QPalette>>();
    exportListLabel = make_unique<QLabel>("<img src=\":/KeywordManager/export_list_icon.png\" width = \"10\" height = \"10\">");
    importListLabel = make_unique<QLabel>("<img src=\":/KeywordManager/import_list_icon.png\" width = \"10\" height = \"10\">");
    clickLabel = make_unique<ClickLabel>("Введите имя нового списка");

    QPixmap bigPlusPixmap = QPixmap(":/KeywordManager/plus_icon.png");
    plusPixmap = bigPlusPixmap.scaled(10, 10, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    plusLabel = make_unique<QLabel>("");
    plusLabel->setPixmap(plusPixmap);

    QMap<int, unique_ptr<QLabel>> initMap;
    initMap[0] = move(plusLabel);
    initMap[1] = move(clickLabel);
    initMap[2] = make_unique<QLabel>();
    initMap[3] = make_unique<QLabel>();
    mapLabel.push_back(initMap);
}

/*KeywordTableModel::KeywordTableModel(QList<QMap<int, unique_ptr<QLabel>>>&& that) noexcept {
    mapLabel = move(that);
	stackPal = QStack<unique_ptr<QPalette>>();
    exportListLabel = make_unique<QLabel>("<img src=\":/KeywordManager/export_list_icon.png\" width = \"10\" height = \"10\">");
    importListLabel = make_unique<QLabel>("<img src=\":/KeywordManager/import_list_icon.png\" width = \"10\" height = \"10\">");
    clickLabel = make_unique<ClickLabel>("Введите имя нового списка");

	QPixmap bigPlusPixmap = QPixmap(":/KeywordManager/plus_icon.png");
	plusPixmap = bigPlusPixmap.scaled(10, 10, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    plusLabel = make_unique<QLabel>("");
	plusLabel->setPixmap(plusPixmap);

    QMap<int, unique_ptr<QLabel>> initMap;
    initMap[0] = move(plusLabel);
    initMap[1] = move(clickLabel);
    initMap[2] = make_unique<QLabel>();
    initMap[3] = make_unique<QLabel>();
}*/

int KeywordTableModel::rowCount(const QModelIndex &parent) { return mapLabel.size(); }
int KeywordTableModel::columnCount(const QModelIndex &parent) {
	return 4;
}

bool KeywordTableModel::insertRows(int row, int count, const QModelIndex& parent) {
    if (row > mapLabel.size()) return false;
    QList<QMap<int, unique_ptr<QLabel>>>::const_iterator  it = mapLabel.begin();

    while (row--) ++it;
    QMap<int, unique_ptr<QLabel>> tmpMap;

	unique_ptr<QLabel> userLabel = make_unique<QLabel>(QString("<font color=blue>"
                                                       "<img src=\":/KeywordManager/document_user.png\" width = \"10\" height = \"10\">"
                                                       "%1<\\img><\\font>"));
    userLabel->setStyleSheet("QLabel { color : blue; }");

    QPixmap tmpBigPixmap(":/KeywordManager/recycle_bin.png");
    recycleBinPixmap = make_unique<QPixmap>(tmpBigPixmap.scaled(10, 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //recycleBinIcon = make_unique<QIcon>(tmpScaledPixmap);
    unique_ptr<QLabel> recycleBinLabel = make_unique<ClickLabel>("");
    recycleBinLabel->setPixmap(*recycleBinPixmap);
    recycleBinLabel->setVisible(false);

	//некое случайное число, которое выбирает цвет
	random_device device;
	default_random_engine randEngine(device());
	uniform_int_distribution<int> dist(0, colorList.size() - 1);
	int indx = dist(randEngine);

	//unique_ptr<QCheckBox> userCheckBox = make_unique<QCheckBox>();
	//userCheckBox->setTristate(false);

	unique_ptr<QLabel> checkLabel = make_unique<QLabel>("0");

	tmpMap[0] = move(checkLabel);
    tmpMap[1] = move(userLabel);
    tmpMap[2] = move(recycleBinLabel);
    tmpMap[3] = make_unique<QLabel>();
    tmpMap[4] = make_unique<QLabel>(tmpMap[3]);

	stackPal.push(make_unique<QPalette>());
	stackPal.top()->setColor(tmpMap[4]->backgroundRole(), colorList[indx]);
    tmpMap[4]->setPalette(*stackPal.top());
	tmpMap[4]->resize(10, 10);
    tmpMap[4]->setAutoFillBackground(true);

    mapLabel.insert(it, tmpMap);
    return true;
}

bool KeywordTableModel::insertColumns(int row, int count, const QModelIndex& parent) { return true; }


QVariant KeywordTableModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) return QVariant();
    //auto& tmpLabel = *mapLabel[index.row()][0];
    if (role == Qt::DisplayRole) return QVariant::fromValue(mapLabel[index.row()][index.column()].get());
	else if (role == Qt::CheckStateRole) {
        if (index.column() == 0 && index.row() != mapLabel.size() - 1) return (!QString(mapLabel[index.row()][0]->text()).toInt())
				? Qt::Unchecked : Qt::Checked;
	}
	return QVariant();
}

QVariant KeywordTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) return QVariant();
	if (orientation == Qt::Vertical) return section;
    QLabel test;
	switch (section) {
		case 0: return QString(""); break;
		case 1: return QString("Списки ключевых слов"); break;
        case 2: return QVariant::fromValue<QLabel*>(exportListLabel.get()); break;
        case 3: return QVariant::fromValue<QLabel*>(importListLabel.get()); break;
	}
	return QVariant();
}

bool KeywordTableModel::removeRows(int row, int count, const QModelIndex& parent) {
    if (mapLabel.empty()) return false;
    else if (row > mapLabel.size() + count - 1) return false;

    QList<QMap<int, unique_ptr<QLabel>>>::const_iterator it = mapLabel.begin();
    while (row--) ++it;
    mapLabel.erase(it);
    return true;
}

bool KeywordTableModel::removeColumns(int row, int count, const QModelIndex& parent) { return false; }

bool KeywordTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	if (!index.isValid()) return false;
	auto& tmpMap = mapLabel[index.row()];
	if (role == Qt::CheckStateRole) {
		QLabel& tmpLabel = static_cast<QLabel&>(*tmpMap[0]);
        if (!QString(tmpLabel.text()).toInt()) {
			tmpLabel.setText("0");
			return true;
		} else {
			tmpLabel.setText("1");
			return true;
		}
	}
    return false;
}

Qt::ItemFlags KeywordTableModel::flags(const QModelIndex& index) const {
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	int lastRow = mapLabel.size() - 1;
	if (index.column() == 0 && index.row() < lastRow) flags |= (Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	else if (index.row() != lastRow) flags |= (Qt::ItemIsEditable | Qt::ItemIsSelectable);
	else flags = Qt::NoItemFlags;
	return flags;
}
