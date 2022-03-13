#include "clicklabel.h"

ClickLabel::ClickLabel(const QString& text, QWidget* parent) : QLabel(parent) {
    setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    setOpenExternalLinks(true);
    setTextFormat(Qt::RichText);
    setText(QString("<a href=\"#\">%1<\\a>").arg(text));
    color = make_unique<QString>("black");
    underline = make_unique<QString>("none");
    fontSize = make_unique<QString>("10");
    styleSheetStr = make_unique<QString>("");
}

ClickLabel::~ClickLabel() { }

//void ClickLabel::clicked() { ; }

void ClickLabel::setColor(const QString &color) {
    this->color->clear();
    this->color->append(color);
    unique_ptr<QString> res = make_unique<QString>("QLabel { color: %1; text-decoration: %2; font-size: %3px }");
    styleSheetStr = std::move(res);
    *styleSheetStr = styleSheetStr->arg(*(this->color), *underline, *fontSize);
    setStyleSheet(*styleSheetStr);
}

void ClickLabel::setTextDecoration(const QString& underline) {
    this->underline->clear();
    this->underline->append(underline);
    unique_ptr<QString> res = make_unique<QString>("QLabel { color: %1; text-decoration: %2; font-size: %3px }");
    styleSheetStr = std::move(res);
    *styleSheetStr = styleSheetStr->arg(*color,  *(this->underline), *fontSize);
    setStyleSheet(*styleSheetStr);
}

void ClickLabel::setFontSize(const int& fontSize) {
    this->fontSize->clear();
    this->fontSize->append(QString::number(fontSize));
    unique_ptr<QString> res = make_unique<QString>("QLabel { color: %1; text-decoration: %2; font-size: %3px }");
    styleSheetStr = std::move(res);
    *styleSheetStr = styleSheetStr->arg(*color,  *underline, *(this->fontSize));
    setStyleSheet(*styleSheetStr);
}

void ClickLabel::setFontSize(const QString& fontSize) {

}

void ClickLabel::mousePressEvent(QMouseEvent* event) { emit clicked(); }
