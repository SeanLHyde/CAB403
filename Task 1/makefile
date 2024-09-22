CC=gcc
CFLAGS=-I.
DEPS = dbl_vector.h
OBJ = dbl_vector.o dbl_vector_t.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

dbl_vector: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)