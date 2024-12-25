CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra \
    -Wfloat-equal -Wfloat-conversion -Wvla -Iinc
LDFLAGS := -lm
TEST_LDFLAGS := -lcheck -lm -lsubunit 

SCR_DIR := ./src/
OUT_DIR := ./out/
UNIT_DIR := ./unit_tests/

LIBC := $(SCR_DIR)arr_lib.c
LIBARR := $(OUT_DIR)libarr.a
MAIN := $(SCR_DIR)main.c
UNIT_SRC :=	$(wildcard unit_tests/*.c)

.PHONY: clean func out build_static build_unit_static test

clean:
	find . -type f \( -name "*.a" -o -name "*.d" -o -name "*.exe" -o -name "*.o" -o -name "*.gcno" -o -name "temp_out.txt" -o -name "*.gcda" -o -name "*.info" -o -name "*.gcov" \) -delete

func:
	-./func_tests/scripts/func_tests.sh

out:
	mkdir -p out

build_static_lib: clean | out
	$(CC) $(CFLAGS) -c $(SCR_DIR)arr_lib.c -o $(OUT_DIR)arr_lib.o
	ar cr $(LIBARR) $(OUT_DIR)arr_lib.o
	ranlib $(LIBARR)

build_static: clean
	$(MAKE) build_static_lib
	$(CC) $(CFLAGS) $(MAIN) $(LIBARR) -o app.exe

build_unit_static: clean
	$(MAKE) build_static_lib
	$(CC) $(CFLAGS) $(UNIT_SRC) $(LIBARR) $(TEST_LDFLAGS) -o app.exe

test:
	echo "Static lib test"
	echo "Func tests"
	@$(MAKE) build_static 1>/dev/null
	$(MAKE) func
	echo "Unit tests"
	$(MAKE) build_unit_static 1>/dev/null
	./app.exe
