#ifndef HJ_FINITE_STATE_MACHINE_H_
#define HJ_FINITE_STATE_MACHINE_H_

#include <map>
#include <boost/shared_ptr.hpp>

namespace hj { namespace fsm {

// only ensure inheritable
class event_interface
{
public:
	virtual ~event_interface(){}
};

template <typename EI, typename KEY, typename PARAM>
class state : public EI
{
public:
	virtual ~state(){}
	virtual void enter(KEY &next_key, PARAM &p) {next_key = "";}
	virtual void leave(){}
};

// hierachical fsm
template <typename EI, typename KEY, typename PARAM>
class finite_state_machine : public state<EI, KEY, PARAM>
{
public:
  typedef state<EI, KEY, PARAM> state_t;
	typedef typename std::map<KEY, boost::shared_ptr<state_t> > states_container;

	finite_state_machine():active_state_(0){}
	virtual ~finite_state_machine(){}

	virtual void leave() {
		if(active_state_) active_state_->leave();
	}

	state_t *active_state(void) const {return active_state_;}

	state_t *get_state(const KEY &k) const {
		typename states_container::const_iterator i;
		i = states_.find(k);
		assert(i != states_.end());
		return i->second.get();
	}

protected:
	virtual bool transition(KEY &k, PARAM &p) {
		if(EI::no_transition(k)) return false;	// not only for efficiency
		typename states_container::const_iterator i;
		i = states_.find(k);
		assert(i != states_.end());
		if(active_state_) active_state_->leave();
		active_state_ = i->second.get();
		active_state_->enter(k, p);
		return true;
	}
	states_container states_;
private:
	state_t *active_state_;
};

}}

#endif
