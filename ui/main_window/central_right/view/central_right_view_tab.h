#ifndef UI_CENTRAL_RIGHT_VIEWTAB_H
#define UI_CENTRAL_RIGHT_VIEWTAB_H

#include <QtWidgets>
#include "ui/common/sql_editor.h"
#include "models/forms/view_form.h"

namespace meow {

namespace db {
    class ViewEntity;
}

namespace ui {
namespace main_window {
namespace central_right {

class ViewTab : public QWidget
{
public:
    explicit ViewTab(QWidget * parent = nullptr);

    void setView(db::ViewEntity * view);

private:
    void createWidgets();
    void fillDataFromForm();

    QLabel * _nameLabel;
    QLineEdit * _nameEdit;

    QLabel * _definerLabel;
    QComboBox * _definerComboBox;

    QLabel * _algorithmLabel;
    QComboBox * _algorithmComboBox;

    QLabel * _securityLabel;
    QComboBox * _securityComboBox;

    QLabel * _checkOptionLabel;
    QComboBox * _checkOptionComboBox;

    QLabel * _selectLabel;
    ui::common::SQLEditor * _selectEdit;

    models::forms::ViewForm _form;
};

} // namespace central_right
} // namespace main_window
} // namespace ui
} // namespace meow

#endif // UI_CENTRAL_RIGHT_VIEWTAB_H
