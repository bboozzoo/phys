AC_INIT([phys], [0.1])
AC_CONFIG_SRCDIR([src/coord.h])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

AX_CXX_CHECK_FLAG([-std=c++0x],[],[],[CXXFLAGS="$CXXFLAGS -std=c++0x"], 
                  [AC_MSG_ERROR([C++0x support is needed])])
# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_CHECK_FUNCS([floor])

AX_BOOST_BASE
AX_BOOST_PROGRAM_OPTIONS

PKG_CHECK_MODULES([libsdl], [sdl])
AC_CHECK_HEADER([SDL/SDL_gfxPrimitives.h], [], [AC_MSG_ERROR([libSDL_gfx headers are missing])])
AC_CHECK_LIB([SDL_gfx], [filledCircleColor], [LIBSDLGFX_LIBS="-lSDL_gfx"])

AC_SUBST([LIBSDL_CFLAGS], ["$libsdl_CFLAGS"])
AC_SUBST([LIBSDL_LIBS], ["$libsdl_LIBS"])
AC_SUBST([LIBSDLGFX_LIBS])

AC_CHECK_PROGS([ODE_CONFIG], [ode-config], [])
if test -z "$ODE_CONFIG"; then
    AC_MSG_ERROR([ode-config not found])
else
    AC_MSG_CHECKING([checking ODE CFLAGS])
    ODE_CFLAGS=`$ODE_CONFIG --cflags`
    AC_MSG_RESULT([$ODE_CFLAGS])
    AC_MSG_CHECKING([checking ODE libs])
    ODE_LIBS=`$ODE_CONFIG --libs`
    AC_MSG_RESULT([$ODE_LIBS])
fi

AC_SUBST([ODE_CFLAGS])
AC_SUBST([ODE_LIBS])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
