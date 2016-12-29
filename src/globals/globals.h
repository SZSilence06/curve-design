#ifndef HJ_GLOBALS_H_
#define HJ_GLOBALS_H_

#include <hjlib/data_tree/data_tree.h>

#ifdef _MSC_VER
#  ifdef globals_EXPORTS
	#define GLOBALS_API __declspec(dllexport)
#  else
	#define GLOBALS_API
#  endif
#endif

#ifndef GLOBALS_API
#  define GLOBALS_API
#endif

// only store the pointer
// can be used to collect information in the application for global access
// typical usage:
// vps.put("hello", &world)
// ...
// if(vps.get("hello", &ptr_word) && ptr_word)
class GLOBALS_API var_pt_store
{
public:
  template <typename T>
  class raw_ptr {
  public:
    raw_ptr(T *ptr)
      :ptr_(ptr){}
    T *operator*(void) const { return ptr_; }
  private:
    T *ptr_;
  };

	template <typename T>
	void put(const std::string &name, T *var) {
		dt_.put(name.c_str(), raw_ptr<T>(var));
	}

	template <typename T>
	T* get(const std::string &name, T **var) {
    boost::shared_ptr<raw_ptr<T> > ptr;
    try {
      ptr = dt_.get<raw_ptr<T> >(name.c_str());
    }
    catch (...) {
      return 0;
    }
    return *var = *(*ptr);
	}
protected:
  hj::data_tree::data_tree dt_;
};

GLOBALS_API var_pt_store& get_globals(void);
#endif
