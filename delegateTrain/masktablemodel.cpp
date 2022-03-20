#include "masktablemodel.h"
#include <QPixmap>
#include <QTextEdit>
#include <cassert>

MaskTableModel::MaskTableModel(const QMap<QString, QVariant>& mapCp,
							   const QList<KeywordDataSet>& cpList, QObject* parent)
	: QAbstractTableModel(parent), map(mapCp), columns(4),
      dataSetList(QList<KeywordDataSet>()),
      documentImportPixmap(":/delegateTrain/document_import.png"),
      documentExportPixmap(":/delegateTrain/document_export.png"),
      delegate(nullptr),
      view(nullptr) {
    QString addList("<a href=\"#\">Добавить список ключевых слов<\\a>");
	dataSetList.push_back(std::move(addList));

    connect()
}

MaskTableModel::MaskTableModel(const QMap<QString, QVariant>& mapCp,
			   QList<KeywordDataSet>&& mvList, QObject* parent) :
    QAbstractTableModel(parent), map(mapCp), dataSetList(std::move(mvList)), columns(4),
    documentImportPixmap(":/delegateTrain/document_import.png"),
    documentExportPixmap(":/delegateTrain/document_export.png"),
    delegate(nullptr),
    view(nullptr) {
    QString addList("<a href=\"#\">Добавить список ключевых слов<\\a>");
    dataSetList.push_back(std::move(addList));
}

int MaskTableModel::rowCount(const QModelIndex& parent) const { return dataSetList.size(); }

int MaskTableModel::columnCount(const QModelIndex &parent) const { return columns; }

QVariant MaskTableModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) return QVariant();
	if (index.row() >= rowCount() && index.column() >= columns) return QVariant();
	if (role == Qt::DisplayRole) {
        if (index.row() == rowCount() - 1) {
			if (index.column() == 1) return dataSetList.back().getData();
		}
	}
	else if (role == Qt::DecorationRole) {
		if (index.row() == rowCount() - 1 && index.column() == 0) {
            return QPixmap::fromImage(dataSetList.back().getPlusImage())
					.scaled(15 ,15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		}
        if (index.column() == 2 && index.row() != rowCount() - 1) return QPixmap::fromImage(dataSetList[index.row()].getRecycleBinImage())
                .scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        if (index.column() == 3 && index.row() != rowCount() - 1) return QPixmap::fromImage(dataSetList[index.row()].getUpImage())
                .scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}
	else if (role == Qt::CheckStateRole) {
        if (index.row() != rowCount() - 1 && !index.column()) {
            if (dataSetList[index.row()].getCheckState()) return Qt::Unchecked;
            else return Qt::Checked;
        }
	}
	return QVariant();
}

QVariant MaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal) {
        if (role == Qt::CheckStateRole) return checkTotalState();
        if (role == Qt::DisplayRole) {
            if (section == 1) return QString("Списки ключевых слов");
        }
        if (role == Qt::DecorationRole) {
            if (section == 2) return documentImportPixmap.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            if (section == 3) return documentExportPixmap.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
    }
    return QVariant();
}

Qt::ItemFlags MaskTableModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return Qt::ItemIsEnabled;
    if (index.row() == rowCount() - 1) return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
    //if (index.row() == rowCount() - 1 && index.column() == 1) return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled;
    if (index.row() < rowCount() - 1 && index.column() != 1) return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MaskTableModel::setData(const QModelIndex &index, const QVariant& value, int role) {
    KeywordDataSet someSet;
    dataSetList.push_back(std::move(value.toString()));
    if (!index.isValid()) return false;
    if (index.isValid() && role == Qt::EditRole) {

    }
    return true;
}

Qt::CheckState MaskTableModel::checkTotalState() const {
    for (int i = 0; i < dataSetList.size() - 1; ++i) {
        if (!dataSetList[i].getCheckState()) return Qt::Unchecked;
    }
    return Qt::Checked;
}

void MaskTableModel::setTableView(QTableView* view) { this->view = view; }

void MaskTableModel::setLastRowDelegate(DrawItemDelegate* delegate) {
    this->delegate = delegate;
    if (this->delegate) connect(this->delegate->getLabel(), &QLabel::linkActivated, this, SLOT(addNewList(const QString&)));
}

void MaskTableModel::addNewList(const QString& dst) {
    assert(this->view != nullptr && this->delegate != nullptr);
    dataSetList.push_back(KeywordDataSet(dst));

}
