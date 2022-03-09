#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>

class ClickLabel : public QLabel {
	Q_OBJECT
public:
	explicit ClickLabel(const QString& text = QString(), QWidget* parent = nullptr);
	~ClickLabel();
signals:
	void clicked();
protected:
	void mousePressEvent(QMouseEvent* event);
};

#endif
