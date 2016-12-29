#include "ui_handler.h"
#include "fsm.h"

ui_handler::ui_handler(const std::string &name)
{
	fsm_.reset(new fsm(name));
    state_key next_state = "run";
	boost::any param;
	fsm_->enter(next_state, param);
}

ui_handler::~ui_handler()
{
}

void ui_handler::init(data_interface &di)
{
	fsm_->init(di);
}

bool ui_handler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	fsm_->on_gui_event(ea, aa);
	return false;
}

void ui_handler::handle_qbutton(std::string button_name)
{
	fsm_->on_button_click(button_name);
	return;
}
void ui_handler::handle_cevent(const std::string &event_name, const boost::any &param)
{
	fsm_->on_cevent(event_name, param);
}

void ui_handler::enter_state(state_key &stateKey)
{
    boost::any param = std::string("");
    fsm_->enter(stateKey, param);
}

//event_interface::event_return ui_handler::on_reshape(int width, int height)
//{
//	return fsm_->on_reshape(width, height);
//}

//event_interface::event_return ui_handler::on_keyboard(unsigned char key, int x, int y)
//{
//	return fsm_->on_keyboard(key, x, y);
//}

//event_interface::event_return ui_handler::on_mouse(int button, int state, int x, int y)
//{
//	return fsm_->on_mouse(button, state, x, y);
//}

//event_interface::event_return ui_handler::on_motion(int x, int y)
//{
//	return fsm_->on_motion(x, y);
//}
