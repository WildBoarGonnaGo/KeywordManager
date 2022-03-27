#ifndef LINEEDITDELEGATE_H
#define LINEEDITDELEGATE_H

#include <QItemDelegate>
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QTableView>
#include <QPushButton>

class KeywordDataSet;

class LineEditDelegate : public QItemDelegate {
	Q_OBJECT
    QPixmap papersPixmap;
    QPixmap recycleBinPixmap;
	QLabel* label;
	QTableView* tableView;
    KeywordDataSet* dataSet;
    QPushButton* recycleBinButton;
	QString data;
    bool activeRecycle;
public:
	LineEditDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index = QModelIndex()) const override;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
	void setTableView(QTableView* tableView);
    void setActiveRecycle(const bool& activeRecycle);
    void setDataSet(KeywordDataSet* dataSet);
    const KeywordDataSet* getDataSet() const;
    const bool& getActiveRecycle() const;
	const QString& getData() const;
    QLabel* getLabel();
    QPushButton* getRecycleBinButton();
	~LineEditDelegate();
};

#endif
