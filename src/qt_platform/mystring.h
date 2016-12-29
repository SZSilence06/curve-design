#ifndef QT_PLATFORM_STRING_H
#define QT_PLATFORM_STRING_H

#include <QString>
//#include <boost/type_traits.hpp>

#ifdef USE_UNICODE
inline std::wstring convert_qstring(const QString &s){
  return s.toStdwString();
}

#else
inline std::string convert_qstring(const QString &s){
  //return s.toLocal8Bit().data();
  return s.toStdString();
}
#endif

#endif // QT_PLATFORM_STRING_H
