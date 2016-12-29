#include "sphere_render.h"
#include "../working_space/sphere.h"
#include <osg/Shape>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>

namespace framework
{
    namespace render
    {
         sphere_render::sphere_render(const locked_shared_ptr<scene::model_base> *mb,
                                      const boost::property_tree::ptree &render_config)
             : mb_(mb), render_config_(render_config)
         {
             assert(mb_ != nullptr);
             if((*mb_)->get_model_type() != scene::model_type::SPHERE)
               throw std::logic_error("Invalid Type For Sphere Render.");

             auto sp = mb_->cast<framework::scene::sphere>();
             double x,y,z,r,g,b;
             sp->getCenter(x,y,z);
             sp->getColor(r,g,b);

             osg::ref_ptr<osg::Geode> geode(new osg::Geode());
             osg::ref_ptr<osg::Sphere> osg_sphere(new osg::Sphere(osg::Vec3(x,y,z), sp->getRadius()));
             osg::ref_ptr<osg::Drawable> drawable(new osg::ShapeDrawable(osg_sphere));

             osg::ref_ptr<osg::Material> mat = new osg::Material();
             mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(r, g, b, 1.0));
             geode->getOrCreateStateSet()->setAttributeAndModes(mat.get());

             geode->addDrawable(drawable);

             addChild(geode);
             setAllChildrenOn();
         }

         sphere_render::~sphere_render()
         {

         }

         void sphere_render::update(const locked_shared_ptr<scene::model_base> *lsp,
                                    const boost::property_tree::ptree &render_config)
         {

         }
    }
}
