#include "cmenu.h"

#include <iostream>

#define _PI_ 3.1415925535897
#define _2PI_ 6.283185107

using namespace std;

void CMenu::addItem(QSignalMapper *signal_mapper, const std::string &map_name, const std::string &icon_file, const std::string &tool_tip)
{
  QIcon icon(QString::fromStdString(icon_file));
  QPushButton *button = new QPushButton(icon, "", parent_);
  button->setToolTip(QString::fromUtf8(tool_tip.c_str()));
  button->hide();
  button_list_.push_back(button);

  signal_mapper->setMapping(button, QString::fromUtf8(map_name.c_str()));
  connect(button, SIGNAL(released()), signal_mapper, SLOT(map()));
}

void CMenu::show(const QPoint &pos)
{
  size_t n = button_list_.size();
  double step = _2PI_/n;
  double angle = _PI_ / 2;
  for(int i = 0; i < button_list_.size(); ++i) {
    button_list_[i]->setGeometry(pos.x()+radius_*cos(angle), pos.y()+radius_*sin(angle), 35, 35);
    button_list_[i]->show();
    angle+= step;
  }
}

void CMenu::hide()
{
  for(QPushButton *button : button_list_) {
    button->hide();
  }
}
