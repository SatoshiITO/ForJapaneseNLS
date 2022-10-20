CC = fccpx
CFLAGS = -g -NRtrap

AR = ar

SRCS = mysse2.c

OBJS = $(SRCS:.c=.o)

HEADERS = mysse2.h

TARGET = libmysse2.a

.SUFFIXES: .c .o

.c.o:
        $(CC) $(CFLAGS) -c $< -o $@

libmysse2.a : $(OBJS)
        $(AR) crv $@ $^

clean:
        rm -rf $(OBJS) $(TARGET) *~
