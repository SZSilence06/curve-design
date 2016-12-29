#include "state_run.h"

#include <GL/glut.h>
#include <iostream>

#include "../common/util.h"	// cannot put before std, otherwise g++ fail
#include "../common/osg_util.h"
#include "../common/color.h"

#include "../working_space/working_space.h"
#include "../working_space/trimesh.h"
#include "../working_space/def_ctrl.h"
#include "../working_space_render/scene_view.h"
#include "../working_space_render/tri_mesh_render.h"
#include "../common/platform.h"
#include "../globals/globals.h"
#include "../working_space/data_tree.h"
#include "../app/app.h"
#include "common_procedure.h"

#undef min
#undef max

#include <osg/Switch>

#include <zjucad/matrix/matrix.h>

using namespace zjucad::matrix;

using namespace std;

state_run::state_run(const std::string & fsm_name):fsm_name_(fsm_name)
{
  const string strokes[] = {
    "\x1B",	// ESCAPE to cmd state
    "a",	// Add region
    "d",	// Del region
    // System
    "sr",	//	reset
    "sR", // random
    "sg",	// Go to iteration
    "ss",	// Stop iteration
    // Render
    "rf",	// Face
    "rw",	// Wire
    "rt",	// Translucent
    "rc",	// Color
    "rsc",	// Switch def_Ctrl
    "rb", // switch background
    // capture
    "ci",	// Image
    "cv",	// Video
  };
  const int num = sizeof(strokes)/sizeof(string);
  //strokes2cmd_.get_keys().insert(strokes, strokes+num);
  sig_run_ = 0;
  get_globals().get("system_run", &sig_run_);
  get_globals().get("app::call", &sig_app_call_);
}

void state_run::enter(state_key &next_state, boost::any &param)
{
  //strokes2cmd_.reset();
  next_state = "";
}

//fsm::event_return state_run::on_keyboard(unsigned char key, int x, int y)
//{
//  string next_state, strokes;

//  //	tri_mesh_node *tmn = dynamic_cast<tri_mesh_node*>(di_->get_scene_view().named_nodes_["tmn"]);
//  //	if(strokes2cmd_.input(key) == 1) {
//  //		strokes = *strokes2cmd_.begin();
//  //		if("\x1B" == strokes) {
//  //			return event_return("cmd", false);
//  //		}
//  //		else if("a" == strokes || "d" == strokes){
//  //			next_state = "region";
//  //		}
//  //		else if("sr" == strokes) {
//  //			if(sig_app_call_)
//  //				(*sig_app_call_)("reset", 0);
//  //		}
//  //		else if("sR" == strokes) {
//  //      matrix<double> &x = di_->get_working_space().x_;
//  //      x = rand<double>(x.size(1), x.size(2));
//  //			di_->get_glwnd_server().post_redisplay();
//  //		}
//  //		else if("sg" == strokes) {
//  //			if(sig_run_)
//  //				(*sig_run_)(true);
//  //		}
//  //		else if("ss" == strokes) {
//  //			if(sig_run_)
//  //				(*sig_run_)(false);
//  //		}
//  //		else if("rf" == strokes) {
//  //			tmn->face(!tmn->face());
//  //			di_->get_glwnd_server().post_redisplay();
//  //		}
//  //		else if("rw" == strokes) {
//  //			tmn->wire(!tmn->wire());
//  //			di_->get_glwnd_server().post_redisplay();
//  //		}
//  //		else if("rt" == strokes) {
//  //			tmn->translucent(!tmn->translucent());
//  //			di_->get_glwnd_server().post_redisplay();
//  //		}
//  //		else if("rc" == strokes) {
//  //			tmn->v_color(!tmn->v_color());
//  //			di_->get_glwnd_server().post_redisplay();
//  //		}
//  //		else if("rsc" == strokes) {
//  //			working_space_scene_view &sc = di_->get_scene_view();
//  //			osg::Switch *s = sc.switch_;
//  //			const osg::Node *child = sc.named_nodes_["dcr"];
//  //			assert(child);
//  //			s->setChildValue(child, !s->getChildValue(child));
//  //			di_->get_glwnd_server().post_redisplay();
//  //		}
//  //		else if("rb" == strokes) {
//  //			working_space_scene_view &sc = di_->get_scene_view();
//  //			osg::Switch *s = sc.switch_;
//  //			const osg::Node *child = sc.named_nodes_["bk"];
//  //      s->setChildValue(child, !s->getChildValue(child));
//  //			di_->get_glwnd_server().post_redisplay();
//  //    }
//  //		else {
//  //			cout << "no response for stroke: " << strokes << endl;
//  //		}
//  //	}

//  return event_return(next_state);
//}


//fsm::event_return state_run::on_mouse(int button, int state, int x, int y)
//{
//  //	if(state == GLUT_UP) return event_return("", false);
//  //	const int modifiers = platform::get_platform().get_modifiers();
//  //	if(modifiers & GLUT_ACTIVE_CTRL) {	// pick
//  //		int idx = pick_mesh_vertex(&di_->get_scene_view(), di_->get_working_space(), x, y);
//  //		def_ctrl &dc = *di_->get_working_space().def_ctrl_;
//  //		int cur_frame = 0;	//inst->glwnd_->cur_frame_
//  //		dc.pick_region(idx);
//  //		di_->get_glwnd_server().post_redisplay();
//  //		return event_return("", false);
//  //	}
//  //	else if(modifiers & GLUT_ACTIVE_SHIFT) {	// deform
//  //		const def_ctrl &dc = *di_->get_working_space().def_ctrl_;
//  //		if(dc.active_region_ >= 0) {
//  //			return event_return("move_ctrl", true);
//  //		}
//  //		return event_return("", false);
//  //	}
//  //	else
//  //		return event_return("trackball", true);

//  return event_return("", false);
//}

//fsm::event_return state_run::on_motion(int x, int y)
//{
//  return event_return("", false);
//}

state_key state_run::key(void) const
{
  return "run";
}

fsm::event_return state_run::on_gui_event(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
  auto view = aa.asView();
  auto working_scene_view = dynamic_cast<framework::render::working_space_scene_view*>(view);
  assert(view->getName() == fsm_name_);
  if(working_scene_view->get_view_type() == framework::render::view_type::V3D){
      if((ea.getButtonMask() & osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) &&
         (ea.getEventType() & osgGA::GUIEventAdapter::EventType::PUSH))
        {
          boost::shared_ptr<boost::thread> p(new boost::thread(boost::bind(&framework::load_model_to_scene, "../../dat/model.obj", view->getName())));
        }
    }
  return event_return("", false);
}

fsm::event_return state_run::on_button_click(const std::string &button_name)
{
  return event_return("", false);
}

fsm::event_return state_run::on_cevent(const std::string &event_name, const boost::any &param)
{
  if(event_name == "load_model"){
      boost::shared_ptr<boost::thread> p(new boost::thread(boost::bind(&framework::load_model_to_scene, boost::any_cast<std::string>(param), fsm_name_)));
    }

  return event_return("", false);
}


