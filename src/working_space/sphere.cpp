#include "sphere.h"

namespace framework {
    namespace scene {
        sphere::sphere()
        {
            r = g = b = 1.0;
            state_ = node_state_type::ORDINARY;
        }

        sphere::sphere(const std::string &name) : name_(name)
        {
            r = g = b = 1.0;
            state_ = node_state_type::ORDINARY;
        }

        sphere::~sphere()
        {

        }

        void sphere::set_name(const std::string &name)
        {
            this->name_ = name;
        }

        const std::string & sphere::get_name() const
        {
            return name_;
        }

        node_state_type sphere::get_node_state() const
        {
            return state_;
        }

        void sphere::reset_state(const node_state_type state)
        {
            this->state_ = state;
        }

        model_type sphere::get_model_type() const
        {
            return model_type::SPHERE;
        }

        void sphere::lock()
        {
            lock_.lock();
        }

        void sphere::unlock()
        {
            lock_.unlock();
        }
    }
}
