#ifndef _QT_PLATFORM_API_H_
#define _QT_PLATFORM_API_H_


#ifdef _MSC_VER
#if defined QT_PLATFORM_EXPORT
#define QT_PLATFORM_API __declspec(dllexport)
#else
#define QT_PLATFORM_API __declspec(dllimport) 
#endif
#else
#define QT_PLATFORM_API 
#endif


#endif // API_H

