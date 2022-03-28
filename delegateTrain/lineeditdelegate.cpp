#include "lineeditdelegate.h"
#include <QLineEdit>
#include <QString>
#include <QClipboard>
#include <QPainter>
#include <QDebug>
#include <QPointF>
#include <QRect>
#include <QIcon>
#include <QPainterPath>
#include <QPen>

LineEditDelegate::LineEditDelegate(QObject *parent) : QItemDelegate(parent),
    papersPixmap(":/delegateTrain/papers_icon.png"),
    recycleBinPixmap(":/delegateTrain/recycle_bin.png"),
    label(new QLabel()), tableView(nullptr),
    recycleBinButton(new QPushButton()),
	data(QString()), activeRecycle(false),
	color(Qt::color0) {
    QIcon recycleBinIcon(recycleBinPixmap.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    recycleBinButton->setIcon(recycleBinIcon);
    recycleBinButton->setFlat(true);
	recycleBinButton->setFocusPolicy(Qt::NoFocus);
	recycleBinButton->setStyleSheet("QPushButton { border: 1px solid transparent }");
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

    if (!index.isValid()) return ;
    if (index.row() < rowPos && index.column() == 1) {
		QPointF iconPoint(option.rect.left(), option.rect.top() + 8);
		QPointF textPoint(option.rect.left() + 25, option.rect.bottom() - 8);

		painter->drawPixmap(iconPoint, papersPixmap.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		painter->drawText(textPoint, index.model()->data(index, Qt::EditRole).toString());
    }
    if (index.row() < rowPos && index.column() == 2) {
		recycleBinButton->setGeometry(option.rect.left() - 2, option.rect.top() + 3, 20, 25);
        this->tableView->setIndexWidget(index, recycleBinButton);
    }
	if (index.row() < rowPos && index.column() == 3 && color != Qt::color0) {
		QRectF targetRect(option.rect.left() + 1, option.rect.top() + 8, 15, 15);

		painter->setRenderHint(QPainter::Antialiasing);
		QPainterPath path;
		path.addRect(targetRect);
		QPen pen(Qt::darkGray, 2);
		painter->setPen(pen);
		painter->fillPath(path, color);
		painter->drawPath(path);
	}
    else QItemDelegate::paint(painter, option, index);
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
    if (index.row() < index.model()->rowCount() - 1 && index.column() == 1) {
        QString value = index.model()->data(index, Qt::EditRole).toString();

        QLineEdit* lineEditor = static_cast<QLineEdit*>(editor);
        lineEditor->setText(value);
    }
}

QPushButton* LineEditDelegate::getRecycleBinButton() { return recycleBinButton; }

void LineEditDelegate::setColor(const Qt::GlobalColor& color) { this->color = color; }

const Qt::GlobalColor& LineEditDelegate::getColor() const { return color; }

LineEditDelegate::~LineEditDelegate() {
    if (label) delete label;
    if (recycleBinButton) delete recycleBinButton;
}
