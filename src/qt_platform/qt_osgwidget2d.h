#ifndef QT_OSGWIDGET2D_H
#define QT_OSGWIDGET2D_H

#include <QGLWidget>
#include <QSignalMapper>
#include <QInputEvent>
#ifndef Q_MOC_RUN
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <QtWidgets/QGraphicsScene>
#include "../app/app.h"
#include "qevent_adapter.h"
#include "qt_osgwidget.h"
#include "cmenu.h"
#endif

namespace framework
{
  class OSG2DWidget : public OSGWidget
  {
    Q_OBJECT

  public:
    OSG2DWidget(QWidget* parent = 0, const QGLWidget* shareWidget = 0,
                Qt::WindowFlags f = 0, const std::string & osgviewer_name = "master", osg::ref_ptr<ui_handler> ui_hd = nullptr);

    virtual ~OSG2DWidget();
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> get_graphics_window() {
      return graphics_window_;
    }
    QEventAdapter	 qevent_adapter_;
    void acceptKeyPress(QKeyEvent* event);
    void acceptKeyRelease(QKeyEvent* event);
    void relayout();
    void getModelOrientation(double * matrix);
    enum edit_button_state{
      state_hide,
      state_show,
      state_ok_highlight,
      state_cancel_highlight,
    };
    void setEditButonState(int state);

    static OSG2DWidget* getInstance() { return instance; }

  public slots:
    void on_ok_cancel(int flag);
  signals:
    void edit_butong_clicked(int falg);//0 ok,-1 cancel
  protected:
    //void initMenu();
    virtual void paintEvent(QPaintEvent* paintEvent);
    virtual void paintGL();
    virtual void resizeGL(int width, int height);
    virtual void  resizeEvent(QResizeEvent *event);

    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    void setKeyboardModifiers(QInputEvent* event);

    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void dragEnterEvent(QDragEnterEvent *event);
    //  virtual void dropEvent(QDropEvent *event);

    virtual bool event(QEvent* event);
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);
    void  drawButton(QPainter& painter);
  private:

    osgGA::EventQueue* getEventQueue() const;
    app *the_app_;
    osg::ref_ptr<framework::render::working_space_scene_view> scene_view_;
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> graphics_window_;
    osg::Camera* camera_;
    QTimer *timer;
    CMenu cmenu_;

    static OSG2DWidget* instance;
  };
}

#endif // QT_OSGWIDGET_H
