CC = gcc
CFLAGS = -I../include -c
TARGET = ls
OBJS = main.o dir.o common.o opts.o print.o queue.o

$(TARGET) : $(OBJS) 
	$(CC) $(OBJS) -o $(TARGET) 

%.o : %.c
	$(CC) $(CFLAGS) -g $<

clean :
	rm -f $(OBJS) $(TARGET)

