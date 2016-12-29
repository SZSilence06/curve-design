#ifndef HJ_STATE_RUN_H_
#define HJ_STATE_RUN_H_

#include <boost/signals2/signal.hpp>

#include <set>
#include <string>

#include "fsm.h"

class state_run : public hj::fsm::state<fsm_glwnd_interface, state_key, boost::any>
{
public:
	state_run(const std::string & fsm_name);

	virtual void enter(state_key &next_state, boost::any &param);

//	virtual event_return on_keyboard(unsigned char key, int x, int y);
//	virtual event_return on_mouse(int button, int state, int x, int y);
//	virtual event_return on_motion(int x, int y);
	virtual state_key key(void) const;

    virtual event_return on_gui_event(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    virtual event_return on_button_click(const std::string &button_name);
	virtual event_return on_cevent(const std::string &event_name, const boost::any &param);
private:
	boost::signals2::signal<int (bool)> *sig_run_;
	boost::signals2::signal<boost::any(const char *, boost::any*)> *sig_app_call_;
	const std::string fsm_name_;
};

#endif
