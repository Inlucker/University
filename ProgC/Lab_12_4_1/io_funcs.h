#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#ifdef ARR_EXPORT
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

#include "defines.h"

ARR_DLL int ARR_DECL read_file_n(char *file_name, int *n);

ARR_DLL int ARR_DECL read_file(char *file_name, int *mas);

ARR_DLL int ARR_DECL output(char *file_name, int *mas, int n);

#endif // IO_FUNCS_H
