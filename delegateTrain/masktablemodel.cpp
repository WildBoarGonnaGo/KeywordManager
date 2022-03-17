#include "masktablemodel.h"

MaskTableModel::MaskTableModel(const QMap<QString, QVariant>& mapCp,
							   const QList<KeywordDataSet>& cpList, QObject* parent)
	: QAbstractTableModel(parent), map(mapCp), columns(2),
	  dataSetList(QList<KeywordDataSet>()) {  }

MaskTableModel::MaskTableModel(const QMap<QString, QVariant>& mapCp,
			   QList<KeywordDataSet>&& mvList, QObject* parent) :
	QAbstractTableModel(parent), map(mapCp), dataSetList(std::move(mvList)), columns(dataSetList.size()) { }

int MaskTableModel::rowCount(const QModelIndex& parent) const { return map.size(); }

int MaskTableModel::columnCount(const QModelIndex &parent) const { return columns; }

QVariant MaskTableModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) return QVariant();
	if (index.row() >= map.size() && index.column() >= 2) return QVariant();
	if (role == Qt::DisplayRole) {
		QMap<QString, QVariant>::const_iterator it = map.begin();
		int count = index.row();
		while (count--) ++it;
		if (!index.column()) return it.key();
		return it.value();
	}
	else if (role == Qt::DecorationRole) {
		if (index.row() == )
	}
	return QVariant();
}

QVariant MaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) return QVariant();
	else if (orientation == Qt::Horizontal)
		return (!section) ? QString("Key") : QString("Value");
    return QVariant();
}

Qt::ItemFlags MaskTableModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::ItemIsEnabled;
    if (index.row() < rowCount() && !index.column()) return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MaskTableModel::setData(const QModelIndex &index, const QVariant& value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        QMap<QString, QVariant>::const_iterator it = map.begin();
        int count = index.row();
        while (count--) ++it;
        map[it.key()] = value;
        return true;
    }
    return false;
}
