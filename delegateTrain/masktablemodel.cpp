#include "masktablemodel.h"
#include <QPixmap>
#include <QTextEdit>
#include <cassert>
#include <QDebug>
#include <iostream>

const QVector<Qt::GlobalColor> MaskTableModel::colorVector =
    { Qt::white, Qt::black, Qt::red, Qt::darkRed, Qt::green,
	Qt::darkGreen, Qt::blue, Qt::darkBlue, Qt::cyan, Qt::darkCyan,
	Qt::magenta, Qt::darkMagenta, Qt::yellow, Qt::darkYellow, Qt::gray,
	Qt::lightGray, Qt::darkGray};

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
    if (!index.isValid()) return false;
	if (index.isValid() && role == Qt::EditRole) {
		dataSetList[index.row()].setData(value.toString());
		emit dataChanged(index, index, {role});
		return true;
	}
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
	}
}

void MaskTableModel::addNewList(const QString& dst) {
	assert(this->view != nullptr);
	assert(this->lineEditDelegate != nullptr);

	int bound = dataSetList.size() - 1;
	boundSave = bound;

    connect(this, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(openEditor()));
	insertRows(bound, 1);
    connect(this->view, SIGNAL(entered(QModelIndex)), this, SLOT(showRecycle(QModelIndex)));
    connect(this->view, SIGNAL(viewportEntered()), this, SLOT(hideRecycle(QModelIndex)));
}

const QList<KeywordDataSet>& MaskTableModel::getDataSetList() const { return this->dataSetList; }


bool MaskTableModel::insertRows(int row, int count, const QModelIndex &parent) {
	beginInsertRows(QModelIndex(), row, row + count - 1);

	int bound = row + count;
	for (int i = row; i < bound; ++i)
		dataSetList.insert(i, KeywordDataSet(lineEditDelegate->getData()));
	dataSetList[bound].getLineEditDelegate()->setTableView(this->view);
	for (int i = 0; i < rowCount() - 1; ++i)
		this->view->setItemDelegateForRow(i, dataSetList[i].getLineEditDelegate());
	this->view->setItemDelegateForRow(rowCount() - 1, delegate);
	endInsertRows();
	return true;
}

void MaskTableModel::showRecycle(const QModelIndex& parent) {
    if (!parent.isValid()) return;
    if (parent.row() < rowCount() - 1 && parent.column() == 2)
        dataSetList[boundSave].getLineEditDelegate()->setActiveRecycle(true);
    qDebug() << "showRecycle called";
}

void MaskTableModel::hideRecycle(const QModelIndex& parent) {
    if (!parent.isValid()) return;
    if (parent.row() < rowCount() - 1 && parent.column() == 2)
        dataSetList[boundSave].getLineEditDelegate()->setActiveRecycle(false);
    qDebug() << "hideRecycle called";
}

void MaskTableModel::openEditor() {
	qDebug() << "Open editor called";
	QModelIndex editorIndex = this->index(boundSave, 1);
	emit this->view->edit(editorIndex);
}
