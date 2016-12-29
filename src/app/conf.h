#ifndef _HJ_APP_CONF_H_
#define _HJ_APP_CONF_H_

#ifdef _MSC_VER
#  ifdef app_EXPORTS
#    define APPAPI __declspec(dllexport)
#  endif
#endif

#ifndef APPAPI
#  define APPAPI
#endif

#endif
