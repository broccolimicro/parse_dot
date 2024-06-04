NAME          = parse_dot
DEPEND        = parse common

SRCDIR        = $(NAME)
TESTDIR       = tests
GTEST        := ../../googletest
GTEST_I      := -I$(GTEST)/googletest/include -I.
GTEST_L      := -L$(GTEST)/build/lib -L.

CXXFLAGS	    = -O2 -g -Wall -fmessage-length=0 $(DEPEND:%=-I../%) -I.
LDFLAGS		    =  

SOURCES	     := $(shell mkdir -p $(SRCDIR); find $(SRCDIR) -name '*.cpp')
OBJECTS	     := $(SOURCES:%.cpp=build/%.o)
DEPS         := $(shell mkdir -p build/$(SRCDIR); find build/$(SRCDIR) -name '*.d')
TARGET		    = lib$(NAME).a

TESTS        := $(shell mkdir -p $(TESTDIR); find $(TESTDIR) -name '*.cpp')
TEST_OBJECTS := $(TESTS:%.cpp=build/%.o) build/$(TESTDIR)/gtest_main.o
TEST_DEPS    := $(shell mkdir -p build/$(TESTDIR); find build/$(TESTDIR) -name '*.d')
TEST_TARGET   = test

all: lib

lib: $(TARGET)

tests: lib $(TEST_TARGET)

$(TARGET): $(OBJECTS)
	ar rvs $(TARGET) $(OBJECTS)

build/$(SRCDIR)/%.o: $(SRCDIR)/%.cpp 
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) -MM -MF $(patsubst %.o,%.d,$@) -MT $@ -c $<
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c -o $@ $<

$(TEST_TARGET): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(GTEST_L) $^ -pthread -l$(NAME) -lgtest -o $(TEST_TARGET)

build/$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(GTEST_I) -MM -MF $(patsubst %.o,%.d,$@) -MT $@ -c $<
	$(CXX) $(CXXFLAGS) $(GTEST_I) $< -c -o $@

build/$(TESTDIR)/gtest_main.o: $(GTEST)/googletest/src/gtest_main.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(GTEST_I) $< -c -o $@

include $(DEPS) $(TEST_DEPS)

clean:
	rm -rf build $(TARGET) $(TEST_TARGET)
