#include "mainwindow.h"
#include <QSize>
#include <QHeaderView>
#include <iostream>
#include <QIcon>

MVCTestWidget::MVCTestWidget(const QMap<QString, QVariant>& map, const QList<KeywordDataSet>& dataSet, QWidget *parent) :
	QWidget(parent), _map(map), _list(dataSet), _model(new MaskTableModel(_map, _list)), _drawDelegate(new DrawItemDelegate()),
	header(nullptr) {
	setWindowTitle("Диспетчер списков ключевых слов");
	setWindowIcon(QIcon(":/delegateTrain/abc_icon.png"));
    setMinimumSize(QSize(640, 480));

    QString styleSheet = "QHeaderView::section { border: 0px; border-bottom: 0px; }";

    _tableView = new QTableView(this);
	header = new ModelHeader(Qt::Horizontal, _tableView, _model);
	_tableView->setMinimumSize(500, 480);
    _tableView->setShowGrid(false);
	_tableView->setHorizontalHeader(header);
    _tableView->horizontalHeader()->setStyleSheet(styleSheet);
    _tableView->setModel(_model);
    _tableView->show();
    _tableView->setRowHeight(0, 25);
    _tableView->verticalHeader()->setVisible(false);
    _tableView->setColumnWidth(0, 25);
    _tableView->setColumnWidth(1, 400);
    _tableView->setColumnWidth(2, 25);
    _tableView->setColumnWidth(3, 25);
    _tableView->setMouseTracking(true);
    _drawDelegate->setTableView(_tableView);
	_model->setLastRowDelegate(_drawDelegate);
    _tableView->setItemDelegateForRow(_model->rowCount() - 1, _drawDelegate);
	_model->setTableView(_tableView);
	setVisible(true);
}

MVCTestWidget::MVCTestWidget(const QMap<QString, QVariant>& map, QList<KeywordDataSet>&& dataSet, QWidget *parent) :
	QWidget(parent), _map(map), _list(dataSet), _model(new MaskTableModel(_map, _list)), _drawDelegate(new DrawItemDelegate()),
	header(nullptr) {
	setWindowTitle("Диспетчер списков ключевых слов");
	setWindowIcon(QIcon(":/delegateTrain/abc_icon.png"));
    setMinimumSize(QSize(640, 480));

    QString styleSheet = "QHeaderView::section { border: 0px; border-bottom: 0px; }";

    _tableView = new QTableView(this);
	header = new ModelHeader(Qt::Horizontal, _tableView, _model);
	_tableView->setMinimumSize(500, 480);
    _tableView->setShowGrid(false);
	_tableView->setHorizontalHeader(header);
    _tableView->horizontalHeader()->setStyleSheet(styleSheet);
    _tableView->setModel(_model);
    _tableView->show();
    _tableView->verticalHeader()->setVisible(false);
    _tableView->setRowHeight(0, 25);
    _tableView->setColumnWidth(0, 25);
    _tableView->setColumnWidth(1, 400);
    _tableView->setColumnWidth(2, 25);
    _tableView->setColumnWidth(3, 25);
    _tableView->setMouseTracking(true);
    _drawDelegate->setTableView(_tableView);
	_model->setLastRowDelegate(_drawDelegate);
    _tableView->setItemDelegateForRow(_model->rowCount() - 1, _drawDelegate);
	_model->setTableView(_tableView);

    setVisible(true);
}

MaskTableModel* MVCTestWidget::getModel() { return _model; }

MVCTestWidget::~MVCTestWidget() {
    if (_model) delete _model;
    if (_tableView) delete _tableView;
    if (_drawDelegate) delete _drawDelegate;
}
