# tests/Makefile
CC      := mpicc
CFLAGS  := -Wall -Wextra -O2 -I../include
SRCS    := test_io.c
TARGETS := $(SRCS:.c=)

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean