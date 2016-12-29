#pragma once

#include "model.h"
#include <zjucad/matrix/matrix.h>
#include <boost/thread/recursive_mutex.hpp>

using namespace zjucad::matrix;

namespace framework
{
    namespace scene
    {
        class line : public model_base
        {
        public:
            line();
            line(const std::string& name);
            virtual ~line();

            virtual void set_name(const std::string & name) override;
            virtual const std::string & get_name()const override;
            virtual node_state_type get_node_state()const  override;
            virtual void reset_state(const node_state_type ) override;
            virtual model_type get_model_type()const override;
            virtual void lock() override;
            virtual void unlock() override;

            void setPoints(const matrix<double>& line_points)
            {
                this->points = line_points;
            }

            void setWidth(double width) { this->width = width; }

            void setColor(double r, double g, double b)
            {
                this->r = r;
                this->g = g;
                this->b = b;
            }

            const matrix<double>& getPoints() const
            {
                return points;
            }

            double getWidth() const { return width; }

            void getColor(double& r, double& g, double& b) const
            {
                r = this->r;
                g = this->g;
                b = this->b;
            }

        private:
            std::string name_;
            matrix<double> points;
            double width;
            double r,g,b;

            node_state_type state_;
            boost::recursive_mutex lock_;
        };
    }
}
