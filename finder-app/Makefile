
CC = $(CROSS_COMPILE)gcc
INCLUDES = -I/
TARGET = writer
LDFLAGS = 
CFLAGS = -g -Wall

SRC := writer.c
OBJS := $(SRC:.c=.o)

all: $(TARGET)

writer: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	-rm -f *.o $(TARGET) *.elf *.map
