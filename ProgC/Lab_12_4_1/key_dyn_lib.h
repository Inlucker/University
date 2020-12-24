#ifndef KEY_H
#define KEY_H

#ifdef ARR_EXPORT
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

#define MEMORY_ERROR -3
#define FILTR_ERROR -5

ARR_DLL int ARR_DECL key(const int *pb_src, const int *pe_src, int *pb_dst, float sr, int m);

#endif // KEY_H
