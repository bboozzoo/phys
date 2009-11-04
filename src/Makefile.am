bin_PROGRAMS = phys
phys_SOURCES = main.cc \
			   bin.cc \
			   system.cc \
			   gfx_sdl.cc \
			   input_sdl.cc \
			   sim.cc \
			   point.cc \
			   coord.cc \
			   log.cc \
			   plane.cc \
			   event.cc

phys_CXXFLAGS = $(LIBSDL_CFLAGS) \
				$(BOOST_CPPFLAGS) \
				$(ODE_CFLAGS)
phys_LDFLAGS = $(LIBSDL_LIBS) \
			   $(LIBSDLGFX_LIBS) \
			   $(BOOST_LDFLAGS) \
			   $(BOOST_PROGRAM_OPTIONS_LIB) \
			   $(ODE_LIBS)

