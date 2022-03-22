#include "keyworddataset.h"

KeywordDataSet::KeywordDataSet() :
    plusImage(":/delegateTrain/plus_icon.png"),
    documentImage(":/delegateTrain/papers_icon.png"),
    recycleBinImage(":/delegateTrain/recycle_bin.png"),
    upImage(":/delegateTrain/up_document.png"),
    data(QString()),
    lineEditDelegate(new LineEditDelegate()),
    checkState(0)
{

}

KeywordDataSet::KeywordDataSet(const QString& cpData) :
    plusImage(":/delegateTrain/plus_icon.png"),
    documentImage(":/delegateTrain/papers_icon.png"),
    recycleBinImage(":/delegateTrain/recycle_bin.png"),
    upImage(":/delegateTrain/up_document.png"),
    data(cpData),
    lineEditDelegate(new LineEditDelegate()),
    checkState(0)
{

}

KeywordDataSet::KeywordDataSet(const QString&& mvData) :
    plusImage(":/delegateTrain/plus_icon.png"),
    documentImage(":/delegateTrain/papers_icon.png"),
    recycleBinImage(":/delegateTrain/recycle_bin.png"),
    upImage(":/delegateTrain/up_document.png"),
    data(std::move(mvData)),
    lineEditDelegate(new LineEditDelegate()),
    checkState(0)
{

}

const QImage& KeywordDataSet::getPlusImage() const { return plusImage; }

const QImage& KeywordDataSet::getDocumentImage() const { return documentImage; }

const QImage& KeywordDataSet::getRecycleBinImage() const { return recycleBinImage; }

const QImage& KeywordDataSet::getUpImage() const { return upImage; }

void KeywordDataSet::setData(const QString& data) { this->data = data; }

void KeywordDataSet::setData(QString&& data) { this->data = std::move(data); }

const QString& KeywordDataSet::getData() const { return data; }

void KeywordDataSet::setCheckState(const int& checkState) { this->checkState = checkState; }

void KeywordDataSet::setCheckState(int&& checkState) { this->checkState = std::move(checkState); }

const int& KeywordDataSet::getCheckState() const { return checkState; }

LineEditDelegate* KeywordDataSet::getLineEditDelegate() { return lineEditDelegate; }
