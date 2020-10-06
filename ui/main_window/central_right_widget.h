#ifndef UI_CENTRALRIGHTWIDGET_H
#define UI_CENTRALRIGHTWIDGET_H

#include <QtWidgets>
#include "models/ui/central_right_widget_model.h"
#include "central_right/host/central_right_host_tab.h"
#include "central_right/database/central_right_database_tab.h"
#include "central_right/table/central_right_table_tab.h"
#include "central_right/data/central_right_data_tab.h"
#include "central_right/query/central_right_query_tab.h"
#include "central_right/view/central_right_view_tab.h"

namespace meow {
namespace ui {
namespace main_window {

class CentralRightWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralRightWidget(QWidget *parent = 0);

    void setActiveDBEntity(db::Entity * entity);

    bool onGlobalRefresh();

    Q_SLOT void onBeforeEntityEditing();

    Q_SLOT void onEntityEdited(db::Entity * entity);

private:

    void createRootTabs();
    bool onHostTab() const;
    bool onDatabaseTab() const;
    bool onEntityTab() const;
    bool onDataTab() const;
    bool onQueryTab() const;

    Q_SLOT void rootTabChanged(int index);

    central_right::HostTab * hostTab();
    central_right::DatabaseTab * databaseTab();
    central_right::TableTab * tableTab();
    central_right::ViewTab * viewTab();
    central_right::DataTab * dataTab();
    central_right::QueryTab * queryTab();

    void removeAllRootTabs();
    bool removeHostTab();
    bool removeQueryTabs();
    bool removeDatabaseTab();
    bool removeTableTab();
    bool removeViewTab();
    bool removeDataTab();
    void removeEntityTabsExcept(db::Entity::Type except);

    bool removeTab(QWidget * tab);

    models::ui::CentralRightWidgetModel _model;

    QTabWidget  * _rootTabs;
    central_right::HostTab * _hostTab;
    central_right::DatabaseTab * _databaseTab;
    central_right::TableTab * _tableTab;
    central_right::ViewTab * _viewTab;
    central_right::DataTab * _dataTab;
    central_right::QueryTab * _queryTab;
};


} // namespace meow
} // namespace ui
} // namespace main_window

#endif // UI_CENTRALRIGHTWIDGET_H
