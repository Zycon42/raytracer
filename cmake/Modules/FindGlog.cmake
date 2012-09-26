# - Try to find the Google Glog library
#
#  This module defines the following variables
#
#  GLOG_FOUND - Was Glog found
#  GLOG_INCLUDE_DIRS - the Glog include directories
#  GLOG_LIBRARIES - Link to this
#
#  This module accepts the following variables
#
#  GLOG_ROOT - Can be set to Glog install path or Windows build path
#
#=============================================================================
#  FindGlog.cmake, adapted from FindBullet.cmake which has the following
#  copyright -
#-----------------------------------------------------------------------------
# Copyright 2009 Kitware, Inc.
# Copyright 2009 Philip Lowman <philip@yhbt.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

if (WIN32)
	if (NOT DEFINED GLOG_ROOT)
		set(GLOG_ROOT $ENV{GLOG_ROOT})
	endif (NOT DEFINED GLOG_ROOT)
else (WIN32)
	if (NOT DEFINED GLOG_ROOT)
		set (GLOG_ROOT /usr /usr/local)
	endif (NOT DEFINED GLOG_ROOT)
endif(WIN32)

if(MSVC)
	set(LIB_DEBUG_PATHS ${GLOG_ROOT}/Debug)
	set(LIB_RELEASE_PATHS ${GLOG_ROOT}/Release)
	set(LIB_PATHS ${LIB_DEBUG_PATHS} ${LIB_RELEASE_PATHS})
else(MSVC)
	set (LIB_PATHS ${GLOG_ROOT} ${GLOG_ROOT}/lib)
endif(MSVC)

if(MSVC)
    find_path(GLOG_INCLUDE_DIR NAMES raw_logging.h
        PATHS
		  ${GLOG_ROOT}/src/windows
          ${GLOG_ROOT}/src/windows/glog
		  )
else(MSVC)
	# Linux/OS X builds
    find_path(GLOG_INCLUDE_DIR NAMES raw_logging.h
        PATHS
          ${GLOG_ROOT}/include/glog
		  )
endif(MSVC)

# Find the libraries
if(MSVC)
	# prefer static libs
	
    find_library(GLOG_DEBUG_LIBRARY
		NAMES libglog_static libglog
		PATHS ${LIB_DEBUG_PATHS}
	)
	
	find_library(GLOG_RELEASE_LIBRARY
		NAMES libglog_static libglog
		PATHS ${LIB_RELEASE_PATHS}
	)
	
	set(GLOG_LIBRARIES debug ${GLOG_DEBUG_LIBRARY} optimized ${GLOG_RELEASE_LIBRARY})
else(MSVC)
	# Linux/OS X builds
	find_library(GLOG_LIBRARIES
		NAMES libglog
		PATHS ${LIB_PATHS}
	)
endif(MSVC)

if(MSVC)
    string(REGEX REPLACE "/glog$" "" VAR_WITHOUT ${GLOG_INCLUDE_DIR})
    set(GLOG_INCLUDE_DIRS "${VAR_WITHOUT}")
else(MSVC)
	# Linux/OS X builds
    set(GLOG_INCLUDE_DIRS ${GLOG_INCLUDE_DIR})
endif(MSVC)

# handle the QUIETLY and REQUIRED arguments and set GLOG_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Glog DEFAULT_MSG
    GLOG_INCLUDE_DIRS GLOG_LIBRARIES)
