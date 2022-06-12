#ifndef DB_MYSQL_DATA_TYPE_H
#define DB_MYSQL_DATA_TYPE_H

#include "data_type.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <mysql.h>
#else
#include <mysql/mysql.h>
#endif

namespace meow {
namespace db {

// rm!
inline DataTypeIndex dataTypeFromMySQLDataType(const int nativeDatatype,
                                               bool isBinary)
{
    if (isBinary) {

        switch (nativeDatatype) {
        case FIELD_TYPE_STRING: // char
            return DataTypeIndex::Binary;

        case FIELD_TYPE_VAR_STRING: // varchar
            return DataTypeIndex::Varbinary;

        case FIELD_TYPE_BLOB:
            return DataTypeIndex::Blob;
        default:
            break;
        }
    }

    switch (nativeDatatype) {
    case FIELD_TYPE_TINY:
        return DataTypeIndex::TinyInt;

    case FIELD_TYPE_SHORT:
        return DataTypeIndex::SmallInt;

    case FIELD_TYPE_INT24:
        return DataTypeIndex::MediumInt;

    case FIELD_TYPE_LONG:
        return DataTypeIndex::Int;

    case FIELD_TYPE_LONGLONG:
        return DataTypeIndex::BigInt;

    case FIELD_TYPE_FLOAT:
        return DataTypeIndex::Float;

    case FIELD_TYPE_DOUBLE:
        return DataTypeIndex::Double;

    case FIELD_TYPE_NEWDECIMAL:
        return DataTypeIndex::Decimal;

    case FIELD_TYPE_DATE:
        return DataTypeIndex::Date;

    case FIELD_TYPE_TIME:
        return DataTypeIndex::Time;

    case FIELD_TYPE_YEAR:
        return DataTypeIndex::Year;

    case FIELD_TYPE_DATETIME:
        return DataTypeIndex::DateTime;

    case FIELD_TYPE_TIMESTAMP:
        return DataTypeIndex::Timestamp;

    case FIELD_TYPE_STRING:
        return DataTypeIndex::Char;

    case FIELD_TYPE_VAR_STRING:
        return DataTypeIndex::Varchar;

    case FIELD_TYPE_TINY_BLOB:
        return DataTypeIndex::TinyText;

    case FIELD_TYPE_BLOB:
        return DataTypeIndex::Text;

    case FIELD_TYPE_MEDIUM_BLOB:
        return DataTypeIndex::MediumText;

    case FIELD_TYPE_LONG_BLOB:
        return DataTypeIndex::LongText;

    case FIELD_TYPE_ENUM:
        return DataTypeIndex::Enum;

    case FIELD_TYPE_SET:
        return DataTypeIndex::Set;

    case FIELD_TYPE_BIT:
        return DataTypeIndex::Bit;

    case FIELD_TYPE_GEOMETRY: // TODO: point/polygon/etc
        return DataTypeIndex::Geometry;

    default:
        return DataTypeIndex::None;
    }
}

} // namespace db
} // namespace meow

#endif // DB_MYSQL_DATA_TYPE_H

