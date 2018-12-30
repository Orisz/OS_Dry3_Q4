CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS = main.o semaphore.o
RM = rm -f
# Creating the  executable
sem: $(OBJS)
	$(CCLINK) -o sem $(OBJS)
# Creating the object files
main.o: main.c semaphore.h
semaphore.o: semaphore.c semaphore.h pthread_includes.h
# Cleaning old files before new make
clean:
	$(RM) $(TARGET) *.o *~ "#"* core.*