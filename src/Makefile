CC          := g++
CSTANDARTS  := -std=c++17 -lstdc++
CWARNS      := -Wall -Werror -Wextra
CFLAGS      := $(CSTANDARTS) $(CWARNS) -I.
GCOV_FLAGS  := -fprofile-arcs -ftest-coverage
LIBS=

OS=$(shell uname -s)
ifeq ($(OS), Linux)
  LIBS = -lm
endif

BUILD_DIR := build

ifeq ($(wildcard $(BUILD_DIR)/.), )
  $(shell mkdir $(BUILD_DIR))
endif

CORE_MODULES  := core $(wildcard core/*/)
UTILS_MODULES := utils $(wildcard utils/*/)
MODULES       := $(CORE_MODULES) $(UTILS_MODULES)

SRC_DIRS := $(MODULES)
SRC      := $(foreach sdir,$(SRC_DIRS),$(wildcard $(sdir)/*.cpp))
OBJ      := $(addprefix $(BUILD_DIR)/,$(notdir $(SRC:%.cpp=%.o)))

vpath %.cpp $(SRC_DIRS)

TARGET := s21_containers.a

TEST_DIR := unit_tests
TEST_EXE := s21_containers_test.exe

.PHONY: all rebuild debug debug_flags test test_debug
.DELETE_ON_ERROR:

all: $(TARGET)

rebuild: clean all

$(TARGET): $(OBJ)
	ar rcs $@ $(OBJ)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(LIBS) -c $< -o $@

debug: clean debug_flags $(TARGET) test_debug

debug_flags:
	$(eval CFLAGS += -g -DDEBUG)

test: $(TARGET)
	cd $(TEST_DIR) && make
	cd $(TEST_DIR) && ./$(TEST_EXE) --gtest_output=json:test_results.json

test_no_warn: $(TARGET)
	cd $(TEST_DIR) && make test_no_warn
	cd $(TEST_DIR) && ./$(TEST_EXE)

test_debug: debug
	cd $(TEST_DIR) && make debug

run_playground: all
	$(CC) $(CSTANDARTS) -g $(LIBS) _playground/playground.c $(TARGET) -o _playground/playground.exe
	./_playground/playground.exe

run_playground_debug: debug run_playground

.PHONY: gcov_report gcov_flags valgrind_check

gcov_report: clean_obj debug_flags gcov_flags $(TARGET)
	cd $(TEST_DIR) && make gcov

gcov_flags:
	$(eval CFLAGS += $(GCOV_FLAGS))

valgrind_check: debug
	cd $(TEST_DIR) && make valgrind_check

.PHONY: clean clean_obj clean_gcov

clean_obj:
	cd $(BUILD_DIR) && rm -rf *.o *.a *.exe *.so
	rm -rf *.o *.a *.exe *.so

clean_gcov:
	cd $(BUILD_DIR) && rm -rf *.gcda *.gcno *.info *.out
	cd $(TEST_DIR) && make clean

clean: clean_obj clean_gcov

.PHONY: clang_check clang

clang_check:
	cp ../materials/linters/.clang-format ./
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -n {} \;
	rm .clang-format

clang:
	cp ../materials/linters/.clang-format ./
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i {} \;
	rm .clang-format
