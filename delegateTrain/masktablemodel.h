#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QMap>
#include <memory>
#include "keyworddataset.h"

class MaskTableModel : public QAbstractTableModel {
	QMap<QString, QVariant> map;
	QList<KeywordDataSet> dataSetList;
	int columns;
public:
	MaskTableModel(const QMap<QString, QVariant>& mapCp = QMap<QString, QVariant>(),
				   const QList<KeywordDataSet>& cpList = QList<KeywordDataSet>(),
				   QObject* parent = nullptr);
	MaskTableModel(const QMap<QString, QVariant>& mapCp = QMap<QString, QVariant>(),
				   QList<KeywordDataSet>&& mvList, QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant& value, int role = Qt::EditRole) override;
};
