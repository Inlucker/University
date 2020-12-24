# Компилятор
CC := gcc

# Опции компиляции
CFLAGS := -std=c99 -Wall -Werror

# Общие объектные файлы
#OBJS := 

# Файлы динамической библиотеки
DYN := mylib.o

# Файлы библиотеки
LIBS :=


dyn: mylib.dll
dyn: LIBS += mylib.dll

unit: CFLAGS += -g3
unit: mylib.dll
unit: LIBS += mylib.dll
unit : unit_tests.exe

#app%.exe : $(OBJS) main%.o
#	$(CC) $^ $(LIBS) -o $@

unit_tests.exe : $(OBJS) check_unit_tests.o
	$(CC) $^ $(LIBS) -o $@ -lcheck
	
mylib.dll : $(DYN)
	$(CC) -shared $^ -Wl,--subsystem,windows -o $@

%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

.PHONY : stat_lib clean debug release
clean :
	$(RM) *.o *.exe *.a *.dll
