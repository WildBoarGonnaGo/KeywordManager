#include <QAbstractTableModel>
#include <QVariant>
#include <QModelIndex>
#include <QMap>
#include <memory>

class MaskTableModel : public QAbstractTableModel {
	QMap<QString, QVariant> map;
	int columns;
public:
	MaskTableModel(const QMap<QString, QVariant>& map, QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
