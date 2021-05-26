#if defined(_MSC_VER)
//  Microsoft
#ifdef EXPORT_DLL
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif
#elif defined(__GNUC__)
//  GCC
#ifdef EXPORT_DLL
#define API __attribute__((visibility("default")))
#else
#define API
#endif
#else
//  do nothing and hope for the best?
#define API
#pragma warning Unknown dynamic link import / export semantics.
#endif