# -*- Mode:cmake -*-

# $Id$

# find_libs
#    in: list of library names
#   out: list containing absolute path for each lib
FUNCTION(find_libs liblist libpath outlist)
  FOREACH(libname ${liblist})
    FIND_LIBRARY(LIBPATH_${libname} NAMES ${libname} HINTS ${libpath})
    IF(NOT LIBPATH_${libname})
      MESSAGE(SEND_ERROR "Library ${libname} not found.")
    ELSE(NOT LIBPATH_${libname})
      LIST(APPEND loc_outlist ${LIBPATH_${libname}})
    ENDIF(NOT LIBPATH_${libname})
  ENDFOREACH(libname)
  
  # message (STATUS "out list: ${loc_outlist}")
  SET(${outlist} ${loc_outlist} PARENT_SCOPE)
ENDFUNCTION(find_libs)

# generate installation rules
FUNCTION(gen_install_rules target)
  INSTALL(TARGETS ${target}
    RUNTIME DESTINATION usr/bin
    LIBRARY DESTINATION usr/lib
    ARCHIVE DESTINATION usr/lib/static)
ENDFUNCTION(gen_install_rules)

FUNCTION(print_variable_change variable access value current_list_file stack)
  IF("MODIFIED_ACCESS" STREQUAL "${access}")
    MESSAGE(STATUS "${variable}: ${access} ${value}")
  ENDIF()
ENDFUNCTION(print_variable_change)

# $Id$
