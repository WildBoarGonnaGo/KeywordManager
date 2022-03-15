#include <QWidget>
#include "masktablemodel.h"
#include <QTableView>

class MVCTestWidget : public QWidget {
	Q_OBJECT
	QMap<QString, QVariant> _map;
	QAbstractItemModel* _model;
	QTableView* _tableView;
public:
	MVCTestWidget(const QMap<QString, QVariant>& map, QWidget* parent = nullptr);

};
