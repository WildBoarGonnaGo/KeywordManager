#include "mainwindow.h"
#include <QSize>
#include <QHeaderView>

MVCTestWidget::MVCTestWidget(const QMap<QString, QVariant>& map, QWidget *parent) :
	QWidget(parent), _map(map), _model(new MaskTableModel(_map)) {
	setWindowTitle("MVC Test System");
	setMinimumSize(QSize(400, 400));

	_tableView = new QTableView(this);
	_tableView->setModel(_model);
	_tableView->show();
    _tableView->verticalHeader()->setVisible(false);

	setVisible(true);
}
