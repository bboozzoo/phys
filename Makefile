TARGET=phys
SRCS=main.cc bin.cc system.cc gfx_sdl.cc
CFLAGS=-Wall -std=gnu++0x `pkg-config --cflags sdl`
LDFLAGS=`pkg-config --libs sdl`

all: $(TARGET) 
$(TARGET): $(SRCS:.cc=.o)
	$(CXX) -o $@ $(LDFLAGS) $^

%.o: %.cc
	$(CXX) -c -o $@ $(CFLAGS) $<

clean:
	rm -f $(TARGET)
	rm -f *.o
	rm -f *~

ifeq ($(shell test -r Makefile.depend && echo yes),yes)
include Makefile.depend
endif

.PHONY: clean

