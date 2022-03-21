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
		//this->data = lineEdit->text();
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
		tableView->setIndexWidget(index, label);
    }
}

void LineEditDelegate::setTableView(QTableView* tableView) { this->tableView = tableView; }

const QString& LineEditDelegate::getData() const { return this->data; }

LineEditDelegate::~LineEditDelegate() { if (label) delete label; }
