# 1. 变量定义区
# 定义编译器
CC       = gcc
# 定义编译选项：-Wall -Wextra 开启警告，-g 包含调试信息，-IInc/First 指定头文件搜索路径
CFLAGS   = -Wall -Wextra -g -IInc
# 最终生成的可执行文件名
TARGET   = test_protocol
# 需要链接的目标文件列表
OBJS     = pack.o protocol.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# pack.o 依赖于 src/pack.c 以及它包含的头文件
pack.o: src/pack.c Inc/pack.h Inc/protocol.h Inc/car_record.h
	$(CC) $(CFLAGS) -c -o $@ $<

# protocol.o 来自于 test/protocol.c（注意：这里不是 src/ 目录）
# 它可能也包含了 pack.h、protocol.h 等头文件
protocol.o: test/protocol.c Inc/pack.h Inc/protocol.h Inc/car_record.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)