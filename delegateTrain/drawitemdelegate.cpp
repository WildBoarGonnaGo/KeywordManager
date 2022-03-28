#include "drawitemdelegate.h"
#include <QTextDocument>
#include <QPainter>
#include <QAbstractItemModel>
#include <QPoint>

DrawItemDelegate::DrawItemDelegate(QObject* parent) :
    QStyledItemDelegate(parent), view(nullptr), label(new QLabel()) {

}

void DrawItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid() || !view) return;
    const QAbstractItemModel* model = index.model();


    if (index.row() == model->rowCount() - 1 && index.column() == 1) {
        label->setTextFormat(Qt::RichText);
        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
		label->setOpenExternalLinks(false);
        label->setText(index.data().toString());
        view->setIndexWidget(index, label);
	}
	else QStyledItemDelegate::paint(painter, option, index);
}

void DrawItemDelegate::setTableView(QTableView *view) { this->view = view; }

const QLabel* DrawItemDelegate::getLabel() const { return label; }
