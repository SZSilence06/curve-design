#ifndef QEVENT_ADAPTER_H
#define QEVENT_ADAPTER_H

#include <QObject>
#include <QFileDialog>
#include <osg/ref_ptr>
#include "../UI_op/ui_handler.h"

namespace framework{
  class QEventAdapter : public QObject
  {
    Q_OBJECT
  public:
    void set_ui_hd(osg::ref_ptr<ui_handler> ui_hd) {
      ui_hd_ = ui_hd;
    }

    void set_load_model_dlg(QFileDialog *dlg) {
            load_model_dlg_ = dlg;
    }
    void set_save_model_dlg(QFileDialog * dlg) {
            load_model_dlg_ = dlg;
    }

  public slots :
    void load_model();
    void save_model();
    void buttonPressed(const QString& button_name);
    void keyPress(const std::string &key);
    void keyRelease(const std::string &key);

    void send_cevent(const std::string & name, const boost::any & param);

    osg::ref_ptr<ui_handler> get_ui_handler() { return ui_hd_; }
  private:
    osg::ref_ptr<ui_handler> ui_hd_;
    QString start_time;
    QFileDialog *load_model_dlg_;
  };
}

#endif /* QEVENT_ADAPTER_H */
