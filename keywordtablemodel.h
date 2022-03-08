#ifndef KEYWORDTABLEMODEL_H
#define KEYWORDTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QLabel>
#include <QVector>
#include <QModelIndex>
#include <QIcon>
#include <QPixmap>
#include <memory>

using std::unique_ptr;
using std::make_unique;
using std::move;

class KeywordTableModel : public QAbstractTableModel
{
    QList<QMap<int, unique_ptr<QWidget>>> mapLabel;
    unique_ptr<QIcon> recycleBinIcon;
    unique_ptr<QPixmap> recycleBinPixmap;
    static QColor stdColors;
    static QVector<int> colorList = { stdColors.blue(), stdColors.red(), stdColors.green(),
                                      stdColors.yellow(), stdColors.cyan(), stdColors.magenta(),
                                      stdColors.black() };
public:
    KeywordTableModel();
    KeywordTableModel(const QList<QMap<int, unique_ptr<QWidget>>>& that) = delete;
    KeywordTableModel(QList<QMap<int, unique_ptr<QWidget>>>&& that) noexcept;
    virtual int rowCount(const QModelIndex &parent = QModelIndex());
    virtual int columnCount(const QModelIndex &parent = QModelIndex());
    virtual bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex());
    virtual bool insertColumns(int row, int count, const QModelIndex& parent = QModelIndex());

};

#endif // KEYWORDTABLEMODEL_H
