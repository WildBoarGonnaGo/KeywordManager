#ifndef KEYWORDTABLEMODEL_H
#define KEYWORDTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QLabel>
#include <QVector>
#include <QModelIndex>
#include <QIcon>
#include <QPixmap>
#include <memory>
#include <random>
#include <QPalette>
#include <QVariant>
#include <QStack>
#include "clicklabel.h"

using std::unique_ptr;
using std::make_unique;
using std::move;
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;

Q_DECLARE_METATYPE(QLabel*);

class KeywordTableModel : public QAbstractTableModel
{
    QList<QMap<int, unique_ptr<QLabel>>> mapLabel;
    unique_ptr<QIcon> recycleBinIcon;
    unique_ptr<QPixmap> recycleBinPixmap;
    static QColor stdColors;
    static const QVector<int> colorList;
	unique_ptr<QIcon> documentUser;
    QStack<unique_ptr<QPalette>> stackPal;
	QString newListText;
	unique_ptr<QLabel> exportListLabel;
	unique_ptr<QLabel> importListLabel;
	unique_ptr<ClickLabel> clickLabel;
	unique_ptr<QLabel> plusLabel;
	QPixmap plusPixmap;
public:
    KeywordTableModel();
    //KeywordTableModel(const QList<QMap<int, unique_ptr<QLabel>>>& that) = delete;
    //KeywordTableModel(QList<QMap<int, unique_ptr<QLabel>>>&& that) noexcept;
    virtual int rowCount(const QModelIndex &parent = QModelIndex());
    virtual int columnCount(const QModelIndex &parent = QModelIndex());
    virtual bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
    virtual bool insertColumns(int row, int count, const QModelIndex& parent = QModelIndex());
	virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex());
	virtual bool removeColumns(int row, int count, const QModelIndex& parent = QModelIndex());
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual bool setData(const QModelIndex& index, const QVariant& value, int role);
	virtual Qt::ItemFlags flags(const QModelIndex& index) const;
	virtual ~KeywordTableModel();
};

#endif // KEYWORDTABLEMODEL_H
