#ifndef QT_PLATFORM_CMENU_H
#define QT_PLATFORM_CMENU_H

#include <QPushButton>
#include <QObject>
#include <QSignalMapper>


class CMenu : public QObject
{
  Q_OBJECT
public:
  CMenu(QWidget *parent=NULL, double radius=100) : parent_(parent), radius_(radius) {}
  void setParent(QWidget *parent) {
    parent_ = parent;
  }
  void setRadius(const double radius) {
    radius_ = radius;
  }

  void addItem(QSignalMapper *signal_mapper, const std::string &map_name, const std::string &icon_file, const std::string &tool_tip);
  void show(const QPoint &pos);
public slots:
  void hide();
private:
  QList<QPushButton*> button_list_;
  QWidget *parent_;
  double radius_;
};

#endif // QT_PLATFORM_CMENU_H
 