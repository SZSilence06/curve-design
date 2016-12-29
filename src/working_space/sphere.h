#pragma once

#include "model.h"
#include <boost/thread/recursive_mutex.hpp>

namespace framework
{
    namespace scene
    {
        class sphere : public model_base
        {
        public:
            sphere();
            sphere(const std::string& name);
            virtual ~sphere();

            virtual void set_name(const std::string & name) override;
            virtual const std::string & get_name()const override;
            virtual node_state_type get_node_state()const  override;
            virtual void reset_state(const node_state_type ) override;
            virtual model_type get_model_type()const override;
            virtual void lock() override;
            virtual void unlock() override;

            void setCenter(double x, double y, double z)
            {
                this->x = x;
                this->y = y;
                this->z = z;
            }

            void setRadius(double radius) { this->radius = radius; }

            void setColor(double r, double g, double b)
            {
                this->r = r;
                this->g = g;
                this->b = b;
            }

            void getCenter(double& x, double& y, double& z)
            {
                x = this->x;
                y = this->y;
                z = this->z;
            }

            double getRadius() { return radius; }

            void getColor(double& r, double& g, double& b)
            {
                r = this->r;
                g = this->g;
                b = this->b;
            }

        private:
            std::string name_;
            double x,y,z;
            double radius;
            double r,g,b;

            node_state_type state_;
            boost::recursive_mutex lock_;
        };
    }
}
