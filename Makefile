.PHONY: all clean dirs
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -O2 -std=c23 -I betterc/inc/

AR = ar
ARFLAGS = -rcs

C_SRC := $(shell find betterc/lib -type f -name "*.c")
C_OBJ := $(patsubst betterc/lib/%.c, build/lib/%.o, $(C_SRC))

TEST_SRC := src/test_string.c
TEST_BIN := build/test_string

all: dirs build/libbetterc.a $(TEST_BIN)
build/libbetterc.a: $(C_OBJ)
	$(AR) $(ARFLAGS) $@ $^

build/lib/%.o: betterc/lib/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/%: tests/%.c build/libbetterc.a
	$(CC) $(CFLAGS) -o $@ $< -Lbuild/ -lbetterc

dirs:
	@ mkdir -p build
	@ mkdir -p build/lib

clean:
	rm -rf build/
