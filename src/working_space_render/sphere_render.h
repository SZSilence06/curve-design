#pragma once

#include "mesh_render.h"

namespace framework
{
    namespace render
    {
        class sphere_render : public mesh_render
        {
        public:
            sphere_render(const locked_shared_ptr<framework::scene::model_base> * mb,
                          const boost::property_tree::ptree & render_config);
            virtual ~sphere_render();

            virtual void update(const locked_shared_ptr<framework::scene::model_base> * lsp,
                                const boost::property_tree::ptree & render_config) override;

        private:
            const boost::property_tree::ptree & render_config_;
            locked_shared_ptr<framework::scene::model_base> const* mb_;
        };
    }
}
