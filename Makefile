NAME          = parse_dot
DEPEND        = parse common
TEST_DEPEND   = parse common

COVERAGE ?= 0

ifeq ($(COVERAGE),0)
CXXFLAGS = -std=c++20 -g -Wall -fmessage-length=0 -O2
LDFLAGS  =
else
CXXFLAGS = -std=c++20 -g -Wall -fmessage-length=0 -O0 --coverage -fprofile-arcs -ftest-coverage
LDFLAGS  = --coverage -fprofile-arcs -ftest-coverage 
endif

SRCDIR        = $(NAME)
INCLUDE_PATHS = $(DEPEND:%=-I../%) -I.
LIBRARY_PATHS =
LIBRARIES     =

SOURCES	     := $(shell mkdir -p $(SRCDIR); find $(SRCDIR) -name '*.cpp')
OBJECTS	     := $(SOURCES:%.cpp=build/%.o)
DEPS         := $(shell mkdir -p build/$(SRCDIR); find build/$(SRCDIR) -name '*.d')
TARGET	      = lib$(NAME).a

TESTDIR       = tests

ifndef GTEST
override GTEST=../../googletest
endif

TEST_INCLUDE_PATHS = -I$(GTEST)/googletest/include $(TEST_DEPEND:%=-I../%) -I.
TEST_LIBRARY_PATHS = -L$(GTEST)/build/lib $(TEST_DEPEND:%=-L../%) -L.
TEST_LIBRARIES = -l$(NAME) $(TEST_DEPEND:%=-l%) -pthread -lgtest

TESTS        := $(shell mkdir -p $(TESTDIR); find $(TESTDIR) -name '*.cpp')
TEST_OBJECTS := $(TESTS:%.cpp=build/%.o) build/$(TESTDIR)/gtest_main.o
TEST_DEPS    := $(shell mkdir -p build/$(TESTDIR); find build/$(TESTDIR) -name '*.d')
TEST_TARGET   = test

ifeq ($(OS),Windows_NT)
    CXXFLAGS += -D WIN32
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CXXFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CXXFLAGS += -D AMD64
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CXXFLAGS += -D IA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CXXFLAGS += -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        CXXFLAGS += -D OSX -mmacos-version-min=15.0
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CXXFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CXXFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CXXFLAGS += -D ARM
    endif
endif


all: lib

lib: $(TARGET)

tests: lib $(TEST_TARGET)

coverage: clean
	$(MAKE) COVERAGE=1 tests
	./$(TEST_TARGET) || true  # Continue even if tests fail
	lcov --capture --directory build/$(SRCDIR) --output-file coverage.info
	lcov --ignore-errors unused --remove coverage.info '/usr/include/*' '*/googletest/*' '*/tests/*' --output-file coverage_filtered.info
	genhtml coverage_filtered.info --output-directory coverage_report

$(TARGET): $(OBJECTS)
	ar rvs $(TARGET) $(OBJECTS)

build/$(SRCDIR)/%.o: $(SRCDIR)/%.cpp 
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE_PATHS) -MM -MF $(patsubst %.o,%.d,$@) -MT $@ -c $<
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(INCLUDE_PATHS) -c -o $@ $<

$(TEST_TARGET): $(TEST_OBJECTS) $(OBJECTS) $(TARGET)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TEST_LIBRARY_PATHS) $(TEST_OBJECTS) $(TEST_LIBRARIES) -o $(TEST_TARGET)

build/$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(TEST_INCLUDE_PATHS) -MM -MF $(patsubst %.o,%.d,$@) -MT $@ -c $<
	$(CXX) $(CXXFLAGS) $(TEST_INCLUDE_PATHS) $< -c -o $@

build/$(TESTDIR)/gtest_main.o: $(GTEST)/googletest/src/gtest_main.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(TEST_INCLUDE_PATHS) $< -c -o $@

include $(DEPS) $(TEST_DEPS)

clean:
	rm -rf build $(TARGET) $(TEST_TARGET) $(WASM_BUILD_DIR) coverage.info coverage_filtered.info coverage_report *.gcda *.gcno

clean-test:
	rm -rf build/$(TESTDIR) $(TEST_TARGET)

clean-coverage:
	rm -rf coverage.info coverage_filtered.info coverage_report *.gcda *.gcno


# wasm support for bin/studio
WASM_BUILD_DIR = build-wasm
WASM_TARGET = $(WASM_BUILD_DIR)/lib$(NAME).a
WASM_CXX = em++
WASM_CXXFLAGS = -std=c++20 -Os -g0 -fvisibility=hidden

$(WASM_BUILD_DIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(WASM_CXX) $(WASM_CXXFLAGS) $(INCLUDE_PATHS) -c -o $@ $<

WASM_OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(WASM_BUILD_DIR)/%.o,$(SOURCES))

$(WASM_TARGET): $(WASM_OBJECTS)
	@mkdir -p $(@D)
	emar rcs $@ $^

wasm: $(WASM_TARGET)
