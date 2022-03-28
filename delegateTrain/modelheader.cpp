#include "modelheader.h"
#include <QStyleOptionButton>
#include <QPainter>

ModelHeader::ModelHeader(Qt::Orientation orientation, QWidget* parent, MaskTableModel* otherModel) :
	QHeaderView(orientation, parent), model(otherModel) {
	checkState = false;
}

const bool& ModelHeader::getCheckState() const { return checkState; }

void ModelHeader::setCheckState(const bool& checkState) {
	if (this->checkState != checkState) {
		this->checkState = checkState;
		model->setCheckTotalState(checkState);
		redrawCheckBox();
	}
}

void ModelHeader::redrawCheckBox() { viewport()->update(); }

void ModelHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const {
	painter->save();
	QHeaderView::paintSection(painter, rect, logicalIndex);
	painter->restore();
	if (!logicalIndex) {
		QStyleOptionButton option;
		option.rect = QRect(rect.left() + 3, rect.top() + 4, 20, 20);
		option.state = QStyle::State_Enabled | QStyle::State_Active;
		option.state |= (checkState) ? QStyle::State_On : QStyle::State_Off;
		this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
	}
}

void ModelHeader::mousePressEvent(QMouseEvent* event) {
	setCheckState(!getCheckState());
	emit checkBoxClicked(getCheckState());
}


