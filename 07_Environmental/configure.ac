#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0], [nowhere@mail.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([Rhash is needed])])

# Checks for header files.
AC_CHECK_HEADER([rhash.h])
# AC_CHECK_HEADER([readline/readline.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_ARG_ENABLE([readline],
  [AS_HELP_STRING([--enable-readline],
    [enable support for readline])],
  [enbale_readline=yes],
  [])
 
  
AS_IF([test "x$enable_readline" = "xyes"],
  [
    AC_CHECK_LIB([readline], [readline], [], [AC_MSG_ERROR([Trying to use readline which is not present])])
    AC_CHECK_HEADERS([readline/readline.h])
    AC_DEFINE(READLINE,[],[try to use readline])
  ])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
