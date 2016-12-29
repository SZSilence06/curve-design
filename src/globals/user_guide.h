#ifndef USER_GUIDE_H
#define USER_GUIDE_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/locale.hpp>

class SysConfig
{
public:
  static const SysConfig &getSysConfig() {
    static SysConfig sys_config("../../res/config.xml");
    return sys_config;
  }
  template<typename T>
  T get(const std::string &st, T default_value) const {
    return pt_.get<T>(st, default_value);
  }
  template<typename T>
  T get(const std::string &st) const {
    return pt_.get<T>(st);
  }

  const boost::property_tree::ptree get_child(const std::string &st)const {
    return pt_.get_child(st);
  }

private:
  SysConfig(const std::string &file_path) {
    using boost::property_tree::ptree;
    read_xml(file_path, pt_);
  }
  boost::property_tree::ptree pt_;
};

#endif /* USER_GUIDE_H */
