#ifndef QT_PLATFORM_OSG_UTILS_H
#define QT_PLATFORM_OSG_UTILS_H

#include <osg/NodeCallback>
#include <osg/Camera>
#include <osgViewer/View>

osg::Camera* add_image_camera(std::string filename, double x, double y,
                              double width, double height);

class AxisCameraUpdateCallback :public osg::NodeCallback
{
public:
  virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) {
    if (nv->getVisitorType() == osg::NodeVisitor::UPDATE_VISITOR) {
        osg::Camera* camera = dynamic_cast<osg::Camera*>(node);
        if (camera) {
            osg::View* view = camera->getView();
            if (view && view->getNumSlaves() > 0) {
                osg::View::Slave* slave = &view->getSlave(0);
                if (slave->_camera.get() == camera) {
                    osg::Camera* masterCam = view->getCamera();
                    osg::Vec3 eye, center, up;
                    masterCam->getViewMatrixAsLookAt(eye, center, up, 30);
                    osg::Matrixd matrix;
                    matrix.makeLookAt(eye - center, osg::Vec3(0, 0, 0), up); // always look at (0, 0, 0)
                    camera->setViewMatrix(matrix);
                  }
              }
          }
      }
    traverse(node, nv);
  }
};

osg::Node* create_parallel_light(int num, const osg::Vec3 & dir, const osg::Vec4 & color);

osg::Camera* create_axes_camera(const double x, const double y,
                                const double width, const double height);

#endif // QT_PLATFORM_OSG_UTILS_H
