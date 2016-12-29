#include "app.h"

#include "../common/util.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "../working_space/working_space.h"
#include "../working_space_render/tri_mesh_render.h"
#include "../working_space_render/scene_view.h"
#include "../globals/globals.h"
#include "../qt_platform/qt_wnd_server.h"
#include <boost/bind.hpp>

using namespace zjucad::matrix;

app::app()
  :run_(false){
  sig_run_.connect(boost::bind(&app::run, this, _1));
  get_globals().put("system_run", &sig_run_);

  get_globals().put("system_is_run", &run_);

  sig_call_.connect(boost::bind(&app::call, this, _1, _2));
  get_globals().put("app::call", &sig_call_);
}

app::~app(){}

app& app::get_instance()
{
  static app app_;
  return app_;
}

working_space & app::get_working_space(void)  {
  return get_working_space(0);
}

glwnd_server & app::get_glwnd_server(void)  {
  return *wnd_server_;
}

std::shared_ptr <framework::qt_wnd_server> app::get_glwnd_server_ptr(void)
{
  return wnd_server_;
}

working_space & app::get_working_space(const std::string & name)
{
  auto it = ws_.find(name);
  if(it == ws_.end())
    throw std::logic_error("can not find working_space");
  return (*it->second);
}

framework::render::working_space_scene_view& app::get_scene_view(const std::string & name)
{
  auto it = scene_view_.find(name);
  if(it == scene_view_.end())
    throw std::logic_error("can not find scene_view");
  return (*it->second);
}

framework::render::working_space_scene_view & app::get_scene_view(void) {
  throw std::logic_error("should not be here");
}

void app::push_scene_view(const std::string & name, framework::render::working_space_scene_view *sv)
{
  scene_view_[name] = sv;
}

void app::set_glwnd_server(std::shared_ptr<framework::qt_wnd_server> qws)
{
  wnd_server_ = qws;
}

bool app::on_idle(void)
{
  throw std::logic_error("not used.");
  return true;
  //  if(ws_.get() && run_) {
  //      bool is_cont = deform();
  //      if(!is_cont) {
  //          run_ = false;
  //        }
  //      return !is_cont;
  //    }
  //  return false;
}


void app::reset(void)
{
  //ws_->reset();
  throw std::logic_error("not finished");
}

#include <boost/program_options.hpp>
using namespace boost::program_options;

bool app::on_cmd_line(int argc, char *argv[])
{
  options_description desc("Allowed options");
  desc.add_options()
      ("help,h", "produce help message")
      ("project,p", value<string>(), "open project file")
      ("Profile,P", value<string>(), "specify the profile path")
      ;

  variables_map vm;
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);

  if (vm.count("help")) {
      cout << desc << "\n";
      return true;
    }


  return true;
}


static void load_color_table(const char *path, matrix<double> &ct)
{
  ifstream ifs(path);
  if(ifs.fail()) {
      ct = rand<double>(3, 50);
      cout << "load color_table.txt fail." << endl;
      return;
    }
  vector<double> vct;
  double c;
  while(!ifs.eof()) {
      ifs >> c;
      vct.push_back(c);
    }
  ct.resize(3, vct.size()/3);
  copy(vct.begin(), vct.begin()+ct.size(), ct.begin());
  if(sum(ct)/ct.size() > 1)
    ct /= 255;
}


int app::run(bool is_run)
{
  run_ = is_run;
  return 0;
}

boost::any app::call(const char *id, boost::any *data)
{
  boost::any rtn;
  if(!strcmp(id, "reset")) {
      reset();
    }
  return rtn;
}
