#include "central_right_widget_model.h"
#include "db/connection.h"
#include <QObject> // tr()

namespace meow {
namespace models {
namespace ui {

CentralRightWidgetModel::CentralRightWidgetModel()
    : _entityHolder()
{

}

bool CentralRightWidgetModel::setCurrentEntity(db::Entity * currentEntity)
{
    return _entityHolder.setCurrentEntity(currentEntity);
}

meow::db::Entity * CentralRightWidgetModel::currentEntity() const
{
    return _entityHolder.currentEntity();
}

bool CentralRightWidgetModel::connectionChanged() const
{
    return _entityHolder.connectionChanged();
}

bool CentralRightWidgetModel::databaseChanged() const
{
    return _entityHolder.databaseChanged();
}

bool CentralRightWidgetModel::hasDatabase() const
{
    return _entityHolder.hasDatabase();
}

bool CentralRightWidgetModel::hasDataTab() const
{
    if (_entityHolder.currentEntity() == nullptr) {
        return false;
    }

    if (_entityHolder.currentEntity()->isNew() == true) {
        return false;
    }

    if (_entityHolder.currentEntity()->type() == db::Entity::Type::Table ||
        _entityHolder.currentEntity()->type() == db::Entity::Type::View)
    {
        return _entityHolder.currentEntity()->connection()
                ->features()->supportsViewingTablesData();
    }

    return false;
}

bool CentralRightWidgetModel::hasEntityTab() const
{
    if (_entityHolder.currentEntity() == nullptr) {
        return false;
    }
    // TODO: other types
    if (_entityHolder.currentEntity()->type() == db::Entity::Type::Table) {
        return _entityHolder.currentEntity()->connection()
                ->features()->supportsViewingTables();
    }

    if (_entityHolder.currentEntity()->type() == db::Entity::Type::View) {
        return _entityHolder.currentEntity()->connection()
                ->features()->supportsViewingViews();
    }

    return false;
}

bool CentralRightWidgetModel::hasQueryTab() const
{
    return _entityHolder.currentEntity() != nullptr;
}

QString CentralRightWidgetModel::titleForHostTab() const
{
    if (_entityHolder.currentEntity()) {

        const db::ConnectionParameters * params = _entityHolder.currentEntity()
                ->connection()->connectionParams();

        QString host;
        if (params->isFilebased()) {
            host = params->fileNameShort();
        } else {
            if (params->isSSHTunnel()) {
                host = params->sshTunnel().host() + " (SSH)";
            } else {
                host = params->hostName();
            }
        }

        return QObject::tr("Host") + ": " + host;
    } else {
        return QObject::tr("Host");
    }
}

QString CentralRightWidgetModel::titleForDatabaseTab() const
{
    if (_entityHolder.currentEntity()) {

        QString database = _entityHolder.currentEntity()
                ->connection()->database();

        return QObject::tr("Database") + ": " + database;
    }

    return QObject::tr("Database");
}

QString CentralRightWidgetModel::titleForEntityTab() const
{
    if (_entityHolder.currentEntity()) {
        switch (_entityHolder.currentEntity()->type()) {

        case meow::db::Entity::Type::Table:
            return titleForTableTab();

        case meow::db::Entity::Type::View:
            return titleForViewTab();

        default:
            break;
        }
    }
    return QString();
}

QString CentralRightWidgetModel::titleForTableTab() const
{
    if (_entityHolder.currentEntity() &&
        _entityHolder.currentEntity()->type() == meow::db::Entity::Type::Table) {
        QString title = QObject::tr("Table") + ": ";
        if (_entityHolder.currentEntity()->isNew()) {
            title += "[" + QObject::tr("Untitled") + "]";
        } else {
            title += _entityHolder.currentEntity()->name();
        }
        return title;
    }

    return QObject::tr("Table");
}

QString CentralRightWidgetModel::titleForViewTab() const
{
    if (_entityHolder.currentEntity() &&
        _entityHolder.currentEntity()->type() == meow::db::Entity::Type::View) {
        QString title = QObject::tr("View") + ": ";
        if (_entityHolder.currentEntity()->isNew()) {
            title += "[" + QObject::tr("Untitled") + "]";
        } else {
            title += _entityHolder.currentEntity()->name();
        }
        return title;
    }

    return QObject::tr("View");
}

QString CentralRightWidgetModel::titleForDataTab() const
{
    return QObject::tr("Data");
}

QString CentralRightWidgetModel::titleForQueryTab() const
{
    return QObject::tr("Query");
}

int CentralRightWidgetModel::indexForQueryTab() const
{
    if (hasDataTab()) {
        return static_cast<int>(CentralRightWidgetTabs::Data) + 1;

    } else if (hasEntityTab()) {
        return static_cast<int>(CentralRightWidgetTabs::Entity) + 1;

    } else if (hasDatabase()) {
        return static_cast<int>(CentralRightWidgetTabs::Database) + 1;
    }

    return static_cast<int>(CentralRightWidgetTabs::Host) + 1;
}

int CentralRightWidgetModel::indexForDataTab() const
{
    if (hasDataTab()) {
        db::Entity::Type curType = _entityHolder.currentEntity()->type();
        if (curType == db::Entity::Type::Table
                || curType == db::Entity::Type::View) {

            if (hasEntityTab()) {
                return static_cast<int>(CentralRightWidgetTabs::Entity) + 1;
            } else {
                return static_cast<int>(CentralRightWidgetTabs::Database) + 1;
            }
        }
    }
    return -1;
}

} // namespace ui
} // namespace models
} // namespace meow
