#ifndef DB_DATABASEENTITY_H
#define DB_DATABASEENTITY_H

#include "entity.h"
#include "entity_list_for_database.h"

namespace meow {
namespace db {

class SessionEntity;
class TableEntity;

class DataBaseEntity : public Entity
{
public:
    explicit DataBaseEntity(const QString & dbName, SessionEntity * parent);
    virtual ~DataBaseEntity() override;
    virtual QString name() const override;
    virtual Connection * connection() const override;
    virtual int row() const override;
    virtual int childCount() override;
    virtual Entity * child(int row) override;

    virtual Type type() const override { return Type::Database; }
    virtual QVariant icon() const override;

    virtual db::ulonglong dataSize() const override;
    virtual bool hasDataSize() const override { return true; }

    bool childrenFetched() const;
    void clearChildren();

    int indexOf(Entity * entity);

    bool hasChild(const QString & name, const Entity::Type type);

    // TODO: entity should be shared_ptr?
    void appendEntity(EntityInDatabase * entity);

    bool removeEntity(EntityInDatabase * entity);

    SessionEntity * session() const;

    QString defaultCollation() const {
        return QString(); // TODO
    }

private:

    void initEntitiesIfNeed();

    QString _dbName;
    EntityListForDataBase * _entities;
    bool _entitiesWereInit;
};

} // namespace db
} // namespace meow

#endif // DB_DATABASEENTITY_H
