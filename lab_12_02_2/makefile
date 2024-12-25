CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra \
    -Wfloat-equal -Wfloat-conversion -Wvla -Iinc
TEST_LDFLAGS := -lcheck -lm -lsubunit 

SCR_DIR := ./src/
OUT_DIR := ./out/
UNIT_DIR := ./unit_tests/

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c,$(OUT_DIR)%.o,$(SRCS))

UNIT_SRC :=	$(wildcard unit_tests/*.c)
UNIT_OBJS :=  $(patsubst unit_tests/%.c,$(OUT_DIR)%.o,$(UNIT_SRC))

LIBARR := $(OUT_DIR)libarr.so

.PHONY: build_lib clean out unit_tests build_unit

build_lib: clean | out
	$(CC) $(CFLAGS) -c $(SRCS) -o $(OBJS)
	$(CC) -o $(LIBARR) -shared $(OBJS)

build_unit: clean | out
	$(MAKE) build_lib
	$(foreach src, $(UNIT_SRC), $(CC) $(CFLAGS) $(TEST_LDFLAGS) -c $(src) -o $(OUT_DIR)$(notdir $(src:.c=.o));)
	$(CC) $(CFLAGS) $(UNIT_OBJS) -o app.exe -L$(OUT_DIR) -larr $(TEST_LDFLAGS) -Wl,-rpath,$(OUT_DIR)
	

unit_tests:
	@echo UNIT TESTS
	@$(MAKE) build_unit 1>/dev/null
	@./app.exe
	@$(MAKE) clean 1>/dev/null

out:
	mkdir -p out

clean:
	find . -type f \( -name "*.so" -o -name "*.a" -o -name "*.d" -o -name "*.exe" -o -name "*.o" -o -name "*.gcno" -o -name "temp_out.txt" -o -name "*.gcda" -o -name "*.info" -o -name "*.gcov" \) -delete

