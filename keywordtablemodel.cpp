#include "keywordtablemodel.h"
#include <QCheckBox>

KeywordTableModel::KeywordTableModel() : mapLabel(QList<QMap<int, unique_ptr<QWidget>>>()) { }

KeywordTableModel::KeywordTableModel(QList<QMap<int, unique_ptr<QWidget>>>&& that) noexcept {
    mapLabel = move(that);
}

int KeywordTableModel::rowCount(const QModelIndex &parent) { return mapLabel.size(); }
int KeywordTableModel::columnCount(const QModelIndex &parent) {
    return (mapLabel.isEmpty()) ? 0 : mapLabel.at(0).size();
}

bool KeywordTableModel::insertRows(int row, int count, const QModelIndex& parent) {
    QList<QMap<int, unique_ptr<QWidget>>>::iterator  it = mapLabel.begin();

    while (row--) ++it;
    QMap<int, unique_ptr<QWidget>> tmpMap;

    unique_ptr<QLabel> userLabel = make_unique<QLabel>("новый список");
    userLabel->setStyleSheet("QLabel { color : blue; }");

    QPixmap tmpBigPixmap(":/KeywordManager/recycle_bin.png");
    recycleBinPixmap = make_unique<QPixmap>(tmpBigPixmap.scaled(10, 10, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    //recycleBinIcon = make_unique<QIcon>(tmpScaledPixmap);
    unique_ptr<QLabel> recycleBinLabel = make_unique<QLabel>("");
    recycleBinLabel->setPixmap(*recycleBinPixmap);
    recycleBinLabel->setVisible(false);

    unique_ptr<QCheckBox> userCheckBox = make_unique<QCheckBox>();
    userCheckBox->setTristate(false);

    tmpMap[0] = move(userCheckBox);
    tmpMap[1] = move(userLabel);
    tmpMap[2] = move(recycleBinLabel);
}

bool KeywordTableModel::insertColumns(int row, int count, const QModelIndex& parent) { return true; }
