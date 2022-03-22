#include "lineeditdelegate.h"
#include "masktablemodel.h"
#include <QLineEdit>
#include <QString>
#include <QClipboard>

LineEditDelegate::LineEditDelegate(QObject *parent) : QItemDelegate(parent), papersPixmap(":/delegateTrain/papers_icon.png"),
	label(new QLabel()), tableView(nullptr), data(QString()) {  }

QWidget *LineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	QLineEdit* editor = new QLineEdit(parent);
	return editor;
}

void LineEditDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
	QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);

	if (index.row() < model->rowCount() - 1 && index.column() == 1) {
        QString targetText = lineEdit->text();
        model->setData(index, targetText);
	}

}

void LineEditDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	editor->setGeometry(option.rect);
}

void LineEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) return ;
    if (index.row() < index.model()->rowCount() - 1 && index.column() == 1) {
		assert(label != nullptr && tableView != nullptr);

		label->setPixmap(papersPixmap.scaled(15, 15, Qt::KeepAspectRatio, Qt::SmoothTransformation));
		label->setText(index.data().toString());
        //tableView->setIndexWidget(index, label);
    } else QItemDelegate::paint(painter, option, index);
}

void LineEditDelegate::setTableView(QTableView* tableView) { this->tableView = tableView; }

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

LineEditDelegate::~LineEditDelegate() { if (label) delete label; }
