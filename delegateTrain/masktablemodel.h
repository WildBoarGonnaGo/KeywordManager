#ifndef MASKTABLEMODEL_H
#define MASKTABLEMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QMap>
#include <memory>
#include <QPixmap>
#include <QTableView>
#include "keyworddataset.h"
#include "drawitemdelegate.h"
#include "lineeditdelegate.h"

class MaskTableModel : public QAbstractTableModel {

	Q_OBJECT

	QMap<QString, QVariant> map;
	QList<KeywordDataSet> dataSetList;
    QPixmap documentImportPixmap;
    QPixmap documentExportPixmap;
	DrawItemDelegate* delegate;
	LineEditDelegate* lineEditDelegate;
    QTableView* view;
	int columns;
public:
	MaskTableModel(const QMap<QString, QVariant>& mapCp = QMap<QString, QVariant>(),
				   const QList<KeywordDataSet>& cpList = QList<KeywordDataSet>(),
				   QObject* parent = nullptr);
	MaskTableModel(const QMap<QString, QVariant>& mapCp = QMap<QString, QVariant>(),
                   QList<KeywordDataSet>&& mvList = std::move(QList<KeywordDataSet>()), QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant& value, int role = Qt::EditRole) override;
    void setTableView(QTableView* view);
	void setLastRowDelegate(DrawItemDelegate* delegate);
	const QList<KeywordDataSet>& getDataSetList() const;
	bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
private:
    Qt::CheckState checkTotalState() const;
public slots:
    void addNewList(const QString& dst);
	//void openEditor();
};

#endif
