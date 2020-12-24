import ctypes

lib = ctypes.CDLL('./mylib.dll')

# int filter(double *src, int src_len, double *dst, int *dst_len);
_get_new_mas = lib.get_new_mas

_get_new_mas.argtypes = (ctypes.POINTER(ctypes.c_double), ctypes.c_int, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_int))
_get_new_mas.restype = ctypes.c_int

def get_new_mas(nums):
  n = len(nums)
  arr = (ctypes.c_double * n)(*nums)
  
  n_res = ctypes.c_int(0)
  
  rc = _get_new_mas(arr, n, None, n_res)
  if rc:
    res = (ctypes.c_double * n_res.value)()
	
    rc = _get_new_mas(arr, n, res, n_res)
	
    return rc, list(res)	
  else:
    return rc, list()
	
print(get_new_mas((1, 2, 4, 9, 16)))

print(get_new_mas((1, 2, 3, 4)))

print(get_new_mas((1, -2, 3, -4, 5)))


