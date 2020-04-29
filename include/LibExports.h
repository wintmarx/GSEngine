#ifndef GSENGINE_API

#ifdef GSENGINE_EXPORT
#define GSENGINE_API __declspec(dllexport)
#else
#define GSENGINE_API __declspec(dllimport)
#endif

#endif
