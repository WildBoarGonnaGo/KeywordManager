#ifndef DRAWITEMDELEGATE_H
#define DRAWITEMDELEGATE_H

#include <QString>
#include <QLabel>
#include <QStyledItemDelegate>
#include <QTableView>

class DrawItemDelegate : public QStyledItemDelegate
{
    QTableView* view;
    QLabel* label;
public:
    DrawItemDelegate(QObject* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setTableView(QTableView* view);
    const QLabel* getLabel() const;
};

#endif // DRAWITEMDELEGATE_H
