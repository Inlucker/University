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

from tkinter import *

def print_new_mas(event):
  nums = list(map(int,ent1.get().split()))
  print(nums)
  x, y = get_new_mas(nums)
  if (x == 0):
    print(y)

#Creating window
window = Tk()
window.title("Lab_12_1_2")  
window.geometry("400x460+800+400")

A_label = Label(window, text = 'Исходный массив')
A_label.place(x = 60, y = 2, width = 280, height = 20)

ent1 = Entry(window, width=20, bd=2)
ent1.insert(0, '0')
ent1.place(x = 60, y = 26, width = 280, height = 20)

create_btn = Button(window, width = 10, text = "Get_new_mas")
create_btn.bind("<Button-1>", print_new_mas)
create_btn.place(x = 100, y = 52, width = 200, height = 25)

B_label = Label(window, text = 'Сдвиг на: ')
B_label.place(x = 60, y = 78, width = 280, height = 20)

ent2 = Entry(window, width=280,bd=2)
ent2.insert(0, '0')
ent2.place(x = 60, y = 104, width = 280, height = 20)

create_btn = Button(window, width = 10, text = "Sdvig")
#create_btn.bind("<Button-1>", print_new_mas)
create_btn.place(x = 100, y = 130, width = 200, height = 25)

window.mainloop()
