#ifndef WORKING_SPACE_MESSAGE_QUEUE_H
#define WORKING_SPACE_MESSAGE_QUEUE_H

#include "model.h"
#include "locked_shared_ptr.h"
#include <tuple>
#include <deque>
#include <boost/thread/recursive_mutex.hpp>

namespace framework
{
  namespace scene
  {
    // node name, node_state, node_ptr, viewer_type
    typedef std::tuple<std::string, framework::scene::node_state_type, const locked_shared_ptr<model_base>*> info;
    typedef std::deque<info> info_deq;


    class message_queue
    {
    public:
      message_queue & operator=(const message_queue&) = delete;
      message_queue(const message_queue&) = delete;
      message_queue(){}
      bool is_queue_empty();
      void wait_to_clear_queue();
      void push_back(const info &);
      const info pop_front();
private:
      info_deq q_;
      boost::recursive_mutex lock_;
    };
  }
}

#endif // WORKING_SPACE_MESSAGE_QUEUE_H
