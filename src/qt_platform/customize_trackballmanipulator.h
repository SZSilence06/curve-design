#ifndef CUSTOMIZE_TRACKBALLMANIPULATOR_H
#define CUSTOMIZE_TRACKBALLMANIPULATOR_H

#include <osgGA/OrbitManipulator>

#include "conf.h"

class my_trackball_manipulator : public osgGA::OrbitManipulator
{
  typedef osgGA::OrbitManipulator inherited;

public:
  /// Constructor.
  my_trackball_manipulator( int flags = DEFAULT_SETTINGS  ): inherited( flags), enable_mid_button_(true),
    enable_left_button_(true) {
    setVerticalAxisFixed( false );
  }
  my_trackball_manipulator(const my_trackball_manipulator& om,
                           const osg::CopyOp& copyOp = osg::CopyOp::SHALLOW_COPY)
    : inherited( om, copyOp ) {}

  void disable_mid_button() {
    enable_mid_button_ = false;
  }
  void enable_mid_button() {
    enable_mid_button_ = true;
  }

  void disable_left_button() {
    enable_left_button_ = false;
  }

  void enable_left_button() {
    enable_left_button_ = true;
  }

  META_Object( osgGA::osgGA, my_trackball_manipulator );
private:
  bool enable_mid_button_;
  bool enable_left_button_;
protected:
  virtual bool performMovementRightMouseButton( const double eventTimeDelta, const double dx, const double dy ) {
    return true;
  }
  virtual bool  performMovementLeftMouseButton (const double eventTimeDelta, const double dx, const double dy) {
    if(enable_left_button_)
      return osgGA::OrbitManipulator::performMovementLeftMouseButton(eventTimeDelta, dx, dy);
  }
  virtual bool performMovementMiddleMouseButton(const double eventTimdeDelta, const double dx, const double dy) {
	  if (enable_mid_button_)
		  return osgGA::OrbitManipulator::performMovementMiddleMouseButton(eventTimdeDelta, dx, dy);
  }
  virtual bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us ) {
    using namespace osgGA;
    osgGA::GUIEventAdapter::ScrollingMotion sm = ea.getScrollingMotion();

    // handle centering
    if( _flags & SET_CENTER_ON_WHEEL_FORWARD_MOVEMENT ) {

      if( ((sm == GUIEventAdapter::SCROLL_DOWN && _wheelZoomFactor > 0.)) ||
          ((sm == GUIEventAdapter::SCROLL_UP   && _wheelZoomFactor < 0.)) ) {

        if( getAnimationTime() <= 0. ) {
          // center by mouse intersection (no animation)
          setCenterByMousePointerIntersection( ea, us );
        } else {
          // start new animation only if there is no animation in progress
          if( !isAnimating() )
            startAnimationByMousePointerIntersection( ea, us );
        }

      }
    }

    if(enable_mid_button_) {
      switch( sm ) {
        // mouse scroll up event
      case GUIEventAdapter::SCROLL_UP: {
        // perform zoom
        zoomModel( _wheelZoomFactor, true );
        us.requestRedraw();
        us.requestContinuousUpdate( isAnimating() || _thrown );
        return true;
      }
      // mouse scroll down event
      case GUIEventAdapter::SCROLL_DOWN: {
        // perform zoom
        zoomModel( -_wheelZoomFactor, true );
        us.requestRedraw();
        us.requestContinuousUpdate( isAnimating() || _thrown );
        return true;
      }
      // unhandled mouse scrolling motion
      default:
        return false;
      }
    }
  }

};


#endif // CUSTOMIZE_TRACKBALLMANIPULATOR_H
