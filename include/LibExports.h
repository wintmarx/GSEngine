#ifndef GSENGINE_API

#ifndef _MSC_VER
#define GSENGINE_API
#else
#ifdef GSENGINE_EXPORT
#define GSENGINE_API __declspec(dllexport)
#else
#define GSENGINE_API __declspec(dllimport)
#endif
#endif

#endif
