#                         -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# Project Grid package  
# 
# Time-stamp: <2015-05-26 17:18:54 neo>

AC_PREREQ([2.63])
AC_INIT([Grid], [1.0], [paboyle@ph.ed.ac.uk])
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE(subdir-objects)
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([lib/Grid.h])
AC_CONFIG_HEADERS([lib/Grid_config.h])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_MSG_NOTICE([

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
Configuring $PACKAGE v$VERSION  for $host
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
])

# Checks for programs.
AC_LANG(C++)
AC_PROG_CXX
AC_OPENMP
AC_PROG_RANLIB
AX_CXX_COMPILE_STDCXX_11(noext, mandatory)


# Checks for libraries.
#AX_GCC_VAR_ATTRIBUTE(aligned)

# Checks for header files.
AC_CHECK_HEADERS(stdint.h)
AC_CHECK_HEADERS(mm_malloc.h)
AC_CHECK_HEADERS(malloc/malloc.h)
AC_CHECK_HEADERS(malloc.h)
AC_CHECK_HEADERS(endian.h)
AC_CHECK_HEADERS(gmp.h)
AC_CHECK_DECLS([ntohll],[], [], [[#include <arpa/inet.h>]])
AC_CHECK_DECLS([be64toh],[], [], [[#include <arpa/inet.h>]])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
echo
echo Checking libraries 
echo :::::::::::::::::::::::::::::::::::::::::::


AC_CHECK_FUNCS([gettimeofday])

AC_CHECK_LIB([gmp],[__gmpf_init],,
        [AC_MSG_ERROR(GNU Multiple Precision GMP library was not found in your system.
Please install or provide the correct path to your installation
Info at: http://www.gmplib.org)])

AC_CHECK_LIB([mpfr],[mpfr_init],,
        [AC_MSG_ERROR(GNU Multiple Precision MPFR library was not found in your system.
Please install or provide the correct path to your installation
Info at: http://www.mpfr.org/)])





AC_ARG_ENABLE([simd],[AC_HELP_STRING([--enable-simd=SSE|AVX|AVX2|AVX512|MIC],\
	[Select instructions to be SSE4.0, AVX 1.0, AVX 2.0+FMA, AVX 512, MIC])],\
	[ac_SIMD=${enable_simd}],[ac_SIMD=AVX2])

case ${ac_SIMD} in
     SSE4)
       echo Configuring for SSE4
       AC_DEFINE([SSE4],[1],[SSE4] )
     ;;
     AVX)
       echo Configuring for AVX
       AC_DEFINE([AVX1],[1],[AVX] )
     ;;
     AVX2)
       echo Configuring for AVX2
       AC_DEFINE([AVX2],[1],[AVX2] )
     ;;
     AVX512|MIC)
       echo Configuring for AVX512 and MIC
       AC_DEFINE([AVX512],[1],[AVX512] )
     ;;
     *)
     AC_MSG_ERROR([${ac_SIMD} unsupported --enable-simd option]); 
     ;;
esac


AC_ARG_ENABLE([comms],[AC_HELP_STRING([--enable-comms=none|mpi],[Select communications])],[ac_COMMS=${enable_comms}],[ac_COMMS=none])

case ${ac_COMMS} in
     none)
       echo Configuring for NO communications
       AC_DEFINE([GRID_COMMS_NONE],[1],[GRID_COMMS_NONE] )
     ;;
     mpi)
       echo Configuring for MPI communications
       AC_DEFINE([GRID_COMMS_MPI],[1],[GRID_COMMS_MPI] )
     ;;
     *)
     AC_MSG_ERROR([${ac_COMMS} unsupported --enable-comms option]); 
     ;;
esac

AM_CONDITIONAL(BUILD_COMMS_MPI,[ test "X${ac_COMMS}X" == "XmpiX" ])
AM_CONDITIONAL(BUILD_COMMS_NONE,[ test "X${ac_COMMS}X" == "XnoneX" ])


###################################################################
# Checks for doxygen support
# if present enables the "make doxyfile" command
echo
echo Checking doxygen support 
echo :::::::::::::::::::::::::::::::::::::::::::
AC_PROG_DOXYGEN

if test -n "$DOXYGEN"
then
AC_CONFIG_FILES([docs/doxy.cfg])
fi


AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(lib/Makefile)
AC_CONFIG_FILES(tests/Makefile)
AC_CONFIG_FILES(benchmarks/Makefile)
AC_OUTPUT


echo "
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Summary of configuration for $PACKAGE v$VERSION
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following features are enabled:

- architecture (build)          : $build_cpu
- os (build)                    : $build_os
- architecture (target)         : $target_cpu
- os (target)                   : $target_os
- build DOXYGEN documentation   : `if test "x$enable_doc" = xyes; then echo yes; else echo no; fi`
- graphs and diagrams           : `if test "x$enable_dot" = xyes; then echo yes; else echo no; fi`

----------------------------------------------------------
- enabled simd support          : ${ac_SIMD}
- communications type           : ${ac_COMMS}


"
