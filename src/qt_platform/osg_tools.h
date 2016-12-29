#ifndef QT_PLATFORM_OSG_TOOLS_H
#define QT_PLATFORM_OSG_TOOLS_H

#include <osg/Camera>
#include <string>
#include <osg/Node>

namespace framework
{
osg::Camera* add_image_camera(std::string filename, double x, double y,
                              double width, double height);

osg::Node* create_parallel_light(int num, const osg::Vec3 & dir, const osg::Vec4 & color);

osg::Camera* create_axes_camera(const double x, const double y,
                                const double width, const double height);

}

#endif // QT_PLATFORM_OSG_TOOLS_H
