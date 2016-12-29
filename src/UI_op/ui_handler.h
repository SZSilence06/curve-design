#ifndef HJ_UI_HNANLDER_H_
#define HJ_UI_HNANLDER_H_

#include "conf.h"

#include <list>
#include <boost/shared_ptr.hpp>
#include <osg/Referenced>
#include <osgGA/GUIEventHandler>
#include "event_interface.h"

class fsm;

class UIOPAPI ui_handler : public osgGA::GUIEventHandler
{
public:
  ui_handler(const std::string &name);
  virtual ~ui_handler();

  virtual void init(data_interface &di);

  bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
  void handle_qbutton(std::string button_name = "");

  void handle_cevent(const std::string &event_name, const boost::any &param);

  //	virtual void handle_qbutton(const std::string & button_name);
  //	virtual void handle_cevent(const std::string & command, const std::string &args);

  //virtual event_return on_reshape(int width, int height);
  //virtual event_return on_keyboard(unsigned char key, int x, int y);
  //virtual event_return on_mouse(int button, int state, int x, int y);
  //virtual event_return on_motion(int x, int y);

  void enter_state(state_key& stateKey);

protected:
  std::unique_ptr<fsm> fsm_;
};

#endif
