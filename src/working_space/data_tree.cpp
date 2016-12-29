#include "data_tree.h"
#include "trimesh.h"
#include "sphere.h"
#include "line.h"
#include <boost/assign/ptr_map_inserter.hpp>

using namespace framework::scene;

data_tree & data_tree::get_instance()
{
  static data_tree dt;
  return dt;
}

smart_ptr * data_tree::get_or_create_model(const std::string & name, const framework::scene::model_type & mt)
{
    auto it = dtr_.find(name);
    if(it != dtr_.end()){
        if(mt != (*it->second)->get_model_type())
            throw std::invalid_argument("Wrong model type.");
        return it->second;
    }else{
        lock_.lock();// JTF
        if(mt == framework::scene::model_type::TRIMESH)
          boost::assign::ptr_map_insert<smart_ptr>(dtr_)(name, new trimesh(name));
            //get_instance().insert(name, new smart_ptr(new trimesh()));
       // if(mt == framework::scene::model_type::PATCH2D)
       //     get_instance()[name] = new smart_ptr(new patch2d());
        else if(mt == framework::scene::model_type::SPHERE)
        {
            boost::assign::ptr_map_insert<smart_ptr>(dtr_)(name, new sphere(name));
        }
        else if(mt == framework::scene::model_type::LINE)
        {
            boost::assign::ptr_map_insert<smart_ptr>(dtr_)(name, new line(name));
        }
        lock_.unlock();
        return dtr_.find(name)->second;
    }
}

void data_tree::delete_model(const std::string & name)
{
    auto it = dtr_.find(name);
    lock_.lock();
    if(it != dtr_.end()){
        dtr_.erase(it);
    }
    lock_.unlock();
}

