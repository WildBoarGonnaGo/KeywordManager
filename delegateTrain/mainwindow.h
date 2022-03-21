#include <QWidget>
#include "masktablemodel.h"
#include <QTableView>
#include "drawitemdelegate.h"
#include "lineeditdelegate.h"

class MVCTestWidget : public QWidget {
	Q_OBJECT
	QMap<QString, QVariant> _map;
    QList<KeywordDataSet> _list;
	MaskTableModel* _model;
	QTableView* _tableView;
    DrawItemDelegate* _drawDelegate;
public:
    MVCTestWidget(const QMap<QString, QVariant>& map = QMap<QString, QVariant>(),
                  const QList<KeywordDataSet>& dataSet = QList<KeywordDataSet>(), QWidget* parent = nullptr);
    MVCTestWidget(const QMap<QString, QVariant>& map = QMap<QString, QVariant>(),
                  QList<KeywordDataSet>&& dataSet = std::move(QList<KeywordDataSet>()), QWidget* parent = nullptr);
    ~MVCTestWidget();
};
