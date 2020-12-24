gcc -std=c99 -Wall -Werror -c mylib.c

gcc -shared mylib.o -Wl,--subsystem,windows -o mylib.dll