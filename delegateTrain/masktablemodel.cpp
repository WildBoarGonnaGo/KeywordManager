#include "masktablemodel.h"

MaskTableModel::MaskTableModel(const QMap<QString, QVariant>& mapCp, QObject* parent)
	: QAbstractTableModel(parent), map(mapCp), columns(2) { }

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
	return QVariant();
}
QVariant MaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole) return QVariant();
	else if (orientation == Qt::Horizontal)
		return (!section) ? QString("Key") : QString("Value");
}
