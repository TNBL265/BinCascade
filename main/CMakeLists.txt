# Embed CA, certificate & key directly into binary
set(COMPONENT_ADD_INCLUDEDIRS
	"."
	"${CMAKE_CURRENT_LIST_DIR}"
	)

idf_component_register(SRCS "main.c" "aws.c"
                       INCLUDE_DIRS ${COMPONENT_ADD_INCLUDEDIRS}
                      )