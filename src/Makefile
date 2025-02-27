CC = gcc
CFLAGS = -pthread -mavx -lm -std=c11 -Wall
# -pthread: Enables POSIX threading.
# -mavx: Enables AVX (Advanced Vector Extensions) instruction set.
# -lm: Links the math library.
# -std=c11: Specifies the C standard to use (C11).
# -Wall: Enables all compiler warnings.
TARGET = main
# Specifies the name of the output executable


all: $(TARGET)
# The default target, which builds the final executable (main).

$(TARGET): main.o utils.o operations.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o utils.o operations.o -lm
# Added -lm at the very end because had error with sqrt from math
# This rule creates the executable main by linking main.o, utils.o, and operations.o using gcc.

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
# Compiles main.c into main.o.

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c
# Compiles utils.c into utils.o, ensuring that utils.h is present.

operations.o: operations.c operations.h
	$(CC) $(CFLAGS) -c operations.c

clean:
	rm -f $(TARGET) *.o