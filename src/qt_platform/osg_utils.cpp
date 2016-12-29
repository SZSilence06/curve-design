#include "osg_utils.h"
#include <osg/Texture>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osg/MatrixTransform>

osg::Camera* add_image_camera(std::string filename, double x, double y,
                              double width, double height)
{
  osg::ref_ptr<osg::Camera>camera = new osg::Camera;
  camera->setViewMatrix(osg::Matrix::identity());
  camera->setRenderOrder(osg::Camera::PRE_RENDER);
  camera->setClearMask(GL_DEPTH_BUFFER_BIT);
  camera->setAllowEventFocus(false);
  camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);

  camera->setViewport(x, y, width, height);
  camera->setProjectionMatrixAsOrtho2D(x, width, y, height);

  osg::ref_ptr<osg::Geode> geode = new osg::Geode;
  geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
  geode->getOrCreateStateSet()->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::ON);
  osg::Geometry* gm = osg::createTexturedQuadGeometry(osg::Vec3(x, y, 0), osg::Vec3(x + width, 0, 0), osg::Vec3(0, y + height, 0), 0, 0, 1, 1);
  geode->addDrawable(gm);
  osg::Texture2D* texture = new osg::Texture2D(osgDB::readImageFile(filename));
  geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);

  camera->addChild(geode);
  return camera.release();
}

osg::Node* create_parallel_light(int num, const osg::Vec3 & dir, const osg::Vec4 & color)
{
  osg::ref_ptr<osg::Light> light = new osg::Light;
  light->setLightNum(num);
  light->setDiffuse(color);
  light->setPosition(osg::Vec4(1.0, 1.0, 1.0, 0.0));

  osg::ref_ptr<osg::LightSource> lightSource = new osg::LightSource;
  lightSource->setLight(light);

  osg::ref_ptr<osg::MatrixTransform> sourceTrans = new osg::MatrixTransform;
  sourceTrans->setMatrix(osg::Matrix::translate(dir));
  sourceTrans->addChild(lightSource.get());
  return sourceTrans.release();
}

osg::Camera* create_axes_camera(const double x, const double y,
                                const double width, const double height)
{
  osg::Camera* camera = new osg::Camera;
  camera->setViewport(x, -6, 15, 15);
  const double s = 4;
  camera->setProjectionMatrix(osg::Matrix::ortho2D(-s, s, -s, s));

  camera->setAllowEventFocus(false);
  camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
  camera->setClearMask(GL_DEPTH_BUFFER_BIT);
  camera->setRenderOrder(osg::Camera::POST_RENDER);

  camera->setUpdateCallback(new AxisCameraUpdateCallback);
  osg::Node* axes = osgDB::readNodeFile("../../res/model/axes.osgt");
  if(axes == nullptr){
      std::cout << "[info] can not load axes.osgt" << std::endl;
    }
  else
    camera->addChild(axes);

  return camera;
}
