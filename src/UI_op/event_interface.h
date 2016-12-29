#ifndef HJ_EVENT_INTERFACE_H_
#define HJ_EVENT_INTERFACE_H_

#include <utility>
#include <string>
#include <boost/any.hpp>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>

typedef std::string state_key;

class working_space;
class glwnd_server;

namespace framework
{
  namespace render
  {
    class working_space_scene_view;
  }
}
class data_interface
{
public:
  virtual ~data_interface(){}
  virtual working_space &get_working_space(void) = 0;
  virtual glwnd_server &get_glwnd_server(void) = 0;
  virtual framework::render::working_space_scene_view &get_scene_view(void) = 0;
};

class event_interface
{
public:
  virtual ~event_interface(){}

  virtual void init(data_interface &di){}

  class event_return
  {
  public:
    event_return(const std::string &key = "", bool need_to_relay = true, const boost::any &p = boost::any())
      :key_(key), need_to_relay_(need_to_relay), param_(p)
    {}
    state_key key_;
    boost::any param_;	// for enter
    bool need_to_relay_;
  };

  virtual event_return on_gui_event(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
    return event_return();
  }
  virtual event_return on_button_click(const std::string &button_name) {
    return event_return();
  }
  virtual event_return on_cevent(const std::string &event_name, const boost::any &param) {
    return event_return();
  }
};

#endif
