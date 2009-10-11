TARGET=phys
SRCS=main.cc bin.cc system.cc gfx_sdl.cc input_sdl.cc sim.cc point.cc coord.cc log.cc
CFLAGS=-ggdb -g3 -Wall -std=gnu++0x `pkg-config --cflags sdl`
LDFLAGS=`pkg-config --libs sdl` -lSDL_gfx -lboost_program_options

all: $(TARGET) 
$(TARGET): $(SRCS:.cc=.o)
	$(CXX) -o $@ $(LDFLAGS) $^

%.o: %.cc
	$(CXX) -c -o $@ $(CFLAGS) $<

clean:
	rm -f $(TARGET)
	rm -f *.o
	rm -f *~

cscope:
	find . -type f -name '*.cc' -o -name '*.h' | grep -v git | grep -v *~ > cscope.files
	cscope -buv

ifeq ($(shell test -r Makefile.depend && echo yes),yes)
include Makefile.depend
endif

.PHONY: clean

