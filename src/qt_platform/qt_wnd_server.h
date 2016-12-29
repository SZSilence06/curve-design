#ifndef QT_WND_SERVER_H
#define QT_WND_SERVER_H

#include <set>
#include <vector>
#include <osg/ref_ptr>
#include "platform.h"
#include "conf.h"
#include <map>
#include <boost/any.hpp>
#include "qt_mainwindow.h"

namespace framework
{
  class OSGWidget;
}

class DragWidget;
class QWidget;
class QPoint;
class QLabel;

namespace framework{
  class  qt_wnd_server : public glwnd_server
  {
  public:
    qt_wnd_server();
    virtual ~qt_wnd_server();

    virtual void enter_glctx(void);
    virtual void leave_glctx(void);

    virtual void post_redisplay(void);
    // msecs == 0 means cancel
    virtual void set_timer(unsigned int msecs, int value);
    virtual void swap_buffer(void);

    virtual int get(int state){ return __LINE__; }
    virtual void reshape_window(int width, int height);

    virtual void set_statusbar_key(int i, std::string str, int color = 0);

    virtual void key_press(const std::string &key);
    virtual void key_release(const std::string &key);
    virtual bool is_pressed(const std::string &key);
    void set_mainwidget(MainWindow *mainwidget) {
      main_widget_ = mainwidget;
    }

    void set_status_label(const std::vector<QLabel*> &q) {
      statusLabels_ = q;
    }
    framework::OSGWidget* get(const std::string &name)
    {
      auto it = osgswidget_.find(name);
      if (it != osgswidget_.end())
        return it->second;
      return nullptr;
    }

    void send_osg_event(const std::string & event_name, const boost::any& param,
                        const std::string & osg_widget_name);

    void change_widget(const std::string &key, bool bchange);
    void push_osgwidget(const std::string name, framework::OSGWidget *widget_);
    void show_load_model_dialog(const std::string & osgwidget_name);

    void subwidget_enter_state(std::string state_key);
    void enter_state(MainWindow::State state);

    static qt_wnd_server* get_instance() { return instance_; }

  private:
    MainWindow *main_widget_;
    std::vector<QLabel*> statusLabels_; // status_label
    std::set<std::string> pressed_key_;
    std::map<std::string,framework::OSGWidget*> osgswidget_;

    static qt_wnd_server* instance_;
  };
}
#endif /* QT_WND_SERVER_H */
