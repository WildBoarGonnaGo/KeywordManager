#include "clicklabel.h"


explicit ClickLabel::ClickLabel(const QString& text = QString(), QWidget* parent = nullptr) : QLabel(parent) { setText(text); }

ClickLabel::~ClickLabel();

void ClickLabel::clicked() { ; }

void ClickLabel::mousePressEvent(QMouseEvent* event) { emit clicked(); }
