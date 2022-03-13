#ifndef CLICKLABEL_H
#define CLICKLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <memory>

using std::unique_ptr;
using std::make_unique;

class ClickLabel : public QLabel {
	Q_OBJECT
    unique_ptr<QString> color;
    unique_ptr<QString> underline;
    unique_ptr<QString> styleSheetStr;
    unique_ptr<QString> fontSize;
public:
	explicit ClickLabel(const QString& text = QString(), QWidget* parent = nullptr);
    void setColor(const QString& _color);
    void setTextDecoration(const QString& underline);
    void setFontSize(const int& fontSize);
    void setFontSize(const QString& fontSize);
	~ClickLabel();
signals:
	void clicked();
protected:
	void mousePressEvent(QMouseEvent* event);
};

#endif
