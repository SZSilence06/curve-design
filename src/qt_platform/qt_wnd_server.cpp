#include "qt_wnd_server.h"

#include <fstream>

#include <QObject>
#include <QtWidgets>
//#include <QFileDialog>
#include <QErrorMessage>
#include <QString>
#include <QLabel>
#include <iostream>
#include <sstream>
#include "qt_osgwidget.h"
#include "../UI_op/ui_handler.h"
#include "qt_mainwindow.h"
#include "../working_space/data_tree.h"
#include "../working_space_render/scene_view.h"
#include "../alg/CurveGenerator.h"

namespace framework{
  qt_wnd_server* qt_wnd_server::instance_ = nullptr;

  qt_wnd_server::qt_wnd_server()
  {
    assert(instance_ == nullptr);
    pressed_key_.clear();
    instance_ = this;
  }

  qt_wnd_server::~qt_wnd_server()
  {
  }

  void qt_wnd_server::enter_glctx(void) {}
  void qt_wnd_server::leave_glctx(void) {}

  // @todo
  void qt_wnd_server::post_redisplay(void) {}

  // msecs == 0 means cancel
  void qt_wnd_server::set_timer(unsigned int msecs, int value) {}

  void qt_wnd_server::swap_buffer(void)
  {
  }

  void qt_wnd_server::reshape_window(int width, int height)
  {
  }

  void qt_wnd_server::set_statusbar_key(int i, std::string str, int color)
  {
    if (!statusLabels_.empty() &&  statusLabels_[i]) {
        // std::stringstream ss;
        // if(color == 0)
        //   ss << "<h2><font color=#00ff00>" << str.c_str() << "</font></h2>";
        // else
        //   ss << "<h2><font color=red>" << str.c_str() << "</font></h2>";
        // statusLabels_[i]->setText(QString::fromStdString(ss.str()));
        str = "                " + str;
        statusLabels_[i]->setText(QString::fromUtf8(str.c_str()));
        // statusLabels_[i]->setText(QString::fromStdString("                "+str));
      }
  }

  void qt_wnd_server::key_press(const std::string &key)
  {
    pressed_key_.insert(key);
  }
  void qt_wnd_server::key_release(const std::string &key)
  {
    pressed_key_.erase(key);
  }

  bool qt_wnd_server::is_pressed(const std::string &key)
  {
    std::set<std::string>::iterator it = pressed_key_.find(key);
    return it != pressed_key_.end();
  }

  void qt_wnd_server::push_osgwidget(const std::string name,framework::OSGWidget *widget_)
  {
    osgswidget_.insert(std::map<std::string, framework::OSGWidget*>::value_type(name,widget_));
  }

  void qt_wnd_server::change_widget(const std::string &key, bool bchange)
  {
    std::map<std::string, framework::OSGWidget*>::iterator  it_;
    for (it_ = osgswidget_.begin(); it_ != osgswidget_.end(); ++it_)
      {
        if (it_->first == key){
            if (bchange){
                //it_->second->hide();
                it_->second->setVisible(false);
              }
            else{
                it_->second->setVisible(true);
                printf("qt_wnd_server::change_widget  hide widget:==%d\n", bchange);
              }
          }
      }
  }

  void qt_wnd_server::send_osg_event(const std::string & event_name, const boost::any& param,
                                     const std::string & osg_widget_name)
  {
    auto it = get(osg_widget_name);
    if (it != nullptr)
      {
        it->qevent_adapter_.send_cevent(event_name, param);
      }
  }

  //void qt_wnd_server::hide_load_model_dialog()
  //{
  //	static QFileDialog *fdlg = 0;
  //	if (fdlg == 0){
  //		QStringList filters;
  //		filters << "Obj Files (*.obj)" << "STL Files (*.stl)" << "ASC Files (*.asc)";
  //		fdlg = new QFileDialog(main_widget_, "Load model");
  //		fdlg->setNameFilters(filters);
  //	}
  //	fdlg->open(&(widget_->qevent_adapter_), SLOT(load_model()));
  //	//widget_->qevent_adapter_.set_load_model_dlg(fdlg);

  //	fdlg->setVisible(true);
  //}

  //	void qt_wnd_server::hide_save_model_dialog()
  //	{
  //		static QFileDialog *fdlg = 0;
  //		if (fdlg == 0){
  //			QStringList filters;
  //			filters << "Obj Files (*.obj)" << "STL Files (*.stl)" << "ASC Files (*.asc)";
  //			fdlg = new QFileDialog(main_widget_, "Save model");
  //			fdlg->setNameFilters(filters);
  //		}
  //
  //		fdlg->open(&(widget_->qevent_adapter_), SLOT(save_model()));
  //		fdlg->setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
  ////		widget_->qevent_adapter_.set_save_model_dlg(fdlg);
  //		fdlg->setVisible(true);
  //	}

  void qt_wnd_server::show_load_model_dialog(const std::string & osgwidget_name)
  {
    static QFileDialog *fdlg = 0;
    if (fdlg == 0){
        QStringList filters;
        filters << "Obj Files (*.obj)" << "STL Files (*.stl)" << "DXF Files (*.dxf)";
        fdlg = new QFileDialog(0, "Load model");
        fdlg->setNameFilters(filters);
      }
    auto widget = get(osgwidget_name);
    fdlg->open(&(widget->qevent_adapter_), SLOT(load_model()));
    widget->qevent_adapter_.set_load_model_dlg(fdlg);

    fdlg->setVisible(true);
  }

  void qt_wnd_server::subwidget_enter_state(state_key stateKey)
  {
      if(stateKey == "select_vertex" ||
              stateKey == "run")
      {
          get("master_3d")->qevent_adapter_.get_ui_handler()->enter_state(stateKey);
      }
  }

  void qt_wnd_server::enter_state(MainWindow::State state)
  {
      main_widget_->enter_state(state);
  }
}
