#ifndef _HJ_PLATFORM_H_
#define _HJ_PLATFORM_H_

#ifndef PLATFORMAPI
#define PLATFORMAPI
#endif

#include <string>
#include <boost/any.hpp>

namespace framework{
	// GLUT fashion, subset of GLUT API
	class PLATFORMAPI glwnd_server
	{
	public:
		virtual ~glwnd_server() {}

		virtual void enter_glctx(void) = 0;
		virtual void leave_glctx(void) = 0;

		virtual void post_redisplay(void) = 0;
		// msecs == 0 means cancel
		virtual void set_timer(unsigned int msecs, int value) = 0;
		virtual void swap_buffer(void) = 0;
		virtual void send_osg_event(const std::string & event_name, const boost::any& param, const std::string & osg_widget_name) = 0;
		virtual int get(int state) = 0;
		virtual void reshape_window(int width, int height) = 0;

		virtual void show_load_model_dialog() {}
		virtual void show_save_model_dialog() {}

		virtual void key_press(const std::string &key) {}
		virtual void key_release(const std::string &key) {}
		virtual bool is_pressed(const std::string &key) {
			return false;
		}

		virtual void change_widget(const std::string &key, bool bchange){}
		virtual void set_statusbar_key(int i, std::string str, int color = 0) {}
	};
}
#endif
