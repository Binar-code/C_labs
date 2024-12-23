CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wextra \
    -Wfloat-equal -Wfloat-conversion -Wvla -Iinc
TEST_CFLAGS := -g3 -O0
LDFLAGS := -lm
TEST_LDFLAGS := -lcheck -lm -lsubunit 
COVERAGE_FLAGS := -fprofile-arcs -ftest-coverage --coverage

SCR_DIR := ./src/
OUT_DIR := ./out/

SRCS := $(wildcard $(SCR_DIR)*.c)
MAIN_OBJ := $(OUT_DIR)main.o
OBJS := $(filter-out $(MAIN_OBJ), $(patsubst $(SCR_DIR)%.c,$(OUT_DIR)%.o,$(SRCS)))

UNIT_SRCS := $(wildcard unit_tests/*.c)
UNIT_OBJS := $(patsubst unit_tests/%.c,$(OUT_DIR)%.o,$(UNIT_SRCS))

.PHONY: memory ub address clean func unit coverage valgrind

unit_tests.exe: $(UNIT_OBJS) $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS) $(TEST_LDFLAGS)

$(OUT_DIR)%.o: $(SCR_DIR)/%.c | out
	$(CC) $(CFLAGS) -MMD -MF $(@:.o=.d) -c $< -o $@

$(OUT_DIR)%.o: unit_tests/%.c | out
	$(CC) $(CFLAGS) $(TEST_CFLAGS) -MMD -MF $(@:.o=.d) -c $< -o $@

out:
	mkdir -p out

DEPS := $(OBJS:.o=.d) $(MAIN_OBJ:.o=.d)
UNIT_DEPS := $(UNIT_OBJS:.o=.d)
-include $(DEPS)
-include $(UNIT_DEPS)

memory:
	$(MAKE) clean
	$(MAKE) CC=clang CFLAGS="$(CFLAGS) $(TEST_CFLAGS) -fsanitize=memory" LDFLAGS="$(LDFLAGS) -fsanitize=memory $(TEST_LDFLAGS)" app.exe -k  

ub:
	$(MAKE) clean
	$(MAKE) CC=clang CFLAGS="$(CFLAGS) $(TEST_CFLAGS) -fsanitize=undefined" LDFLAGS="$(LDFLAGS) -fsanitize=undefined $(TEST_LDFLAGS)" app.exe -k

address:
	$(MAKE) clean
	$(MAKE) CC=clang CFLAGS="$(CFLAGS) $(TEST_CFLAGS) -fsanitize=address" LDFLAGS="$(LDFLAGS) -fsanitize=address $(TEST_LDFLAGS)" app.exe -k

clean:
	find . -type f \( -name "*.d" -o -name "*.exe" -o -name "*.o" -o -name "*.gcno" -o -name "valgrind-out.txt" \
		-o -name "temp_out.txt" -o -name "*.gcda" -o -name "*.info" -o -name "*.gcov" \) -delete
	-rm -r ./coverage_report/

unit:
	$(MAKE) unit_tests.exe
	./unit_tests.exe
