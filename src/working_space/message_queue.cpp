#include "message_queue.h"

using namespace framework::scene;

bool message_queue::is_queue_empty()
{
  lock_.lock();
  bool rtn = q_.empty();
  lock_.unlock();
  return rtn;
}

void message_queue::wait_to_clear_queue()
{
  int test_count = 0;
  while(is_queue_empty() == false){
      usleep(20);
      if(++test_count == 20)
        return;
    }
}

void message_queue::push_back(const info & inf)
{
  lock_.lock();
  q_.push_back(inf);
  lock_.unlock();
}

const info message_queue::pop_front()
{
  lock_.lock();
  auto inf = q_.front();
  q_.pop_front();
  lock_.unlock();
  return inf;
}
