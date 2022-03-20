#ifndef KEYWORDDATASET_H
#define KEYWORDDATASET_H

#include <QImage>
#include <memory>

class KeywordDataSet
{
    QImage plusImage;
    QImage documentImage;
    QImage recycleBinImage;
    QImage upImage;
    QString data;
    int checkState;
public:
    KeywordDataSet();
    KeywordDataSet(const QString& cpData);
    KeywordDataSet(const QString&& mvData);
    const QImage& getPlusImage() const;
    const QImage& getDocumentImage() const;
    const QImage& getRecycleBinImage() const;
    const QImage& getUpImage() const;
    void setData(const QString& data);
    void setData(QString&& data);
    const QString& getData() const;
    void setCheckState(const int& checkState);
    void setCheckState(int&& checkState);
    const int& getCheckState() const;
};

#endif // KEYWORDDATASET_H
