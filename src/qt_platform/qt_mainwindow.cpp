#include <cassert>
#include <stdexcept>
#include <vector>
#include <iostream>

#ifndef Q_MOC_RUN
#include "qt_mainwindow.h"
#include <osg/Material>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osg/Shape>
#include <osg/Depth>
#include <osg/ShapeDrawable>

#include "../working_space_render/scene_view.h"

#include "../UI_op/ui_handler.h"
#include "../UI_op/curve_operand_helper.h"
#include "../working_space/working_space.h"
#include "../globals/user_guide.h"
#include "qt_osgwidget.h"
#include "qt_osgwidget2d.h"
#endif

#include <QTimer>
#include <QToolBar>
#include <QApplication>
#include <QDir>
#include <QKeyEvent>

#include <QLabel>
#include <QAction>
#include <QtWidgets/QWidget>
#include <QVBoxLayout>
#include <QMimeData>
#include <QStatusBar>
#include <QFile>
#include <QSignalMapper>
#include <QMenuBar>
#include <QTextStream>
#include "string.h"
#include "qt_wnd_server.h"

#include "../globals/GlobalData.h"

namespace framework
{
  MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags), qws_(nullptr)
  {
    setWindowTitle("framework");

    init_tab_page();

    createMenus();

    showMaximized();

    enter_state(STATE_NOMODEL);
  }

  void MainWindow::init_tab_page()
  {
    QWidget *w = new QWidget;
    QHBoxLayout *hlayout = new QHBoxLayout;
    {
      QWidget* left_osg = init_osg3d("master_3d");
      left_osg->setLayout(set_osg3d_layout("master_3d", left_osg));
      hlayout->addWidget(left_osg);
    }
    {
      QWidget * right_osg = init_osg2d("master_2d");
      right_osg->setLayout(set_osg2d_layout("master_2d", right_osg));
      hlayout->addWidget(right_osg);
    }
    w->setLayout(hlayout);
    setCentralWidget(w);
  }

  QLayout* MainWindow::set_osg3d_layout(const std::string & viewername, QWidget * parent)
  {
    QVBoxLayout * vlayout = new QVBoxLayout();
    QPushButton * bt_load = new QPushButton();
    bt_load->setText("Open");

    QPushButton * bt_save = new QPushButton();
    bt_save->setText("Save");

    connect(bt_load, &QPushButton::pressed, [=](){
        app::get_instance().get_glwnd_server_ptr()->show_load_model_dialog(viewername);
      });

    vlayout->addStretch(1);
    {
      QHBoxLayout *hlayout = new QHBoxLayout();
      hlayout->addWidget(bt_load);
      hlayout->addWidget(bt_save);
      vlayout->addLayout(hlayout);
    }
    vlayout->addStretch(40);
    return vlayout;
  }

  QLayout* MainWindow::set_osg2d_layout(const std::string & viewername, QWidget * parent)
  {
    QVBoxLayout * vlayout = new QVBoxLayout();
    QPushButton * bt_load = new QPushButton();
    bt_load->setText("Open");

    QPushButton * bt_save = new QPushButton();
    bt_save->setText("Save");

    connect(bt_load, &QPushButton::pressed, [=](){
        app::get_instance().get_glwnd_server_ptr()->show_load_model_dialog(viewername);
      });

    vlayout->addStretch(1);
    {
      QHBoxLayout *hlayout = new QHBoxLayout();
      hlayout->addWidget(bt_load);
      hlayout->addWidget(bt_save);
      vlayout->addLayout(hlayout);
    }
    vlayout->addStretch(40);
    return vlayout;
  }

  QWidget* MainWindow::init_osg3d(const std::string & osgwidget_name)
  {
    osg::ref_ptr<ui_handler> ui_hd = new ui_handler(osgwidget_name);
    ui_hd->init(app::get_instance());

    OSGWidget *osgwidget_(new OSGWidget(this, 0, 0, osgwidget_name, ui_hd));
    osgwidget_->showMaximized();

    if(qws_ == nullptr){
        qws_.reset(new qt_wnd_server());
        app::get_instance().set_glwnd_server(qws_);
        qws_->set_mainwidget(this);
      }

    qws_->push_osgwidget(osgwidget_name, osgwidget_);

    return osgwidget_;
  }

  QWidget* MainWindow::init_osg2d(const std::string & osgwidget_name)
  {
    osg::ref_ptr<ui_handler> ui_hd = new ui_handler(osgwidget_name);
    ui_hd->init(app::get_instance());

    OSG2DWidget *osgwidget_(new OSG2DWidget(this, 0, 0, osgwidget_name, ui_hd));
    osgwidget_->showMaximized();

    if(qws_ == nullptr){
        qws_.reset(new qt_wnd_server());
        app::get_instance().set_glwnd_server(qws_);
        qws_->set_mainwidget(this);
      }

    qws_->push_osgwidget(osgwidget_name, osgwidget_);

    return osgwidget_;
  }

  MainWindow::~MainWindow()
  {
  }

  void MainWindow::set_status_label(LABEL_NAME ln, const QString & words)
  {
    size_t idx = static_cast<int>(ln);
    if (idx < statusLabels_.size()) {
        statusLabels_[static_cast<int>(ln)]->setText(words);
      }
  }


  QStatusBar * MainWindow::createStatusBar(int width, int height)
  {
    QStatusBar* bar = this->statusBar(); //获取状态栏
    size_t num = 2;
    statusLabels_.resize(num);

    for (size_t i = 0; i < statusLabels_.size(); ++i) {
        statusLabels_[i] = new QLabel; //新建标签
        statusLabels_[i]->setMinimumSize(width / num, height); //设置标签最小尺寸
        statusLabels_[i]->setFrameShape(QFrame::WinPanel); //设置标签形状
        statusLabels_[i]->setFrameShadow(QFrame::Sunken); //设置标签阴影
      }
    bar->addWidget(statusLabels_[1]);
    return bar;
  }

  QHBoxLayout* MainWindow::createToolBar(QWidget * parent)
  {
    QHBoxLayout * hlayout = new QHBoxLayout(parent);
    //QToolBar *tool_bar = new QToolBar(parent);
    QPushButton * button = new QPushButton();
    button->setText("Load");
    hlayout->addWidget(button);
    connect(button, &QPushButton::pressed, [&](){
        app::get_instance().get_glwnd_server_ptr()->show_load_model_dialog("master_3d");
      });

    return hlayout;
  }

  void MainWindow::addButtonToToolBar(QToolBar *tool_bar, QSignalMapper *signal_mapper, const std::string &action_key,
                                      const std::string &icon_file, const std::string &tip_string)
  {
    QDir dir(icon_file.c_str());
    QAction *action = new QAction(QIcon(dir.absolutePath()), QString::fromUtf8(tip_string.c_str()), this);
    connect(action, SIGNAL(triggered()), signal_mapper, SLOT(map()));
    signal_mapper->setMapping(action, action_key.c_str());
    tool_bar->addAction(action);
  }

  void MainWindow::enter_state(State state)
  {
      on_leave_state(this->state);
      on_enter_state(state);

      this->state = state;
  }

  void MainWindow::on_enter_state(State state)
  {
      switch(state)
      {
      case STATE_NOMODEL:
          action_tool_select_->setEnabled(false);
          action_import_control_point_->setEnabled(false);
          action_export_control_point_->setEnabled(false);
          break;
      case STATE_HASMODEL:
          action_tool_select_->setEnabled(true);
          action_import_control_point_->setEnabled(true);
          action_export_control_point_->setEnabled(true);
          break;
      }
  }

  void MainWindow::on_leave_state(State state)
  {

  }

  void MainWindow::createMenus()
  {           
      menu_tool_ = menuBar()->addMenu("Tool");

      menu_tool_->addAction(action_tool_view_);
      action_tool_view_->setCheckable(true);
      action_tool_view_->setChecked(true);
      connect(action_tool_view_, &QAction::triggered, this, [this](){
          action_tool_view_->setChecked(true);
          qws_->subwidget_enter_state("run");
          current_tool_->setChecked(false);
          current_tool_ = action_tool_view_;
      });

      menu_tool_->addAction(action_tool_select_);
      action_tool_select_->setCheckable(true);
      connect(action_tool_select_, &QAction::triggered, this, [this](){
          action_tool_select_->setChecked(true);
          qws_->subwidget_enter_state("select_vertex");
          current_tool_->setChecked(false);
          current_tool_ = action_tool_select_;
      });

      menu_tool_->addAction(action_export_control_point_);
      connect(action_export_control_point_, &QAction::triggered, this, [this](){
          QString fileName = QFileDialog::getSaveFileName(0, "Export Control Point",
                                                          QString(), "Control Points(*.cps)");
          if(fileName.isNull() == false)
          {
              QFile file(fileName);
              file.open(QIODevice::WriteOnly | QIODevice::Text);

              QTextStream out(&file);

              auto globalData = GlobalData::getInstance();
              auto& control_points = globalData->control_points_;

              for(int i = 0; i < control_points.size(); i++)
              {
                  out << control_points[i] << '\n';
              }

              file.close();
          }

      });

      menu_tool_->addAction(action_import_control_point_);
      connect(action_import_control_point_, &QAction::triggered, this, [this](){
          QString fileName = QFileDialog::getOpenFileName(0, "Import Control Point",
                                                          QString(), "Control Points(*.cps)");
          if(fileName.isNull() == false)
          {
              QFile file(fileName);
              file.open(QIODevice::ReadOnly | QIODevice::Text);

              QTextStream in(&file);

              auto globalData = GlobalData::getInstance();
              auto& control_points = globalData->control_points_;

              control_points.clear();

              while(in.atEnd() == false)
              {
                  int read = in.readLine().toInt();
                  control_points.push_back(read);
              }

              file.close();

              curve_operand_helper::get_instance()->update_curve();
          }
      });
  }

  void MainWindow::keyPressEvent(QKeyEvent* event)
  {
    //osgwidget_->acceptKeyPress(event);
  }

  void MainWindow::keyReleaseEvent(QKeyEvent* event)
  {
    //osgwidget_->acceptKeyRelease(event);
  }
}
