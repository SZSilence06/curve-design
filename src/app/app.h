#ifndef _HJ_APP_H_
#define _HJ_APP_H_

#include "../common/platform.h"

#include "conf.h"

#include <zjucad/matrix/matrix.h>
#include <memory>
#include <map>
#include <string>

#include <boost/signals2/signal.hpp>
#include <boost/any.hpp>
#include "../UI_op/event_interface.h"

class osgwnd;
class working_space;
class def_interf;

namespace framework
{
  class qt_wnd_server;
}

class APPAPI app: public data_interface
{
public:
  app();
  ~app();

  static app& get_instance();

  bool on_idle(void);	// return false to stop on_idle message

  bool run_;

  bool on_cmd_line(int argc, char *argv[]);

  virtual working_space &get_working_space(void) ;
  virtual glwnd_server &get_glwnd_server(void) ;
  virtual framework::render::working_space_scene_view &get_scene_view(void) ;

  working_space & get_working_space(const std::string&);
  std::shared_ptr <framework::qt_wnd_server> get_glwnd_server_ptr(void) ;
  framework::render::working_space_scene_view& get_scene_view(const std::string &);

  void push_scene_view(const std::string &, framework::render::working_space_scene_view *);
  void set_glwnd_server(std::shared_ptr<framework::qt_wnd_server> qws);

  void reset(void);

  int run(bool is_run);

  boost::any call(const char *id, boost::any *data = 0);

private:
  std::map<std::string, framework::render::working_space_scene_view *> scene_view_;
  std::map<std::string, std::shared_ptr<working_space> > ws_;
  //std::vector<framework::render::working_space_scene_view *> scene_view_;
  //std::vector<std::shared_ptr<working_space> > ws_;
  std::shared_ptr <framework::qt_wnd_server> wnd_server_;

protected:

  static app *instance_;

  boost::signals2::signal<int (bool)> sig_run_;
  boost::signals2::signal<boost::any(const char *, boost::any*)> sig_call_;
};


#endif
