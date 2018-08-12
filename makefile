CC = gcc

CFLAGS  = -std=c99
CFLAGS += -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

VFLAGS  = --quiet
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1

INCLUDES = $(shell echo src/*.h)

LDLIBS = -lrt

test: tests.out
	./tests.out

tests.out: test/test_rb_tree.c src/rb_tree.c src/rb_tree.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) src/rb_tree.c test/vendor/unity.c test/test_rb_tree.c -o tests.out

memcheck: tests.out
	@valgrind $(VFLAGS) ./tests.out
	@echo "Memory check passed"

%.o: src/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *.out *.out.dSYM *~

