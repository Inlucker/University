import ctypes

lib = ctypes.CDLL('./mylib.dll')

# int get_new_mas(int *src, int src_len, int *dst, int *dst_len)
_get_new_mas = lib.get_new_mas

_get_new_mas.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int))
_get_new_mas.restype = ctypes.c_int

def get_new_mas(nums):
  n = len(nums)
  arr = (ctypes.c_int * n)(*nums)

  n_res = ctypes.c_int(0)

  rc = _get_new_mas(arr, n, None, n_res)
  if rc:
    res = (ctypes.c_int * n_res.value)()

    rc = _get_new_mas(arr, n, res, n_res)

    return rc, list(res)
  else:
    return rc, list()

def get_new_mas2(nums):
  n = len(nums)
  arr = (ctypes.c_int * n)(*nums)

  m = n + 1
  n_res = ctypes.c_int(m)

  res = (ctypes.c_int * m)()

  rc = _get_new_mas(arr, n, res, n_res)
  #print(n_res.value)
  real_res = list()
  for i in range(n_res.value):
      real_res.append(res[i])
  print(real_res)
  return rc, list(real_res)

print("Tests for first type")

print(get_new_mas((0, 1, 2, 4, 9, 16)))

print(get_new_mas((1, 2, 3, 4)))

print(get_new_mas((1, -2, 3, -4, 5)))

print("Same tests for second type")

print(get_new_mas2((0, 1, 2, 4, 9, 16)))

print(get_new_mas2((1, 2, 3, 4)))

print(get_new_mas2((1, -2, 3, -4, 5)))


