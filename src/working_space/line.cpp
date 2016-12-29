#include "line.h"

namespace framework {
    namespace scene {
        line::line()
        {
            r = g = b = 1.0;
            state_ = node_state_type::ORDINARY;
        }

        line::line(const std::string &name) : name_(name)
        {
            r = g = b = 1.0;
            state_ = node_state_type::ORDINARY;
        }

        line::~line()
        {

        }

        void line::set_name(const std::string &name)
        {
            this->name_ = name;
        }

        const std::string & line::get_name() const
        {
            return name_;
        }

        node_state_type line::get_node_state() const
        {
            return state_;
        }

        void line::reset_state(const node_state_type state)
        {
            this->state_ = state;
        }

        model_type line::get_model_type() const
        {
            return model_type::LINE;
        }

        void line::lock()
        {
            lock_.lock();
        }

        void line::unlock()
        {
            lock_.unlock();
        }
    }
}
