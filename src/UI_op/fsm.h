#ifndef HJ_FSM_H_
#define HJ_FSM_H_

#include <utility>
#include <string>

#include "finite_state_machine.h"
#include <osgGA/GUIEventHandler>
#include "event_interface.h"

class fsm_glwnd_interface : public event_interface
{
public:
  virtual void init(data_interface &di) {
    di_ = &di;
  }
  static bool no_transition(const state_key &k) {
    return k.empty();
  }
  virtual state_key key(void) const = 0;
protected:
  data_interface *di_;
};


class fsm : public hj::fsm::finite_state_machine<fsm_glwnd_interface, state_key, boost::any>
{
public:
  fsm(const std::string & name);
  virtual void init(data_interface &di);
  virtual void enter(state_key &next_state, boost::any &param);

  virtual event_return on_gui_event(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
  virtual event_return on_button_click(const std::string &button_name);
  virtual event_return on_cevent(const std::string &event_name, const boost::any &param);

  virtual state_key key(void) const;  

protected:
  virtual bool transition(event_return &er);
  void add_state(hj::fsm::state<fsm_glwnd_interface, state_key, boost::any> *s);
private:
  const std::string name_;
};


#endif
