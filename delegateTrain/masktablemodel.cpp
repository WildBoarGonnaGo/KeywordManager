#include "masktablemodel.h"
#include <QPixmap>
#include <QTextEdit>
#include <cassert>
#include <QDebug>
#include <iostream>

MaskTableModel::MaskTableModel(const QMap<QString, QVariant>& mapCp,
							   const QList<KeywordDataSet>& cpList, QObject* parent)
	: QAbstractTableModel(parent), map(mapCp), columns(4),
      dataSetList(QList<KeywordDataSet>()),
      documentImportPixmap(":/delegateTrain/document_import.png"),
      documentExportPixmap(":/delegateTrain/document_export.png"),
	  delegate(nullptr),
	  lineEditDelegate(new LineEditDelegate()),
	  view(nullptr) {
    QString addList("<a href=\"#\">Добавить список ключевых слов<\\a>");
	dataSetList.push_back(std::move(addList));
}

MaskTableModel::MaskTableModel(const QMap<QString, QVariant>& mapCp,
			   QList<KeywordDataSet>&& mvList, QObject* parent) :
    QAbstractTableModel(parent), map(mapCp), dataSetList(std::move(mvList)), columns(4),
    documentImportPixmap(":/delegateTrain/document_import.png"),
    documentExportPixmap(":/delegateTrain/document_export.png"),
	delegate(nullptr),
	lineEditDelegate(new LineEditDelegate()),
    view(nullptr) {
    QString addList("<a href=\"#\">Добавить список ключевых слов<\\a>");
    dataSetList.push_back(std::move(addList));
}

int MaskTableModel::rowCount(const QModelIndex& parent) const { return dataSetList.size(); }

int MaskTableModel::columnCount(const QModelIndex &parent) const { return columns; }

QVariant MaskTableModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid()) return QVariant();
	if (index.row() >= rowCount() || index.column() >= columns) return QVariant();
	if (role == Qt::DisplayRole) {
		if (index.row() == rowCount() - 1 && index.column() == 1) return dataSetList[index.row()].getData();
	}
	if (role == Qt::EditRole) {
		if (index.row() != rowCount() - 1 && index.column() == 1) return dataSetList[index.row()].getData();
	}
	if (role == Qt::DecorationRole) {
		if (index.row() == rowCount() - 1 && index.column() == 0) {
            return QPixmap::fromImage(dataSetList.back().getPlusImage())
					.scaled(15 ,15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		}
        if (index.column() == 2 && index.row() != rowCount() - 1) return QPixmap::fromImage(dataSetList[index.row()].getRecycleBinImage())
                .scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        if (index.column() == 3 && index.row() != rowCount() - 1) return QPixmap::fromImage(dataSetList[index.row()].getUpImage())
                .scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}
	if (role == Qt::CheckStateRole) {
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
    if (index.row() < rowCount() - 1 && index.column() != 1) return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MaskTableModel::setData(const QModelIndex &index, const QVariant& value, int role) {
    KeywordDataSet someSet;
    dataSetList.push_back(std::move(value.toString()));
    if (!index.isValid()) return false;
	/*if (index.isValid() && role == Qt::EditRole) {

	}*/
    return true;
}

Qt::CheckState MaskTableModel::checkTotalState() const {
    for (int i = 0; i < dataSetList.size() - 1; ++i) {
        if (!dataSetList[i].getCheckState()) return Qt::Unchecked;
    }
    return Qt::Checked;
}

void MaskTableModel::setTableView(QTableView* view) {
	this->view = view;
	lineEditDelegate->setTableView(this->view);
}

void MaskTableModel::setLastRowDelegate(DrawItemDelegate* delegate) {
    this->delegate = delegate;
	if (this->delegate) {
		connect(this->delegate->getLabel(), &QLabel::linkActivated,
					this, &MaskTableModel::addNewList);
		std::cout << "this->delegate->getLabel() = "
				  << std::hex << this->delegate->getLabel() << std::endl;
		std::cout << "this = "
				  << std::hex << this << std::endl;
	}
}

void MaskTableModel::addNewList(const QString& dst) {
	qDebug() << "Entered!";
	assert(this->view != nullptr);
	assert(this->lineEditDelegate != nullptr);
	//dataSetList.push_front(KeywordDataSet(lineEditDelegate->getData()));

	int bound = dataSetList.size() - 1;

	insertRows(bound, 1);
	bound = dataSetList.size() - 1;
	/*for (int i = 0; i < bound; ++i) {
		setData(this->index(i, 0), dataSetList[i].getCheckState(), Qt::CheckStateRole);
		setData(this->index(i, 1), dataSetList[i].getData(), Qt::EditRole);
		setData(this->index(i, 2), dataSetList[i].getRecycleBinImage()
				.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation), Qt::DecorationRole);
		setData(this->index(i, 3), dataSetList[i].getUpImage()
				.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation), Qt::DecorationRole);
		this->view->setItemDelegateForRow(i, lineEditDelegate);
	}

	setData(this->index(bound, 0), dataSetList.back().getPlusImage(), Qt::DecorationRole);
	setData(this->index(bound, 1), dataSetList.back().getData(), Qt::DisplayRole);*/
	for (int i = 0; i < rowCount() - 1; ++i) this->view->setItemDelegateForRow(i, lineEditDelegate);
	this->view->setItemDelegateForRow(rowCount() - 1, delegate);

	emit dataChanged(index(0, 0), index(rowCount() - 1, 3));
}

const QList<KeywordDataSet>& MaskTableModel::getDataSetList() const { return this->dataSetList; }


bool MaskTableModel::insertRows(int row, int count, const QModelIndex &parent) {
	beginInsertRows(QModelIndex(), row, row + count - 1);

	int bound = row + count;
	for (int i = row; i < bound; ++i)
		dataSetList.insert(i, KeywordDataSet(lineEditDelegate->getData()));
	endInsertRows();
	return true;
}

/*bool MaskTableModel::removeRows(int row, int count, const QModelIndex &parent) override {

}*/
