CC = gcc
CFLAGS = -I../include -c
TARGET = ls
OBJS = main.o opts.o common.o file_util.o queue.o

$(TARGET) : $(OBJS) 
	$(CC) $(OBJS) -o $(TARGET) 

%.o : %.c
	$(CC) $(CFLAGS) -g $<

clean :
	rm -f $(OBJS) $(TARGET)

