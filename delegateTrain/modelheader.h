#ifndef MODELHEADER_H
#define MODELHEADER_H

#include <QHeaderView>
#include <QWidget>
#include "masktablemodel.h"

class ModelHeader : public QHeaderView {
	Q_OBJECT

public:
	ModelHeader(Qt::Orientation orientation, QWidget* parent = nullptr, MaskTableModel* otherModel = nullptr);
	const bool& getCheckState() const;
	void setCheckState(const bool& checkState);
signals:
	void checkBoxClicked(bool state);
protected:
	void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
	void mousePressEvent(QMouseEvent* event) override;
private:
	MaskTableModel* model;
	bool checkState;
	void redrawCheckBox();
};

#endif
