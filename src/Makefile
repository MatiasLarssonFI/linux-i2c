# executable name
BIN=i2c-test

# compiler and linker options
CXX=g++
LIBS=
CXXFLAGS=-std=c++11
LFLAGS=
INCLUDES=-Iinclude

# directory paths
OBJDIR=../obj
SRCDIR=.
BINDIR=../bin

# executable path
BINPATH=$(BINDIR)/$(BIN)

CXXSOURCES := $(wildcard *.cxx)
CSOURCES := $(wildcard *.c)
OBJECTS := $(addprefix $(OBJDIR)/,$(CXXSOURCES:.cxx=.o)) $(addprefix $(OBJDIR)/,$(CSOURCES:.c=.o))
debug: CXXFLAGS += -g -Wall -Wextra

release: CXX=$(RELEASE_TOOLPREFIX)g++
release: CXXFLAGS += -O2

debug: $(BINPATH)
release: $(BINPATH)

$(BINPATH): $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS) $(LFLAGS)

$(OBJDIR)/%.o: %.c*
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BINPATH)
	rm -f $(OBJDIR)/*.o

.PHONY: debug release clean
