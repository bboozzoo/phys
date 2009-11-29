bin_PROGRAMS = phys
phys_SOURCES = main.cc \
			   system.cc \
			   gfx_sdl.cc \
			   input_sdl.cc \
			   prog.cc \
			   coord.cc \
			   log.cc \
			   event.cc \
			   world.cc \
			   world_gfx.cc \
			   world_phys.cc \
			   object_phys.cc \
			   point.cc \
			   sphere.cc \
			   box.cc \
			   plane.cc \
			   drawable.cc \
			   color.cc

phys_CXXFLAGS = $(LIBSDL_CFLAGS) \
				$(OPENGL_CFLAGS) \
				$(BOOST_CPPFLAGS) \
				$(ODE_CFLAGS)
phys_LDFLAGS = $(LIBSDL_LIBS) \
			   $(LIBSDLGFX_LIBS) \
			   $(OPENGL_LIBS) \
			   $(BOOST_LDFLAGS) \
			   $(BOOST_PROGRAM_OPTIONS_LIB) \
			   $(ODE_LIBS)

