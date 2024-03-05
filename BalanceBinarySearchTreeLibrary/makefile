# 自定义变量
# 变量赋值
OBJ=$(patsubst %.c, %.o, $(wildcard ./*.c))
TARGET=main

LDFALGS=-L./src_so
LIBS=-lSoMyTree

.PHONY: $(TARGET)

$(TARGET):$(OBJ)
	sudo gcc $^ $(LIBS) $(LDFALGS) -o $@


main.o:main.c
	sudo gcc -c $^ -o $@

clean:
	sudo $(RM) *.o $(TARGET)