#include "qevent_adapter.h"
#include <boost/tuple/tuple.hpp>
#include <iostream>
#include <QMessageBox>
#include <string.h>
#include <qdatetime.h>
using namespace std;
#include "../globals/user_guide.h"
#include "mystring.h"
#include "qt_wnd_server.h"

namespace framework{
  void QEventAdapter::buttonPressed(const QString& button_name)
  {
    ui_hd_->handle_qbutton(button_name.toStdString());
  }

  void QEventAdapter::keyPress(const std::string &key)
  {
    ui_hd_->handle_cevent("key_press", key);
  }

  void QEventAdapter::keyRelease(const std::string &key)
  {
    ui_hd_->handle_cevent("key_release", key);
  }

  void QEventAdapter::send_cevent(const std::string & name, const boost::any & param)
  {
    ui_hd_->handle_cevent(name, param);
  }

  void QEventAdapter::save_model()
  {
    assert(load_model_dlg_ != nullptr);
    QStringList fileNames = load_model_dlg_->selectedFiles();
    std::string file_path = convert_qstring(fileNames.at(0));
    ui_hd_->handle_cevent("save_model", file_path);
  }


  void QEventAdapter::load_model()
  {
    assert(load_model_dlg_ != nullptr);
    QStringList fileNames = load_model_dlg_->selectedFiles();
    std::string file_path = convert_qstring(*(fileNames.begin()));
    ui_hd_->handle_cevent("load_model", file_path);
    qt_wnd_server::get_instance()->enter_state(MainWindow::STATE_HASMODEL);
  }


}
