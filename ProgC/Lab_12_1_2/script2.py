import ctypes

lib = ctypes.CDLL('./mylib.dll')

# void sdvig(int* mas, int n, int k);
_sdvig = lib.sdvig

_sdvig.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.c_int)
_sdvig.restype = None

def sdvig(nums, k):
  n = len(nums)
  arr = (ctypes.c_int * n)(*nums)

  _sdvig(arr, n, k)
  return list(arr)

test = [1, 2, 3, 4]

k = 5

for i in range(5):
  print(test)
  test = sdvig(test, k)
