#ifndef WORKING_SPACE_DATA_TREE_H
#define WORKING_SPACE_DATA_TREE_H

#include "model.h"
#include "locked_shared_ptr.h"
#include <boost/ptr_container/ptr_map.hpp>

namespace framework
{
  namespace scene
  {
    typedef locked_shared_ptr<model_base> smart_ptr;
    typedef boost::ptr_map<std::string, smart_ptr> data_tree_storage; // ptr_map store the pointer of smart_ptr

    class data_tree
    {
    public:
         static data_tree & get_instance();
         smart_ptr* get_or_create_model(const std::string &, const framework::scene::model_type &mt);
         void delete_model(const std::string &);

         data_tree_storage::const_iterator cbegin()const { return dtr_.cbegin();}
         data_tree_storage::const_iterator cend()const { return dtr_.cend();}
    private:
         boost::recursive_mutex lock_;
         data_tree_storage dtr_;
    };
  }
}
#endif //WORKING_SPACE_DATA_TREE_H
