#############################################################################
# Core
#############################################################################
forte_add_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

forte_add_subdirectory(cominfra)
forte_add_subdirectory(datatypes)
forte_add_subdirectory(utils)

forte_add_sourcefile_hcpp(conn  dataconn  eventconn)     

forte_add_sourcefile_h   (esfb.h      event.h    mgmcmd.h      fortenode.h fortelist.h convert_functions.h)
forte_add_sourcefile_hcpp(basicfb     cfb        device      devexec )
forte_add_sourcefile_hcpp(extevhan   funcbloc      fbcontainer  if2indco )
forte_add_sourcefile_hcpp(resource    stringdict typelib       ecet)
forte_add_sourcefile_hcpp(adapterconn adapter    iec61131_functions)

if(FORTE_SUPPORT_MONITORING)
  forte_add_sourcefile_hcpp(monitoring)
endif(FORTE_SUPPORT_MONITORING)


