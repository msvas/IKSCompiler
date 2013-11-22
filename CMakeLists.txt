CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT(compilador)
FIND_PACKAGE(FLEX REQUIRED)
FIND_PACKAGE(BISON REQUIRED)
FLEX_TARGET(scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
BISON_TARGET(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c VERBOSE parser.output)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${compilador_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${compilador_SOURCE_DIR}/src/)
INCLUDE_DIRECTORIES(${compilador_SOURCE_DIR})
ADD_EXECUTABLE(main
  ${FLEX_scanner_OUTPUTS}
  ${BISON_parser_OUTPUTS}
  src/main.c
  src/gv.c
  src/comp_dict.c
  src/comp_list.c
  src/comp_simplelist.c
  src/comp_tree.c
  src/comp_graph.c
  src/iloc.c
  src/comp_programlist.c
)

#set(build_tests yes)
if(build_tests)
ADD_EXECUTABLE(graph_test
  test/step0/comp_graph_tst.c
  src/comp_graph.c
)
ADD_EXECUTABLE(list_test
  test/step0/comp_list_tst.c
  src/comp_list.c
)
ADD_EXECUTABLE(dict_test
  test/step0/comp_dict_tst.c
  src/comp_dict.c
)
ADD_EXECUTABLE(tree_test
  test/step0/comp_tree_tst.c
  src/comp_tree.c
)
endif(build_tests)

TARGET_LINK_LIBRARIES(main ${FLEX_LIBRARIES})

# Use compiler flags for compiling a debug build (with debug symbols, so we can use gdb)
SET(CMAKE_BUILD_TYPE Debug)

# Additional files to clean during the make clean stage.
SET(addfiles dict_test list_test graph_test visual_tree.png visual_tree.dot ../report ../visual_tree.dot ../visual_tree.png)
SET_DIRECTORY_PROPERTIES(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${addfiles}")

