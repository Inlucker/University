# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=c99 -Wall -pedantic -ggdb

# Общие объектные файлы
OBJS := io_functions.o mtrx_functions.o

debug : CFLAGS += -g3
debug : app.exe

release : CFLAGS += -DNDEBUG -g0
release : app.exe

unit: CFLAGS += -g3
unit : unit_tests.exe

app.exe : $(OBJS) main.o
	$(CC) $^ -o $@

unit_tests.exe : $(OBJS) check_unit_tests.o
	$(CC) $^ -o $@ -lcheck

%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

.PHONY : clean debug release
clean :
	$(RM) *.o *.exe
