
# Just the File name

#GET_FILENAME_COMPONENT(FBLIB_FILE_WO_PATH ${FBLIB_FILE} NAME_WE)
STRING(REGEX REPLACE  ".*/" "" FBLIB_FILE_WO_PATH ${FBLIB_FILE})
STRING(REGEX REPLACE  "\\.cpp" ".h" FBLIB_FILE_WO_PATH_H ${FBLIB_FILE_WO_PATH})
STRING(REGEX REPLACE  "\\." "_gen." FBLIB_FILE_NAME ${FBLIB_FILE_WO_PATH})

STRING(REGEX MATCH  ".*stringlist\\.(cpp|h).*" REGEX_STRINGS ${FBLIB_FILE})
IF(NOT REGEX_STRINGS)
STRING(REGEX MATCH  ".*forteinit\\.(cpp|h).*" REGEX_STRINGS ${FBLIB_FILE})
ENDIF(NOT REGEX_STRINGS)
IF(NOT REGEX_STRINGS)
	FILE(READ ${FBLIB_FILE} FILE_STRING)
	STRING(REGEX MATCHALL  "g_nStringId([A-Za-z0-9_]*)" REGEX_STRINGS ${FILE_STRING})
	STRING(REGEX MATCHALL  "g_nStringId([0-9][A-Za-z0-9_]*)" REGEX_STRINGS_ERROR ${FILE_STRING})

	
	# Remove already defined externals, those will be generated #defines in the sourcecode
	STRING(REGEX MATCHALL  "(DEFINE_GENERIC_FIRMWARE_FB|DEFINE_FIRMWARE_DATATYPE)[(]([A-Za-z0-9_]*)" REGEX_STRINGS_CODE_DEFINED ${FILE_STRING})
	IF(REGEX_STRINGS_CODE_DEFINED)
		STRING(REGEX REPLACE "(DEFINE_GENERIC_FIRMWARE_FB|DEFINE_FIRMWARE_DATATYPE)[(]" "" REGEX_STRINGS_CODE_DEFINED ${REGEX_STRINGS_CODE_DEFINED})
	ENDIF(REGEX_STRINGS_CODE_DEFINED)
	
	# remove template connections
	# Do not pars stringlist, as these files will be generated
	STRING(REGEX MATCH  "conn\\.h" REGEX_TEMPLATE ${FBLIB_FILE_WO_PATH})
	IF(NOT REGEX_TEMPLATE)
		IF(FORTE_MODIFY_SOURCES_ON_MISSING_GENERATED_INCLUDES)
			## CConnection::genConPortIdTemplate to GENERATE_CONNECTION_PORT_ID_2_ARG
			STRING(REGEX MATCHALL  "CConnection::genConPortIdTemplate<([A-Za-z0-9_,\t ]*)>::value" REGEX_TO_REPLACE "${FILE_STRING}")
			IF(REGEX_TO_REPLACE)
				FOREACH(ELEMENT ${REGEX_TO_REPLACE})
					MESSAGE("${ELEMENT}")
					STRING(REPLACE "CConnection::genConPortIdTemplate<" "GENERATE_CONNECTION_PORT_ID_2_ARG(" NEW_ELEMENT "${ELEMENT}")
					STRING(REPLACE ">::value" ")" NEW_ELEMENT "${NEW_ELEMENT}")
					MESSAGE("${NEW_ELEMENT}")
					STRING(REPLACE "${ELEMENT}" "${NEW_ELEMENT}" FILE_STRING "${FILE_STRING}")
					FILE(WRITE ${FBLIB_FILE} "${FILE_STRING}")
				ENDFOREACH(ELEMENT)
			ENDIF(REGEX_TO_REPLACE)
			## CConnection::genConPortIdSingleTemplate to GENERATE_CONNECTION_PORT_ID_2_ARG
			STRING(REGEX MATCHALL  "CConnection::genConPortIdSingleTemplate<([A-Za-z0-9_\t ]*)>::value" REGEX_TO_REPLACE "${FILE_STRING}")
			IF(REGEX_TO_REPLACE)
				FOREACH(ELEMENT ${REGEX_TO_REPLACE})
					MESSAGE("${ELEMENT}")
					STRING(REPLACE "CConnection::genConPortIdSingleTemplate<" "GENERATE_CONNECTION_PORT_ID_1_ARG(" NEW_ELEMENT "${ELEMENT}")
					STRING(REPLACE ">::value" ")" NEW_ELEMENT "${NEW_ELEMENT}")
					MESSAGE("${NEW_ELEMENT}")
					STRING(REPLACE "${ELEMENT}" "${NEW_ELEMENT}" FILE_STRING "${FILE_STRING}")
					FILE(WRITE ${FBLIB_FILE} "${FILE_STRING}")
				ENDFOREACH(ELEMENT)
			ENDIF(REGEX_TO_REPLACE)
		ENDIF(FORTE_MODIFY_SOURCES_ON_MISSING_GENERATED_INCLUDES)
	ENDIF(NOT REGEX_TEMPLATE)
	
	list(REMOVE_DUPLICATES REGEX_STRINGS)
	list(REMOVE_ITEM REGEX_STRINGS "g_nStringId${REGEX_STRINGS_CODE_DEFINED}")
	# Sanity check for old files
	STRING(REGEX MATCHALL  "#include \"${FBLIB_FILE_NAME}\"" REGEX_STRINGS_MISSING_INCLUDE ${FILE_STRING})
	IF(REGEX_STRINGS)
	IF(NOT REGEX_STRINGS_MISSING_INCLUDE)
		IF(FORTE_MODIFY_SOURCES_ON_MISSING_GENERATED_INCLUDES)
			MESSAGE(WARNING "${FBLIB_FILE}: Missing include statement.  #include \"${FBLIB_FILE_NAME}\". Will be autogenerated")
			MESSAGE("${FBLIB_FILE_WO_PATH_H}")
			STRING(REGEX REPLACE  "#include \"${FBLIB_FILE_WO_PATH_H}\"" "#include \"${FBLIB_FILE_WO_PATH_H}\"\n#ifdef FORTE_ENABLE_GENERATED_SOURCE_CPP\n#include \"${FBLIB_FILE_NAME}\"\n#endif" FILE_STRING "${FILE_STRING}")
			FILE(WRITE ${FBLIB_FILE} "${FILE_STRING}")
		ELSE(FORTE_MODIFY_SOURCES_ON_MISSING_GENERATED_INCLUDES)
			MESSAGE(FATAL_ERROR "${FBLIB_FILE}: Missing include statement, add: #include \"${FBLIB_FILE_NAME}\". Not generating stringdict-externals file")
			RETURN()
		ENDIF(FORTE_MODIFY_SOURCES_ON_MISSING_GENERATED_INCLUDES)
	ENDIF(NOT REGEX_STRINGS_MISSING_INCLUDE)
	ENDIF(REGEX_STRINGS)

	SET(scm_acLocalConstStringBuf "")
	FOREACH(STR ${REGEX_STRINGS})
	  string(LENGTH ${STR} len)
	  math(EXPR len ${len}-11)
	  string(SUBSTRING ${STR} 11 ${len} OUTSTR)
	  list(APPEND scm_acLocalConstStringBuf ${OUTSTR})
	ENDFOREACH(STR)
	
	SET(${FBLIB_FILE}_externals "")
	list(SORT scm_acLocalConstStringBuf)
	list(REMOVE_DUPLICATES scm_acLocalConstStringBuf)
	FOREACH(STR IN LISTS scm_acLocalConstStringBuf)
		set(${FBLIB_FILE}_externals "${${FBLIB_FILE}_externals} extern const CStringDictionary::TStringId g_nStringId${STR};\n")
	ENDFOREACH(STR)
	
	#IF(NOT (${FBLIB_FILE}_externals STREQUAL ""))
		#create generated file
		CONFIGURE_FILE(${FORTE_SOURCE_DIR}/gen_include.cpp.in ${FORTE_BINARY_DIR}/${FBLIB_FILE_NAME}_new)
		# only copy files if different
		execute_process( COMMAND ${CMAKE_COMMAND} -E copy_if_different ${FORTE_BINARY_DIR}/${FBLIB_FILE_NAME}_new ${FORTE_BINARY_DIR}/${FBLIB_FILE_NAME} OUTPUT_QUIET ERROR_QUIET )
		file(REMOVE ${FORTE_BINARY_DIR}/${FBLIB_FILE_NAME}_new)
	#ENDIF(NOT (${FBLIB_FILE}_externals STREQUAL ""))

ENDIF(NOT REGEX_STRINGS)