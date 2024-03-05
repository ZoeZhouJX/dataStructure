# 生成AVL动态库
TARGET=libSoMyTree.so
OBJ=$(patsubst %.c, %.o, $(wildcard ./*.c))

.PHONY:$(TARGET)

$(TARGET):$(OBJ)
	sudo $(CC) ./*.c -shared -fPIC -o $@
# 发布
	sudo cp $@ /usr/lib
	
# 模式匹配
%.o:%.c
	sudo $(CC) -c $^ -o $@

clean:
	sudo $(RM) *.o $(TARGET)
	sudo $(RM) /usr/lib/$(TARGET)

show:
	@echo $(CC) -c $(wildcard ./*.c) -o $(patsubst %.c, %.o, $(wildcard ./*.c))