#include "lineeditdelegate.h"
#include <QLineEdit>
#include <QString>

LineEditDelegate::LineEditDelegate(QObject *parent) : QItemDelegate(parent), papersPixmap(":/delegateTrain/papers_icon.png") {  }

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	QLineEdit* editor = new QLineEdit(parent);
	return editor;
}

void LineEditDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
	QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
	QString data = lineEdit->text();
	model->setData(index, data);
}

void LineEditDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	editor->setGeometry(option.rect);
}

void LineEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) return ;
    if (index.row() < index.model()->rowCount() - 1 && index.column() == 1) {

    }
}
