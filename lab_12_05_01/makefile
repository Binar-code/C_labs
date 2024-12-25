CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra \
    -Wfloat-equal -Wfloat-conversion -Wvla -Iinc
TEST_LDFLAGS := -lcheck -lm -lsubunit 

SCR_DIR := ./src/
OUT_DIR := ./out/
UNIT_DIR := ./unit_tests/

LIBC := $(SCR_DIR)arr_lib.c
LIBARR := $(OUT_DIR)libarr.a
MAIN := $(SCR_DIR)main.c
UNIT_SRC :=	$(wildcard unit_tests/*.c)
UNIT_OBJS :=  $(patsubst unit_tests/%.c,$(OUT_DIR)%.o,$(UNIT_SRC))

.PHONY: clean func out build_static build_unit_static test

clean:
	find . -type f \( -name "*.so" -o -name "*.a" -o -name "*.d" -o -name "*.exe" -o -name "*.o" -o -name "*.gcno" -o -name "temp_out.txt" -o -name "*.gcda" -o -name "*.info" -o -name "*.gcov" \) -delete

func:
	-./func_tests/scripts/func_tests.sh

out:
	mkdir -p out

# СТАТИЧЕСКАЯ БИБЛИОТЕКА

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

# ДИНАМИЧЕСКАЯ БИБЛИОТЕКА (динамическая компоновка)

build_dynamic_lib: clean | out
	$(CC) $(CFLAGS) -c $(LIBC) -o $(OUT_DIR)arr_lib.o
	$(CC) -o $(OUT_DIR)libarr.so -shared $(OUT_DIR)arr_lib.o

build_dynamic: clean
	$(MAKE) build_dynamic_lib
	$(CC) $(CFLAGS) -c $(MAIN) -o $(OUT_DIR)main.o
	$(CC) -o app.exe $(OUT_DIR)main.o -L$(OUT_DIR) -larr -Wl,-rpath,$(OUT_DIR)

build_unit_dynamic: clean
	$(MAKE) build_dynamic_lib
	$(foreach src, $(UNIT_SRC), $(CC) $(CFLAGS) $(TEST_LDFLAGS) -c $(src) -o $(OUT_DIR)$(notdir $(src:.c=.o));)
	$(CC) $(CFLAGS) $(UNIT_OBJS) -o app.exe -L$(OUT_DIR) -larr $(TEST_LDFLAGS) -Wl,-rpath,$(OUT_DIR)

test: clean
	@echo STATIC LIB TEST
	@echo Func tests
	@$(MAKE) build_static 1>/dev/null
	@$(MAKE) func
	@echo "Unit tests"
	@$(MAKE) build_unit_static 1>/dev/null
	@./app.exe
	@echo
	@echo "DYNAMIC LIB (dynamic linkage)"
	@echo Func tests
	@$(MAKE) build_dynamic 1>/dev/null
	@$(MAKE) func
	@echo Unit tests
	@$(MAKE) build_unit_dynamic 1>/dev/null
	@./app.exe
	@$(MAKE) clean
