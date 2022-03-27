#include "lineeditdelegate.h"
#include <QLineEdit>
#include <QString>
#include <QClipboard>
#include <QPainter>
#include <QDebug>
#include <QPointF>
#include <QRect>
#include <QIcon>

LineEditDelegate::LineEditDelegate(QObject *parent) : QItemDelegate(parent),
    papersPixmap(":/delegateTrain/papers_icon.png"),
    recycleBinPixmap(":/delegateTrain/recycle_bin.png"),
    label(new QLabel()), tableView(nullptr),
    recycleBinButton(new QPushButton()),
    data(QString()), activeRecycle(false) {
    QIcon recycleBinIcon(recycleBinPixmap.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    recycleBinButton->setIcon(recycleBinIcon);
    recycleBinButton->setFlat(true);
}

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	qDebug() << "createEditor enter";
	QLineEdit* editor = new QLineEdit(parent);
	return editor;
}

void LineEditDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
	QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);

	if (index.row() < model->rowCount() - 1 && index.column() == 1) {
		QString targetText = lineEdit->text();
		model->setData(index, targetText, Qt::EditRole);
	}
}

void LineEditDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	QPoint topLeft(option.rect.left() + 20, option.rect.top());
	QRect  editorRect(topLeft, option.rect.bottomRight());

	editor->setGeometry(editorRect);
}

void LineEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    int rowPos = index.model()->rowCount() - 1;

    qDebug() << "paint event called";
    qDebug() << "activeRecycle = " << activeRecycle;
    if (!index.isValid()) return ;
    if (index.row() < rowPos && index.column() == 1) {
		QPointF iconPoint(option.rect.left(), option.rect.top() + 8);
		QPointF textPoint(option.rect.left() + 20, option.rect.bottom() - 8);

		painter->drawPixmap(iconPoint, papersPixmap.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		painter->drawText(textPoint, index.model()->data(index, Qt::EditRole).toString());
    }
    /*if (index.row() < rowPos && index.column() == 2 && activeRecycle == false && option.state) {
        qDebug() << "POINTRECT ERASE step";
        QModelIndex tmpIndex = index.model()->index(index.row(), 2);
        QRect pointRect = this->tableView->visualRect(tmpIndex);

        painter->eraseRect(pointRect);
        //painter->fillRect(pointRect, Qt::color0);
        painter->save();
        painter->restore();
    }
    if (index.row() < rowPos && activeRecycle == true && index.column() == 2) {
        qDebug() << "POINTRECT DRAW step";
        QModelIndex tmpIndex = index.model()->index(index.row(), 2);
        QRect pointRect = this->tableView->visualRect(tmpIndex);
        QPointF iconPoint(pointRect.left() + 2, pointRect.top() + 8);

        painter->drawPixmap(iconPoint, recycleBinPixmap.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        painter->save();
        painter->restore();
    } else QItemDelegate::paint(painter, option, index);*/
    if (index.row() < rowPos && index.column() == 2) {
        qDebug() << "QPUSHBUTTON event called";

        recycleBinButton->setGeometry(option.rect.left() + 2, option.rect.top() + 4, 16, 25);
        //recycleBinButton->setEnabled(activeRecycle);
        //recycleBinButton->setVisible(activeRecycle);
        this->tableView->setIndexWidget(index, recycleBinButton);
        //painter->restore();
    }
    else QItemDelegate::paint(painter, option, index);
    //painter->save();
    //painter->restore();
}

void LineEditDelegate::setTableView(QTableView* tableView) { this->tableView = tableView; }

void LineEditDelegate::setActiveRecycle(const bool& activeRecycle) { this->activeRecycle = activeRecycle; }

void LineEditDelegate::setDataSet(KeywordDataSet* dataSet) { this->dataSet = dataSet; }

const KeywordDataSet* LineEditDelegate::getDataSet() const { return dataSet; }

const bool& LineEditDelegate::getActiveRecycle() const { return activeRecycle; }

const QString& LineEditDelegate::getData() const { return this->data; }

QLabel* LineEditDelegate::getLabel() { return this->label; }

void LineEditDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
    if (!index.isValid()) return ;
	qDebug() << "setEditorData enter";
    if (index.row() < index.model()->rowCount() - 1 && index.column() == 1) {
        QString value = index.model()->data(index, Qt::EditRole).toString();

        QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);
        lineEditor->setText(value);
    }
}

QPushButton* LineEditDelegate::getRecycleBinButton() { return recycleBinButton; }

LineEditDelegate::~LineEditDelegate() {
    if (label) delete label;
    if (recycleBinButton) delete recycleBinButton;
}
