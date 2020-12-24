#ifndef MYLIB_H
#define MYLIB_H

#ifdef ARR_EXPORT
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

#define ARR_DECL __cdecl

int isSquare(long long int x);

ARR_DLL int ARR_DECL get_new_mas(int *src, int src_len, int *dst, int *dst_len);

ARR_DLL void ARR_DECL sdvig(int* mas, int n, int k);

/*ARR_DLL int ARR_DECL add(int a, int b);

ARR_DLL int ARR_DECL divide(int a, int b, int *remainder);

ARR_DLL void ARR_DECL fill_array(double *arr, int n);

ARR_DLL double ARR_DECL avg(double *arr, int n);

ARR_DLL int ARR_DECL filter(double *src, int src_len, double *dst, int *dst_len);*/

#endif // MYLIB_H
