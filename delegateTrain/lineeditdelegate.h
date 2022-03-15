#include <QItemDelegate>
#include <QWidget>

class LineEditDelegate : public QItemDelegate {
	Q_OBJECT
public:
	LineEditDelegate(QObject *parent = nullptr);
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
	void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};
