#/home/cdl/Programs/visit_thirdparty/3.2.1/cmake/3.14.7/linux-x86_64_gcc-7.5/bin/cmake
##
## src/tools/dev/scripts/build_visit generated host.cmake
## created: Thu Oct 28 11:15:27 EDT 2021
## system: Linux whitney 5.4.0-89-generic #100~18.04.1-Ubuntu SMP Wed Sep 29 10:59:42 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux
## by: cdl

##
## Setup VISITHOME & VISITARCH variables.
##
SET(VISITHOME /home/cdl/Programs/visit_thirdparty/3.2.1)
SET(VISITARCH linux-x86_64_gcc-7.5)

## Compiler flags.
##
VISIT_OPTION_DEFAULT(VISIT_C_COMPILER gcc TYPE FILEPATH)
VISIT_OPTION_DEFAULT(VISIT_CXX_COMPILER g++ TYPE FILEPATH)
VISIT_OPTION_DEFAULT(VISIT_FORTRAN_COMPILER no TYPE FILEPATH)
VISIT_OPTION_DEFAULT(VISIT_C_FLAGS " -m64 -fPIC -fvisibility=hidden" TYPE STRING)
VISIT_OPTION_DEFAULT(VISIT_CXX_FLAGS " -m64 -fPIC -fvisibility=hidden" TYPE STRING)

##
## VisIt install location.
##
VISIT_OPTION_DEFAULT(CMAKE_INSTALL_PREFIX /home/cdl/Programs/visit TYPE FILEPATH)

##
## Parallel Build Setup.
##
VISIT_OPTION_DEFAULT(VISIT_PARALLEL ON TYPE BOOL)
## (configured w/ mpi compiler wrapper)
VISIT_OPTION_DEFAULT(VISIT_MPI_COMPILER /usr/bin/mpicxx TYPE FILEPATH)

##
## VisIt Thread Option
##
VISIT_OPTION_DEFAULT(VISIT_THREAD OFF TYPE BOOL)

##############################################################
##
## Database reader plugin support libraries
##
## The HDF5 and NetCDF libraries must be first so that
## their libdeps are defined for any plugins that need them.
##
## For libraries with LIBDEP settings, order matters.
## Libraries with LIBDEP settings that depend on other
## Library's LIBDEP settings must come after them.
##############################################################
##

##
## ZLIB
##
SETUP_APP_VERSION(ZLIB 1.2.11)
VISIT_OPTION_DEFAULT(VISIT_ZLIB_DIR ${VISITHOME}/zlib/${ZLIB_VERSION}/${VISITARCH})

##
## OPENSSL 
##
VISIT_OPTION_DEFAULT(VISIT_OPENSSL_DIR ${VISITHOME}/openssl/1.0.2j/${VISITARCH})

##
## Python
##
VISIT_OPTION_DEFAULT(PYTHON_EXECUTABLE /usr/bin/python3)
VISIT_OPTION_DEFAULT(VISIT_PYTHON_DIR /usr)
VISIT_OPTION_DEFAULT(PYTHON_INCLUDE_PATH /usr/include/python3.6m )
VISIT_OPTION_DEFAULT(PYTHON_LIBRARY /usr/lib/x86_64-linux-gnu/libpython3.6m.so)
VISIT_OPTION_DEFAULT(PYTHON_LIBRARY_DIR /usr/lib/x86_64-linux-gnu)
VISIT_OPTION_DEFAULT(PYTHON_VERSION 3.6)
SET(VISIT_PYTHON_SKIP_INSTALL ON)

##
## Qt
##
SETUP_APP_VERSION(QT 5.14.2)
VISIT_OPTION_DEFAULT(VISIT_QT_DIR ${VISITHOME}/qt/${QT_VERSION}/${VISITARCH})

##
## QWT
##
SETUP_APP_VERSION(QWT 6.1.2)
VISIT_OPTION_DEFAULT(VISIT_QWT_DIR ${VISITHOME}/qwt/${QWT_VERSION}/${VISITARCH})

##
## VTK
##
SETUP_APP_VERSION(VTK 8.1.0)
VISIT_OPTION_DEFAULT(VISIT_VTK_DIR ${VISITHOME}/vtk/${VTK_VERSION}/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_VTK_INCDEP ZLIB_INCLUDE_DIR)
VISIT_OPTION_DEFAULT(VISIT_VTK_LIBDEP ZLIB_LIBRARY)

##
## HDF5
##
VISIT_OPTION_DEFAULT(VISIT_HDF5_DIR ${VISITHOME}/hdf5/1.8.14/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_HDF5_LIBDEP  ${VISITHOME}/zlib/${ZLIB_VERSION}/${VISITARCH}/lib z TYPE STRING)

##
## ADIOS2
##
SETUP_APP_VERSION(ADIOS2 2.5.0)
VISIT_OPTION_DEFAULT(VISIT_ADIOS2_DIR ${VISITHOME}/adios2-ser/${ADIOS2_VERSION}/${VISITARCH})
## (configured w/ mpi compiler wrapper)
VISIT_OPTION_DEFAULT(VISIT_ADIOS2_PAR_DIR ${VISITHOME}/adios2-par/${ADIOS2_VERSION}/${VISITARCH})

##
## Conduit
##
SETUP_APP_VERSION(CONDUIT v0.8.0)
VISIT_OPTION_DEFAULT(VISIT_CONDUIT_DIR ${VISITHOME}/conduit/v0.8.0/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_CONDUIT_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} TYPE STRING)

##
## FMS 
##
VISIT_OPTION_DEFAULT(VISIT_FMS_DIR ${VISITHOME}/fms/100/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_FMS_LIBDEP CONDUIT_LIBRARY_DIR conduit CONDUIT_LIBRARY_DIR conduit_blueprint CONDUIT_LIBRARY_DIR conduit_relay ${VISIT_CONDUIT_LIBDEP} TYPE STRING)

##
## IceT
##
VISIT_OPTION_DEFAULT(VISIT_ICET_DIR ${VISITHOME}/icet/77c708f9090236b576669b74c53e9f105eedbd7e/${VISITARCH})

##
## MFEM 
##
VISIT_OPTION_DEFAULT(VISIT_MFEM_DIR ${VISITHOME}/mfem/Add_FMS_support/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_MFEM_INCDEP CONDUIT_INCLUDE_DIR FMS_INCLUDE_DIR TYPE STRING)
VISIT_OPTION_DEFAULT(VISIT_MFEM_LIBDEP ${VISIT_CONDUIT_LIBDEP} ${VISITHOME}/zlib/${ZLIB_VERSION}/${VISITARCH}/lib z TYPE STRING)

##
## Silo
##
VISIT_OPTION_DEFAULT(VISIT_SILO_DIR ${VISITHOME}/silo/4.10.2/${VISITARCH})
VISIT_OPTION_DEFAULT(VISIT_SILO_LIBDEP HDF5_LIBRARY_DIR hdf5 ${VISIT_HDF5_LIBDEP} ZLIB_LIBRARY_DIR z TYPE STRING)

