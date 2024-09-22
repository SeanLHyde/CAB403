CC=gcc
CFLAGS=-I.
DEPS = operations.h
OBJ = shm_ipc.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

shm_ipc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)