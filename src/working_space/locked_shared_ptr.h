#ifndef WORKING_SPACE_LOCKED_SHARED_PTR_H
#define WORKING_SPACE_LOCKED_SHARED_PTR_H

#include <boost/thread.hpp>
#include <memory>

template <typename T>
class locked_shared_ptr
{
 public:
  locked_shared_ptr(T*t):ptr_(t){}

  locked_shared_ptr(const locked_shared_ptr<T> & ptr)
  {
    ptr_ = ptr();
  }

  const T* operator->()const
  {
    return ptr_.get(); //TODO(JTF): not thread safe
  }

  T* operator->()
  {
    return ptr_.get(); //TODO(JTF): not thread safe
  }

  template <typename T2>
  T2* cast()
  {
    return std::dynamic_pointer_cast<T2>(ptr_).get();
  }

  template <typename T2>
  T2* cast()const
  {
    return std::dynamic_pointer_cast<T2>(ptr_).get();
  }

  std::shared_ptr<T> operator()()const
  {
    return ptr_;
  }

  void lock()
  {
    lock_.lock();
  }

  void unlock()
  {
    lock_.unlock();
  }
  
 private:
  std::shared_ptr<T> ptr_;
//  boost::recursive_mutex lock_;
  boost::detail::spinlock lock_;
};

#endif // WORKING_SPACE_LOCKED_SHARED_PTR_H
