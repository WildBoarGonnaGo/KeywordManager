#include "keywordtablemodel.h"
#include <QCheckBox>

KeywordTableModel::KeywordTableModel() : mapLabel(QList<QMap<int, unique_ptr<QWidget>>>()),
	stackPal(QStack<unique_ptr<QPalette>>){ }

KeywordTableModel::KeywordTableModel(QList<QMap<int, unique_ptr<QWidget>>>&& that) noexcept {
    mapLabel = move(that);
	stackPal = QStack<unique_ptr<QPalette>>();
	exportListLabel = make_unique("<img src=\":/KeywordManager/export_list_icon.png\" width = \"10\ height = \"10\">");
	importListLabel = make_unique("<img src=\":/KeywordManager/import_list_icon.png\" width = \"10\ height = \"10\">");
	clickLabel = make_unique("Введите имя нового списка");

	QPixmap bigPlusPixmap = QPixmap(":/KeywordManager/plus_icon.png");
	plusPixmap = bigPlusPixmap.scaled(10, 10, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	plusLabel = make_shared<QLabel>("");
	plusLabel->setPixmap(plusPixmap);
}

int KeywordTableModel::rowCount(const QModelIndex &parent) { return mapLabel.size(); }
int KeywordTableModel::columnCount(const QModelIndex &parent) {
	return 4;
}

bool KeywordTableModel::insertRows(int row, int count, const QModelIndex& parent) {
    QList<QMap<int, unique_ptr<QWidget>>>::iterator  it = mapLabel.begin();

    while (row--) ++it;
    QMap<int, unique_ptr<QWidget>> tmpMap;

	unique_ptr<QLabel> userLabel = make_unique<QLabel>(QString("<font color=blue>"
													   "<img src=\":/KeywordManager/document_user.png\" width = \"10\ height = \"10\">"
													   "%1<\img><\font>"));
    userLabel->setStyleSheet("QLabel { color : blue; }");

    QPixmap tmpBigPixmap(":/KeywordManager/recycle_bin.png");
    recycleBinPixmap = make_unique<QPixmap>(tmpBigPixmap.scaled(10, 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //recycleBinIcon = make_unique<QIcon>(tmpScaledPixmap);
    unique_ptr<QLabel> recycleBinLabel = make_unique<QLabel>("");
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
	tmpMap[3] = make_unique<QWidget>();
	tmpMap[4] = make_unique<QWidget>(tmpMap[3]);

	stackPal.push(make_unique<QPalette>());
	stackPal.top()->setColor(tmpMap[4]->backgroundRole(), colorList[indx]);
	tmpMap[4]->setPalette(stackPal.top());
	tmpMap[4]->resize(10, 10);
	tmpMap[4]->autoFillBackground(true);

	mapLabel.insert(it, tmpMap);
}

bool KeywordTableModel::insertColumns(int row, int count, const QModelIndex& parent) { return true; }


QVariant KeywordTableModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) return QVariant();
	auto tmpMap = mapLabel[index.row()];
	if (role == Qt::DisplayRole) return mapLabel[index.column()];
	else if (role == Qt::CheckStateRole) {
		if (index.column() == 0) return (!QString::number(static_cast<unique_ptr<QLabel>>(tmpMap[0])->text()))
				? Qt::Unchecked : Qt::Checked;
	}
	return QVariant();
}

QVariant KeywordTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) return QVariant();
	if (orientation == Qt::Vertical) return section;
	switch (section) {
		case 0: return QString(""); break;
		case 1: return QString("Списки ключевых слов"); break;
		case 2: return QVariant::fromValue(*exportListLabel); break;
		case 3: return QVariant::fromValue(*importListLabel); break;
	}
	return QVariant();
}

bool KeywordTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	if (!index.isValid()) return false;
	auto& tmpMap = mapLabel[index.row()];
	if (role == Qt::CheckStateRole) {
		QLabel& tmpLabel = static_cast<QLabel&>(*tmpMap[0]);
		if (!QString::number(tmpLabel.text())) {
			tmpLabel.setText("0");
			return true;
		} else {
			tmpLabel.setText("1");
			return true;
		}
	}
}

virtual Qt::ItemFlags KeywordTableModel::flags(const QModelIndex& index) const {
	Qt::ItemFlags flags = QAbstractTableModel::flags(index);
	int lastRow = mapLabel.size() - 1;
	if (index.column() == 0 && index.row() < lastRow) flags |= (Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
	else if (index.row() != lastRow) flags |= (Qt::ItemIsEditable | Qt::ItemIsSelectable);
	else flags = Qt::NoItemFlags;
	return flags;
}
