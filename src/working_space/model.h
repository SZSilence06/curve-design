#ifndef WORKING_SPACE_MODEL_H
#define WORKING_SPACE_MODEL_H

#include <string>

namespace framework
{
  namespace scene
  {
    enum class node_state_type
    {
      NEW_ADDED,
      UPDATED,
      DELETED,
      ORDINARY	
    };

    enum class model_type
    {
      TRIMESH,
      PATCH2D,
      SPHERE,
      LINE
    };

    class model_base
    {
    public:
      virtual ~model_base(){}
      virtual int load(const std::string & file) { return __LINE__;}
      virtual int save(const std::string & file) { return __LINE__;}
      virtual void set_name(const std::string & name) = 0;
      virtual const std::string & get_name()const = 0;
      virtual node_state_type get_node_state()const  = 0;
      virtual void reset_state(const node_state_type ) = 0;
      virtual model_type get_model_type()const = 0;
      virtual void lock() = 0;
      virtual void unlock() = 0;
    };


  }
}
#endif //WORKING_SPACE_DATA_TREE_H
