CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17 -lstdc++ -I../ -I.
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
LIBS=-lgtest

OS      := $(shell uname -s)
OS_NAME := $(OS)

ifeq ($(OS), Linux)
  OPEN_CMD = xdg-open
  OS_NAME=$(shell grep -o 'Ubuntu' /etc/os-release | head -n 1)
  LIBS += -lm
endif
ifeq ($(OS_NAME), Ubuntu)
  LIBS += -lsubunit -lrt -lpthread
  CFLAGS += -Wformat=0
endif
ifeq ($(OS), Darwin)
  OPEN_CMD = open
endif

BUILD_DIR    := build
GCOV_REP_DIR := $(BUILD_DIR)/report

ifeq ($(wildcard $(BUILD_DIR)), )
  $(shell mkdir $(BUILD_DIR))
endif

CORE_MODULES  := suites-core $(wildcard suites-core/*/)
UTILS_MODULES := suites-utils $(wildcard suites-utils/*/)
MODULES       := . $(CORE_MODULES) $(UTILS_MODULES)

SRC_DIRS := $(MODULES)
SRC      := $(foreach sdir,$(SRC_DIRS),$(wildcard $(sdir)/*.cpp))
OBJ      := $(addprefix $(BUILD_DIR)/,$(notdir $(SRC:%.cpp=%.o)))

vpath %.cpp $(SRC_DIRS)

TARGET_NAME := s21_containers_test
TARGET      := s21_containers_test.exe

S21_CONTAINERS_LIB := ../s21_containers.a

.PHONY: all rebuild gcov gcov_flags debug debug_flags valgrind_check
.DELETE_ON_ERROR:

all: $(TARGET)

rebuild: clean all

disable_warns:
	$(eval CFLAGS=-std=c++17 -lstdc++ -I../ -I.)

test_no_warn: disable_warns all

gcov: clean_obj debug_flags gcov_flags gcov_$(TARGET)

gcov_flags:
	$(eval CFLAGS += $(GCOV_FLAGS))

debug: clean debug_flags $(TARGET)

debug_flags:
	$(eval CFLAGS += -g -DDEBUG)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(S21_CONTAINERS_LIB) -o $@ $(LIBS)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# DEFECT: Production code dir only. Needed dir with tests also.
gcov_$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(S21_CONTAINERS_LIB) -o $(BUILD_DIR)/$@ $(LIBS)
	$(BUILD_DIR)/$@
	lcov -o $(BUILD_DIR)/$(TARGET_NAME).info -c -d ../$(BUILD_DIR)/ -d $(BUILD_DIR)/
	lcov --remove $(BUILD_DIR)/$(TARGET_NAME).info '/usr/include/*' -o $(BUILD_DIR)/$(TARGET_NAME).info
	genhtml -o $(GCOV_REP_DIR) $(BUILD_DIR)/$(TARGET_NAME).info
	nohup $(OPEN_CMD) ./$(BUILD_DIR)/report/index.html >/dev/null 2>&1 &

valgrind_check:
	$(shell valgrind $(VALGRIND_FLAGS) --log-file=$(BUILD_DIR)/RESULT_VALGRIND.txt ./$(TARGET))

.PHONY: clean clean_obj clean_gcov

clean_obj:
	cd $(BUILD_DIR) && rm -rf *.o *.a *.exe *.so
	rm -rf *.o *.a *.exe *.so

clean_gcov:
	rm -rf *.out
	cd $(BUILD_DIR) && rm -rf *.gcda *.gcno *.info
	cd $(BUILD_DIR) && rm -rf report

clean: clean_obj clean_gcov
	cd $(BUILD_DIR) && rm -rf *.txt
	rm -rf *.json
