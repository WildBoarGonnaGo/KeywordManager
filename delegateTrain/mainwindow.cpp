#include "mainwindow.h"
#include <QSize>
#include <QHeaderView>
#include <iostream>

MVCTestWidget::MVCTestWidget(const QMap<QString, QVariant>& map, const QList<KeywordDataSet>& dataSet, QWidget *parent) :
	QWidget(parent), _map(map), _list(dataSet), _model(new MaskTableModel(_map, _list)), _drawDelegate(new DrawItemDelegate()) {
	setWindowTitle("MVC Test System");
    setMinimumSize(QSize(640, 480));

    QString styleSheet = "QHeaderView::section { border: 0px; border-bottom: 0px; }";

    _tableView = new QTableView(this);
    _tableView->setMinimumSize(475, 480);
    _tableView->setShowGrid(false);
    _tableView->horizontalHeader()->setStyleSheet(styleSheet);
    _tableView->setModel(_model);
    _tableView->show();
    _tableView->setRowHeight(0, 25);
    _tableView->verticalHeader()->setVisible(false);
    _tableView->setColumnWidth(0, 25);
    _tableView->setColumnWidth(1, 400);
    _tableView->setColumnWidth(2, 25);
    _tableView->setColumnWidth(3, 25);
    _drawDelegate->setTableView(_tableView);
	_model->setLastRowDelegate(_drawDelegate);
	std::cout << "_drawDelegate = " << std::hex << _drawDelegate << std::endl;
    _tableView->setItemDelegateForRow(_model->rowCount() - 1, _drawDelegate);
	_model->setTableView(_tableView);
	setVisible(true);
}

MVCTestWidget::MVCTestWidget(const QMap<QString, QVariant>& map, QList<KeywordDataSet>&& dataSet, QWidget *parent) :
    QWidget(parent), _map(map), _list(dataSet), _model(new MaskTableModel(_map, _list)), _drawDelegate(new DrawItemDelegate()) {
    setWindowTitle("MVC Test System");
    setMinimumSize(QSize(640, 480));

    QString styleSheet = "QHeaderView::section { border: 0px; border-bottom: 0px; }";

    _tableView = new QTableView(this);
    _tableView->setMinimumSize(475, 480);
    _tableView->setShowGrid(false);
    _tableView->horizontalHeader()->setStyleSheet(styleSheet);
    _tableView->setModel(_model);
    _tableView->show();
    _tableView->verticalHeader()->setVisible(false);
    _tableView->setRowHeight(0, 25);
    _tableView->setColumnWidth(0, 25);
    _tableView->setColumnWidth(1, 400);
    _tableView->setColumnWidth(2, 25);
    _tableView->setColumnWidth(3, 25);
    _drawDelegate->setTableView(_tableView);
	_model->setLastRowDelegate(_drawDelegate);
	std::cout << "_drawDelegate->getLabel() = " << std::hex << _drawDelegate->getLabel() << std::endl;
    _tableView->setItemDelegateForRow(_model->rowCount() - 1, _drawDelegate);
	_model->setTableView(_tableView);
	std::cout << "_tableView->model() = " << std::hex <<_tableView->model() << std::endl;

    setVisible(true);
}


MVCTestWidget::~MVCTestWidget() {
    /*
    QAbstractItemModel* _model;
    QTableView* _tableView;
    DrawItemDelegate* _drawDelegate;
    */
    if (_model) delete _model;
    if (_tableView) delete _tableView;
    if (_drawDelegate) delete _drawDelegate;
}
