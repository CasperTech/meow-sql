#include "base_data_table_model.h"
#include "app/app.h"
#include <QDebug>

namespace meow {
namespace models {
namespace db {

BaseDataTableModel::BaseDataTableModel(meow::db::QueryData * queryData,
                                         QObject *parent)
    : QAbstractTableModel(parent),
      _queryData(queryData),
      _rowCount(0),
      _colCount(0)
{

}

void BaseDataTableModel::setRowCount(int newRowCount)
{
    _rowCount = newRowCount;
}

void BaseDataTableModel::setColumnCount(int newColumnCount)
{
    _colCount = newColumnCount;
}

int BaseDataTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (_colCount != -1) {
        return _colCount;
    }
    return _queryData->columnCount();
}

int BaseDataTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    if (_rowCount != -1) {
        return _rowCount;
    }
    return _queryData->rowCount();
}

Qt::ItemFlags BaseDataTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }

    return QAbstractItemModel::flags(index);
}

QVariant BaseDataTableModel::headerData(int section,
                                    Qt::Orientation orientation,
                                    int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        return _queryData->columnName(section);
    }

    return QVariant();
}

QVariant BaseDataTableModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= rowCount()) {
        return QVariant();
    }

    switch (role) {


    case Qt::EditRole:
        // TODO: EnsureFullRow
        _queryData->prepareEditing(); // Let's do it here
        return _queryData->editDataAt(index.row(), index.column());
    case Qt::DisplayRole:        
        return _queryData->displayDataAt(index.row(), index.column());

    case Qt::ForegroundRole: {
        auto textSettings = meow::app()->settings()->textSettings();
        auto dataType = _queryData->columnDataTypeCategory(index.column());
        if (dataType != meow::db::DataTypeCategoryIndex::None) {
            bool isNull = _queryData->isNullAt(index.row(), index.column());
            if (isNull == false) {
                return textSettings->colorForDataType(dataType);
            } else {
                return textSettings->colorForDataTypeNULL(dataType);
            }
        }
        return QVariant();
    }

    default:
        return QVariant();
    }

}

} // namespace db
} // namespace models
} // namespace meow
