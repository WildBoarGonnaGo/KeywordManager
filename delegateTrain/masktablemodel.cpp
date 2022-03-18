#include "masktablemodel.h"
#include <QPixmap>
#include <QTextEdit>

MaskTableModel::MaskTableModel(const QMap<QString, QVariant>& mapCp,
							   const QList<KeywordDataSet>& cpList, QObject* parent)
	: QAbstractTableModel(parent), map(mapCp), columns(4),
	  dataSetList(QList<KeywordDataSet>()) {
	QString addList("<a href=\"#\">Добавить список ключевых слов<\a>");
	dataSetList.push_back(std::move(addList));
}

MaskTableModel::MaskTableModel(const QMap<QString, QVariant>& mapCp,
			   QList<KeywordDataSet>&& mvList, QObject* parent) :
	QAbstractTableModel(parent), map(mapCp), dataSetList(std::move(mvList)), columns(4) { }

int MaskTableModel::rowCount(const QModelIndex& parent) const { return dataSetList.size(); }

int MaskTableModel::columnCount(const QModelIndex &parent) const { return columns; }

QVariant MaskTableModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) return QVariant();
	if (index.row() >= rowCount() && index.column() >= columns) return QVariant();
	if (role == Qt::DisplayRole) {
		if (index.row = rowCount() - 1) {
			if (index.column() == 1) return dataSetList.back().getData();
		}
		/*QMap<QString, QVariant>::const_iterator it = map.begin();
		int count = index.row();
		while (count--) ++it;
		if (!index.column()) return it.key();
		return it.value();*/
	}
	else if (role == Qt::DecorationRole) {
		if (index.row() == rowCount() - 1 && index.column() == 0) {
			return QPixmap::fromImage(dataSetList.back().getPlusPixmap())
					.scaled(15 ,15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		}
	}
	else if (role == Qt::CheckStateRole) {
		if (index.row() != rowCount() - 1) return dataSetList[index.row()].getCheck();
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
