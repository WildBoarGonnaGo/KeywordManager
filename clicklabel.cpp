#include "clicklabel.h"


ClickLabel::ClickLabel(const QString& text, QWidget* parent) : QLabel(parent) { setText(text); }

ClickLabel::~ClickLabel() { }

void ClickLabel::clicked() { ; }

void ClickLabel::mousePressEvent(QMouseEvent* event) { emit clicked(); }
