#include <cassert>
#include <stdexcept>
#include <vector>
#include <iostream>

#ifndef Q_MOC_RUN
#include "qt_osgwidget2d.h"
#include <osg/Material>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <osg/Shape>
#include <osg/Depth>
#include <osg/ShapeDrawable>
#include <osg/Matrix>
#include <osg/MatrixTransform>
#include <osg/Vec3>
#include "qt_wnd_server.h"
#include "../working_space_render/scene_view.h"
//#include "../manipulator/customize_trackballmanipulator.h"
#include "customize_trackballmanipulator.h"

#include "../UI_op/ui_handler.h"
#include "../working_space/working_space.h"
#include "../globals/user_guide.h"
#include "osg_utils.h"

#endif

#include <QTimer>
#include <QToolBar>
#include <QApplication>

#include <QKeyEvent>

#include <QLabel>
#include <QAction>
#include <QtWidgets/QWidget>
#include <QVBoxLayout>
#include <QMimeData>
#include <QStatusBar>
#include <QFile>
#include <QSignalMapper>
#include <QGraphicsOpacityEffect>
#include <QIcon>
#include <QString>

namespace framework{
  OSG2DWidget::OSG2DWidget(QWidget* parent, const QGLWidget* shareWidget,
                       Qt::WindowFlags f, const std::string & osgviewer_name, osg::ref_ptr<ui_handler> ui_hd)
    : OSGWidget(parent, shareWidget, f, osgviewer_name, ui_hd), cmenu_(this)
  {
    the_app_ = &app::get_instance();
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

    traits->x = this->x();
    traits->y = this->y();
    traits->width = this->width();
    traits->height = this->height();

    traits->windowDecoration = true;
    traits->doubleBuffer = true;
    //traits->pbuffer = false;
    traits->sharedContext = 0;
    //    traits->alpha = 8;
    //    traits->readDISPLAY();
    //    traits->setUndefinedScreenDetailsToDefaultScreen();


    graphics_window_ = new osgViewer::GraphicsWindowEmbedded(traits);

    scene_view_ = new framework::render::working_space_scene_view(osgviewer_name, framework::render::view_type::V2D);
    the_app_->push_scene_view(osgviewer_name, scene_view_.get());

    camera_ = scene_view_->getCamera();
    camera_->setViewport(this->x(), this->y(), this->width(), this->height());

    // set the projection matrix
     camera_->setProjectionMatrix(osg::Matrix::ortho2D(this->x(),this->width(),this->y(),this->height()));

     // set the view matrix
     camera_->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
     camera_->setViewMatrix(osg::Matrix::identity());

    camera_->setGraphicsContext(graphics_window_);
    camera_->setClearMask(GL_DEPTH_BUFFER_BIT);// | GL_COLOR_BUFFER_BIT );
    setMouseTracking(true);

    if (ui_hd != nullptr)
      qevent_adapter_.set_ui_hd(ui_hd);
    scene_view_->addEventHandler(ui_hd);
    my_trackball_manipulator* tb = new my_trackball_manipulator();

    tb->setAllowThrow(false); //禁用throw，以避免在archball中鼠标移动被解释为速度
    scene_view_->setCameraManipulator(tb);

    osg::ref_ptr<osg::Camera> img_camera = add_image_camera("../../res/background/black.jpg", this->x(), this->y(), this->width(), this->height());

    img_camera->setGraphicsContext(graphics_window_);

    if (scene_view_->get_render_tree()) {
        scene_view_->get_render_tree()->addChild(img_camera);
      //  scene_view_->get_render_tree()->addChild(axes_camera);
      }
    else {
        std::cerr << "# empty group" << std::endl;
      }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(40); //10 msec
  }

  OSG2DWidget::~OSG2DWidget()
  {
    timer->stop();
    delete timer;
    timer = nullptr;
    try{
      if (scene_view_.valid())
        scene_view_ = nullptr;
    } catch (...)
    { }
  }
  void OSG2DWidget::on_ok_cancel(int flag)
  {
    emit edit_butong_clicked(flag);
  }
  void OSG2DWidget::paintEvent(QPaintEvent* /* paintEvent */)
  {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    this->paintGL();
    //  this->swapBuffers();
    //drawButton(painter);

    painter.end();
  }

  void OSG2DWidget::paintGL()
  {
    scene_view_->frame();
  }
  void OSG2DWidget::drawButton(QPainter& painter)
  {
    //if (edit_button_state == state_hide)
    //{
    //	return;
    //}

    //int distance_border = 30;
    //int grid_width = 25;
    //QColor colorOk=QColor(118, 228, 126);
    //QColor colorCancel = QColor(232, 190, 194);
    //if (edit_button_state == state_ok_highlight)
    //{
    //	colorOk = QColor(0, 255, 0);
    //}
    //else if (edit_button_state == state_cancel_highlight)
    //{
    //	colorCancel = QColor(255, 0, 0);
    //}
    ////
    //int xStart = this->width() - (5 * grid_width + distance_border);
    //int yStart = this->height() - (5 * grid_width + distance_border);

    //rtOk.setX(xStart);
    //rtOk.setY(yStart + 3 * grid_width);
    //rtOk.setWidth(2 * grid_width);
    //rtOk.setHeight(2 * grid_width);
    //
    //rtCancel.setX(xStart + 3 * grid_width);
    //rtCancel.setY(yStart);
    //rtCancel.setWidth(2 * grid_width);
    //rtCancel.setHeight(2 * grid_width);

    //QBrush  okBrsh(colorOk);
    //QPen    okPen;
    //okPen.setBrush(okBrsh);
    //okPen.setWidth(12);
    //QPolygon plgOk;
    //plgOk.push_back(QPoint(xStart, yStart + 4 * grid_width));
    //plgOk.push_back(QPoint(xStart + grid_width, yStart + 5 * grid_width));
    //plgOk.push_back(QPoint(xStart + 2 * grid_width, yStart + 3 * grid_width));
    //painter.setPen(okPen);
    //painter.drawPolyline(plgOk);
    ////cancel
    //QBrush  cancelBrsh(colorCancel);
    //QPen    cancelPen;
    //cancelPen.setBrush(cancelBrsh);
    //cancelPen.setWidth(12);

    //painter.setPen(cancelPen);

    //QLine line_right(QPoint(xStart + 3 * grid_width, yStart), QPoint(xStart + 5 * grid_width, yStart + 2 * grid_width));
    //QLine line_left(QPoint(xStart + 3 * grid_width, yStart + 2 * grid_width), QPoint(xStart + 5 * grid_width, yStart));
    //painter.drawLine(line_right);
    //painter.drawLine(line_left);
  }
  void OSG2DWidget::resizeEvent(QResizeEvent *event)
  {
    QGLWidget::resizeEvent(event);
  }

  void OSG2DWidget::resizeGL(int width, int height)
  {
    graphics_window_->resized(this->x(), this->y(), width, height);
    camera_->setViewport(0, 0, this->width(), this->height()); //TODO: 仅对单相机时有效,看后期如果要用多相机，再改
    this->getEventQueue()->windowResize(0, 0, this->width(), this->height());

  }

  void OSG2DWidget::setKeyboardModifiers(QInputEvent* event)
  {
    int modkey = event->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier);
    unsigned int mask = 0;
    if (modkey & Qt::ShiftModifier) mask |= osgGA::GUIEventAdapter::MODKEY_LEFT_SHIFT;
    if (modkey & Qt::ControlModifier) mask |= osgGA::GUIEventAdapter::MODKEY_LEFT_CTRL;
    if (modkey & Qt::AltModifier) mask |= osgGA::GUIEventAdapter::MODKEY_LEFT_ALT;
    this->getEventQueue()->getCurrentEventState()->setModKeyMask(mask);
    update();
  }

  void OSG2DWidget::keyPressEvent(QKeyEvent* event)
  {
    setKeyboardModifiers(event);
    int a = event->key();
    switch (event->key())
      {
      case Qt::Key_Delete:
        this->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KeySymbol::KEY_Delete);
        break;
      default:
        this->getEventQueue()->keyPress((osgGA::GUIEventAdapter::KeySymbol) *(event->text().toLatin1().data()));
      }

    this->getEventQueue()->keyPress((osgGA::GUIEventAdapter::KeySymbol) *(event->text().toLatin1().data()));
  }

  void OSG2DWidget::keyReleaseEvent(QKeyEvent* event)
  {
    setKeyboardModifiers(event);
    this->getEventQueue()->keyRelease((osgGA::GUIEventAdapter::KeySymbol) *(event->text().toLatin1().data()));
  }

  void OSG2DWidget::mouseMoveEvent(QMouseEvent* event)
  {
    setKeyboardModifiers(event);
    this->getEventQueue()->mouseMotion(event->x(), event->y());
  }

  void OSG2DWidget::mousePressEvent(QMouseEvent* event)
  {
    int button = 0;
    switch (event->button())
      {
      case Qt::LeftButton: button = 1; break;
      case Qt::MidButton: button = 2; break;
      case Qt::RightButton: button = 3; break;
      case Qt::NoButton: button = 0; break;
      default: button = 0; break;
      }
    setKeyboardModifiers(event);
    this->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
  }

  //void OSG2DWidget::initMenu()
  //{
  //}

  void OSG2DWidget::mouseReleaseEvent(QMouseEvent* event)
  {
    int button = 0;
    switch (event->button())
      {
      case Qt::LeftButton: button = 1; break;
      case Qt::MidButton: button = 2; break;
      case Qt::RightButton: button = 3; break;
      case Qt::NoButton: button = 0; break;
      default: button = 0; break;
      }
    setKeyboardModifiers(event);
    this->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);
    update();
  }

  void OSG2DWidget::wheelEvent(QWheelEvent* event)
  {
    setKeyboardModifiers(event);
    this->getEventQueue()->mouseScroll(
          event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN);

  }

  void OSG2DWidget::mouseDoubleClickEvent(QMouseEvent *event)
  {
    int button = 0;
    switch (event->button())
      {
      case Qt::LeftButton: button = 1; break;
      case Qt::MidButton: button = 2; break;
      case Qt::RightButton: button = 3; break;
      case Qt::NoButton: button = 0; break;
      default: button = 0; break;
      }
    setKeyboardModifiers(event);
    this->getEventQueue()->mouseDoubleButtonPress(event->x(), event->y(), button);

  }
  void OSG2DWidget::showEvent(QShowEvent *e)
  {
    QGLWidget::showEvent(e);
  }
  void OSG2DWidget::hideEvent(QHideEvent * e)
  {
    QGLWidget::hideEvent(e);

  }

  void OSG2DWidget::dragEnterEvent(QDragEnterEvent *event)
  {
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
          }
        else {
            event->acceptProposedAction();
          }
      }
    else {
        event->ignore();
      }
  }

  bool OSG2DWidget::event(QEvent* event)
  {
    bool handled = QGLWidget::event(event);
    // This ensures that the OSG widget is always going to be repainted after the
    // user performed some interaction. Doing this in the event handler ensures
    // that we don't forget about some event and prevents duplicate code.
    switch (event->type()) {
      case QEvent::KeyPress:
      case QEvent::KeyRelease:
      case QEvent::MouseButtonDblClick:
      case QEvent::MouseButtonPress:
      case QEvent::MouseButtonRelease:
      case QEvent::Wheel:
      case QEvent::MouseMove:
        this->update();
        break;
      default:
        break;
      }
    return(handled);
  }

  void OSG2DWidget::acceptKeyPress(QKeyEvent* event)
  {
    keyPressEvent(event);
  }

  void OSG2DWidget::acceptKeyRelease(QKeyEvent* event)
  {
    keyReleaseEvent(event);
  }

  osgGA::EventQueue* OSG2DWidget::getEventQueue() const
  {
    osgGA::EventQueue* eventQueue = graphics_window_->getEventQueue();
    if (eventQueue)
      return(eventQueue);
    else
      throw(std::runtime_error("Unable to obtain valid event queue"));
  }

  void OSG2DWidget::getModelOrientation(double * matrix)
  {
    osg::Matrixd  orientation = scene_view_->getCameraManipulator()->getMatrix();
    memcpy(matrix, orientation.ptr(), 16 * sizeof(double));

  }
}
