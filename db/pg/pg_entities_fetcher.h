#ifndef DB_PG_ENTITIES_FETCHER_H
#define DB_PG_ENTITIES_FETCHER_H

#include "db/entity/entities_fetcher.h"

namespace meow {
namespace db {

class PGConnection;

class PGEntitiesFetcher : public DataBaseEntitiesFetcher
{
public:
    PGEntitiesFetcher(PGConnection * connection);

    virtual QList<EntityPtr> run(const QString & dbName) override;
private:
    void fetchTablesViews(const QString & dbName,
                          QList<EntityPtr> * toList);

    void fetchStoredFunctions(const QString & dbName,
                              QList<EntityPtr> * toList);

    inline QString qu(const char * identifier) const;
};

} // namespace db
} // namespace meow

#endif // DB_PG_ENTITIES_FETCHER_H
