# additional include paths necessary to compile the C++ library
AM_CXXFLAGS = -I$(top_srcdir)/


extra_sources=
if BUILD_COMMS_MPI
  extra_sources+=Grid_communicator_mpi.cc
  extra_sources+=Grid_stencil_common.cc
endif
if BUILD_COMMS_NONE
  extra_sources+=Grid_communicator_fake.cc
  extra_sources+=Grid_stencil_common.cc
endif

#
# Libraries
#
lib_LIBRARIES = libGrid.a
libGrid_a_SOURCES = Grid_init.cc $(extra_sources)

#
# Include files
#
include_HEADERS = Grid_config.h\
	Grid.h\
	Grid_simd.h\
	Grid_vComplexD.h\
	Grid_vComplexF.h\
	Grid_vRealD.h\
	Grid_vRealF.h\
	Grid_Cartesian.h\
	Grid_Lattice.h\
	Grid_Communicator.h\
	Grid_QCD.h\
	Grid_aligned_allocator.h\
	Grid_cshift.h\
	Grid_cshift_common.h\
	Grid_cshift_mpi.h\
	Grid_cshift_none.h\
	Grid_stencil.h\
	Grid_math_types.h


