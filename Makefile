SRCDIR       =  parse_dot
CXXFLAGS	 =  -O2 -g -Wall -fmessage-length=0 -I../parse -I../common
SOURCES	    :=  $(shell find $(SRCDIR) -name '*.cpp')
OBJECTS	    :=  $(SOURCES:%.cpp=%.o)
TARGET		 =  lib$(SRCDIR).a

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ar rvs $(TARGET) $(OBJECTS)

%.o: $(SRCDIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
clean:
	rm -f $(OBJECTS) $(TARGET)
