#include "masktablemodel.h"
#include <QPixmap>
#include <QTextEdit>
#include <cassert>
#include <QDebug>
#include <iostream>
#include <QMouseEvent>
#include <ctime>

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
	}
	if (role == Qt::CheckStateRole) {
		if (index.row() < rowCount() - 1 && !index.column()) {
			return static_cast<Qt::CheckState>(dataSetList[index.row()].getCheckState());
        }
	}
	return QVariant();
}

QVariant MaskTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal) {
		if (!section && role == Qt::CheckStateRole)	return checkTotalState();
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
	if (index.row() < rowCount() - 1 && index.column() > 1) return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
    if (index.row() < rowCount() - 1 && !index.column()) return QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable;
	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool MaskTableModel::setData(const QModelIndex &index, const QVariant& value, int role) {
    KeywordDataSet someSet;
    if (!index.isValid()) return false;
	if (role == Qt::EditRole) {
		dataSetList[index.row()].setData(value.toString());
		emit dataChanged(index, index, {role});
		return true;
	}
	if (role == Qt::CheckStateRole) {
		if (static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked) {
			dataSetList[index.row()].setCheckState(2);
			return true;
		}
		else {
			dataSetList[index.row()].setCheckState(0);
			return true;
		}
	}
	return false;
}

Qt::CheckState MaskTableModel::checkTotalState() const {
	for (int i = 0; i < rowCount() - 1; ++i) {
        if (!dataSetList[i].getCheckState()) return Qt::Unchecked;
    }
    return Qt::Checked;
}

void MaskTableModel::setTableView(QTableView* view) {
	this->view = view;
	lineEditDelegate->setTableView(this->view);
    this->view->viewport()->installEventFilter(this);
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
    connect(this->view, SIGNAL(viewportEntered()), this, SLOT(hideRecycle()));
	connect(dataSetList[bound].getLineEditDelegate()->getRecycleBinButton(), SIGNAL(clicked(bool)), this, SLOT(removeList(bool)));
	dataSetList[bound].getLineEditDelegate()->getRecycleBinButton()->installEventFilter(this);
}

const QList<KeywordDataSet>& MaskTableModel::getDataSetList() const { return this->dataSetList; }


bool MaskTableModel::insertRows(int row, int count, const QModelIndex &parent) {
	qsrand(time(0x0));
	int index = qrand() % colorVector.size();

	beginInsertRows(QModelIndex(), row, row + count - 1);

	int bound = row + count;
	for (int i = row; i < bound; ++i)
		dataSetList.insert(i, KeywordDataSet(lineEditDelegate->getData()));
	dataSetList[row].getLineEditDelegate()->setColor(colorVector[index]);
    for (int i = 0; i < rowCount() - 1; ++i) {
		this->view->setItemDelegateForRow(i, dataSetList[i].getLineEditDelegate());
        dataSetList[i].getLineEditDelegate()->setTableView(this->view);
    }
	this->view->setItemDelegateForRow(rowCount() - 1, delegate);
	endInsertRows();
	return true;
}

bool MaskTableModel::removeRows(int row, int count, const QModelIndex &parent) {
	if (!parent.isValid()) return false;
	beginRemoveRows(QModelIndex(), row, row + count - 1);
	QList<KeywordDataSet>::iterator it = dataSetList.begin();
	for (int i = 0; i < row + count - 1; ++i) ++it;
	dataSetList.erase(it);
	this->view->setItemDelegateForRow(rowCount() - 1, delegate);
	for (int i = 0; i < rowCount() - 1; ++i) {
		this->view->setItemDelegateForRow(i, dataSetList[i].getLineEditDelegate());
		dataSetList[i].getLineEditDelegate()->setTableView(this->view);
	}
    endRemoveRows();
	return true;
}

void MaskTableModel::showRecycle(const QModelIndex& parent) {
    if (!parent.isValid()) return;
    if (parent.row() < rowCount() - 1) {
        dataSetList[parent.row()].getLineEditDelegate()->setActiveRecycle(true);
    }
}

void MaskTableModel::hideRecycle() {
    for (int i = 0; i < rowCount() - 1; ++i)
        dataSetList[i].getLineEditDelegate()->setActiveRecycle(false);
}

void MaskTableModel::openEditor() {
	QModelIndex editorIndex = this->index(boundSave, 1);
	emit this->view->edit(editorIndex);
}

bool MaskTableModel::eventFilter(QObject* watched, QEvent* event) {
    if (watched == this->view->viewport()) {
        if (event->type() == QEvent::MouseMove) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QModelIndex mouseIndex = this->view->indexAt(mouseEvent->pos());
            if (mouseIndex.isValid()) {
                for (int i = 0; i < rowCount(); ++i) {
                    if (i == rowCount() - 1) break;
                    QPushButton* tmpButton = dataSetList[i].getLineEditDelegate()->getRecycleBinButton();
                    setButtonActive(tmpButton, (i == mouseIndex.row()) ? true : false);
                }
            } else {
                for (int i = 0; i < rowCount(); ++i) {
                    QPushButton* tmpButton = dataSetList[i].getLineEditDelegate()->getRecycleBinButton();
                    setButtonActive(tmpButton, false);
                }
			}
        }
    }
    return QAbstractTableModel::eventFilter(watched, event);
}

void MaskTableModel::setButtonActive(QPushButton* button, const bool& activeState) {
    button->setEnabled(activeState);
    button->setVisible(activeState);
    if (activeState) button->show();
    else button->hide();
}

void MaskTableModel::setCheckTotalState(const bool& state) {
	Qt::CheckState totalState = (state) ? Qt::Checked : Qt::Unchecked;
	for (int i = 0; i < rowCount() - 1; ++i) {
		QModelIndex forIndex = this->index(i, 0);
		setData(forIndex, totalState, Qt::CheckStateRole);
	}
	emit dataChanged(index(0, 0), index(rowCount() - 1, 0), {Qt::CheckStateRole});
}

void MaskTableModel::removeList(const bool& state) {
	QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
	int row;
	for (row = 0; row < rowCount() - 1; ++row) {
		QPushButton* tmpButton = dataSetList[row].getLineEditDelegate()->getRecycleBinButton();
		if (tmpButton == buttonSender) {
			QModelIndex rowRemoveIndex  = this->index(0, 0);
			removeRows(row, 1, rowRemoveIndex);
			break ;
		}
	}
}

