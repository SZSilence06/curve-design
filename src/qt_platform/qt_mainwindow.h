#ifndef QT_MAINWINDOWN_H
#define QT_MAINWINDOWN_H

#include <QMainWindow>
#include <QGLWidget>
#include <QSignalMapper>
#include <QLabel>
#include <QAction>

#ifndef Q_MOC_RUN
#include "qevent_adapter.h"
#include "cmenu.h"
#include <QHBoxLayout>
#endif

namespace framework
{
    class qt_wnd_server;

    class  MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);
        QHBoxLayout* createToolBar(QWidget* parent);
        QStatusBar * createStatusBar(int width, int height);

        void createMenus();

        virtual ~MainWindow();

        enum LABEL_NAME { STATE_LABEL, WARNING_LABEL };
        void set_status_label(LABEL_NAME, const QString &);

        enum State{
            STATE_NOMODEL,
            STATE_HASMODEL
        };

        void enter_state(State state);

    protected:
        virtual void keyPressEvent(QKeyEvent* event);
        virtual void keyReleaseEvent(QKeyEvent* event);

    private:
        void init_tab_page();
        QWidget* init_osg3d(const std::string & osgwidget_name);
        QWidget* init_osg2d(const std::string & osgwidget_name);

        QLayout* set_osg3d_layout(const std::string & viewername, QWidget * parent);
        QLayout* set_osg2d_layout(const std::string & viewername, QWidget * parent);

        void on_enter_state(State state);
        void on_leave_state(State state);
       
        void addButtonToToolBar(QToolBar *tool_bar, QSignalMapper *signal_mapper, const std::string &action_key,
            const std::string &icon_file, const std::string &tip_string);
        std::shared_ptr<qt_wnd_server> qws_;
        std::vector<QLabel*> statusLabels_; // status_label

        State state = STATE_NOMODEL;

        //menus
        QMenu* menu_tool_ = nullptr;

        //menu_actions
        QAction* action_tool_select_ = new QAction("Select", this);
        QAction* action_tool_view_ = new QAction("View", this);
        QAction* action_export_control_point_ = new QAction("Export Control Point", this);
        QAction* action_import_control_point_ = new QAction("Import Control Point", this);

        //Current tool
        QAction* current_tool_ = action_tool_view_;
    };
}

#endif // QT_OSGWIDGET_H
