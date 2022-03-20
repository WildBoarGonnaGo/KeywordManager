#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H

#include <QItemDelegate>
#include <QWidget>
#include <QPixmap>
#include <QLabel>

class LineEditDelegate : public QItemDelegate {
	Q_OBJECT
    QPixmap papersPixmap;
    QLabel* label;
public:
	LineEditDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif
