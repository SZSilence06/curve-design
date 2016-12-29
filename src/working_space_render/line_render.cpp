#include "line_render.h"
#include "../working_space/line.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/Material>

namespace framework
{
    namespace render
    {
         line_render::line_render(const locked_shared_ptr<scene::model_base> *mb,
                                      const boost::property_tree::ptree &render_config)
             : mb_(mb), render_config_(render_config)
         {
             assert(mb_ != nullptr);
             if((*mb_)->get_model_type() != scene::model_type::LINE)
               throw std::logic_error("Invalid Type For Line Render.");

             auto line_model = mb_->cast<framework::scene::line>();
             double r,g,b;
             line_model->getColor(r,g,b);

             osg::ref_ptr<osg::Geode> geode(new osg::Geode());
             osg::ref_ptr<osg::Geometry> geometry(new osg::Geometry());
             osg::ref_ptr<osg::Vec3Array> array(new osg::Vec3Array());

             auto& points = line_model->getPoints();
             for(int i = 0; i < points.size(2) - 1; i++)
             {
                 array->push_back(osg::Vec3(points(0, i), points(1, i), points(2, i)));
                 array->push_back(osg::Vec3(points(0, i+1), points(1, i+1), points(2, i+1)));
             }
             geometry->setVertexArray(array.get());
             geometry->addPrimitiveSet(new osg::DrawArrays(GL_LINES, 0, points.size(2) - 1));

             osg::ref_ptr<osg::LineWidth> lineWidth(new osg::LineWidth());
             lineWidth->setWidth(line_model->getWidth());
             geode->getOrCreateStateSet()->setAttributeAndModes(lineWidth, osg::StateAttribute::LINEWIDTH);

             osg::ref_ptr<osg::Material> mat = new osg::Material();
             mat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(r, g, b, 1.0));
             geode->getOrCreateStateSet()->setAttributeAndModes(mat.get());

             geode->addDrawable(geometry);

             addChild(geode);
             setAllChildrenOn();
         }

         line_render::~line_render()
         {

         }

         void line_render::update(const locked_shared_ptr<scene::model_base> *lsp,
                                    const boost::property_tree::ptree &render_config)
         {

         }
    }
}
