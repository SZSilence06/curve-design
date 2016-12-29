#include "fsm.h"
using namespace std;

//#include "state_cmd.h"
//#include "state_trackball.h"
//#include "state_region.h"
#include "state_run.h"
#include "state_select_vertex.h"
//#include "state_move_ctrl.h"

#include <iostream>
using namespace std;

fsm::fsm(const std::string & name)
{
  //	add_state(new state_cmd);
  //	add_state(new state_trackball);
  //	add_state(new state_region);
  add_state(new state_run(name));
  add_state(new state_select_vertex(name));
  //	add_state(new state_move_ctrl);
}

void fsm::init(data_interface &di)
{
  states_container::iterator i;
  for(i = states_.begin(); i != states_.end(); ++i)
    i->second->init(di);
}

void fsm::enter(state_key &next_state, boost::any &param)
{
  event_return er(next_state, false, param);
  transition(er);
}

event_interface::event_return fsm::on_gui_event(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
  event_return er = active_state()->on_gui_event(ea, aa);
  while (transition(er)) {
      if (er.need_to_relay_) {
          er = active_state()->on_gui_event(ea, aa);
        }
      else {
          er.key_.clear();
        }
    }

  return event_interface::event_return();
}

event_interface::event_return fsm::on_button_click(const std::string &button_name)
{
  event_interface::event_return er = active_state()->on_button_click(button_name);
  while (transition(er)) {
      if (er.need_to_relay_) {
          er = active_state()->on_button_click(button_name);
        }
      else {
          er.key_.clear();
        }
    }
  return event_return();
}

event_interface::event_return fsm::on_cevent(const std::string &event_name, const boost::any &param)
{
  event_interface::event_return er = active_state()->on_cevent(event_name, param);
  while (transition(er)) {
      if (er.need_to_relay_) {
          er = active_state()->on_cevent(event_name, param);
        }
      else {
          er.key_.clear();
        }
    }
  return event_interface::event_return();
}

state_key fsm::key(void) const
{
  return "fsm";
}

bool fsm::transition(event_return &er)
{
  state_key k0, k1 = er.key_;
  if(active_state())
    k0 = active_state()->key();
  bool rtn = hj::fsm::finite_state_machine<fsm_glwnd_interface, state_key, boost::any>::transition(er.key_, er.param_);
  if(rtn)
    cout << "leave: " << k0 << "\tenter: " << k1 << "\t transition to: " << er.key_ << endl;
  return rtn;
}

void fsm::add_state(hj::fsm::state<fsm_glwnd_interface, state_key, boost::any> *s)
{
  typedef typename hj::fsm::finite_state_machine<fsm_glwnd_interface, state_key, boost::any> FSM;
  states_.insert(make_pair(s->key(), boost::shared_ptr<FSM::state_t>(s)));
}
