#ifndef _HJ_PLATFORM_H_
#define _HJ_PLATFORM_H_

// Separate window system etc and ui interactive


#ifndef PLATFORMAPI
#define PLATFORMAPI
#endif

#include <string>

class PLATFORMAPI platform
{
public:
	virtual ~platform(){}

	static platform &get_platform();

//	virtual std::string file_dialog(const char *filter, bool is_open) const = 0;
	virtual int get_modifiers(void) const = 0;
};

// GLUT fashion, subset of GLUT API
class PLATFORMAPI glwnd_server
{
public:
	virtual ~glwnd_server(){}

	virtual void enter_glctx(void) = 0;
	virtual void leave_glctx(void) = 0;

	virtual void post_redisplay(void) = 0;
	// msecs == 0 means cancel
	virtual void set_timer(unsigned int msecs, int value) = 0;
	virtual void swap_buffer(void) = 0;

	virtual int get(int state) = 0;
	virtual void reshape_window(int width, int height) = 0;
};

class glwnd_client
{
public:
	glwnd_client(glwnd_server &server)
		:server_(server){}
	virtual ~glwnd_client(){}

	virtual void on_create(void){};
	virtual void on_destroy(void){};

	virtual void on_display(void){};

	virtual void on_reshape(int width, int height){};
	virtual void on_keyboard(unsigned char key, int x, int y){};
	virtual void on_mouse(int button, int state, int x, int y){};
	virtual void on_motion(int x, int y){};
	virtual void on_passive_motion(int x, int y){};
	virtual void on_timer(int value){};

	glwnd_server &server_;
};


#ifndef _MSC_VER
#include <unistd.h>
#else
#include <direct.h>
#define chdir	_chdir
#ifndef getcwd
	#define getcwd	_getcwd
#endif
#define mkdir	_mkdir
#define rmdir	_rmdir
#endif

#endif
