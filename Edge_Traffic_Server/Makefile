CC       = gcc
CFLAGS   = -Wall -Wextra -g -IInc
TARGET   = test_protocol
OBJS     = pack.o protocol.o array_table.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

pack.o: src/pack.c Inc/pack.h Inc/protocol.h Inc/car_record.h
	$(CC) $(CFLAGS) -c -o $@ $<

protocol.o: test/protocol.c Inc/pack.h Inc/protocol.h Inc/car_record.h Inc/array_table.h
	$(CC) $(CFLAGS) -c -o $@ $<

array_table.o: src/array_table.c Inc/array_table.h Inc/car_record.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)