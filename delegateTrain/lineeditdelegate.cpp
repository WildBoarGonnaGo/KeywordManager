#include "lineeditdelegate.h"
#include <QLineEdit>
#include <QString>

LineEditDelegate::LineEditDelegate(QObject *parent) : QItemDelegate(parent) {  }

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
