CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT(compilador)
FIND_PACKAGE(FLEX REQUIRED)
FIND_PACKAGE(BISON REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${compilador_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${compilador_SOURCE_DIR}/src/)
INCLUDE_DIRECTORIES(${compilador_SOURCE_DIR})
BISON_TARGET(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
FLEX_TARGET(scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)
ADD_EXECUTABLE(main
  ${FLEX_scanner_OUTPUTS}
  ${BISON_parser_OUTPUTS}
  src/main.c
  src/comp_dict.c
  src/comp_list.c
  src/comp_tree.c
  src/comp_graph.c
  src/symbol_table.c
)
#ADD_EXECUTABLE(graph_test
#  test/comp_graph_tst.c
#  src/comp_graph.c
#)
#ADD_EXECUTABLE(list_test
#  test/comp_list_tst.c
#  src/comp_list.c
#)
#ADD_EXECUTABLE(dict_test
#  test/comp_dict_tst.c
#  src/comp_dict.c
#  src/symbol_table.c
#)
#ADD_EXECUTABLE(tree_test
#  test/comp_tree_tst.c
#  src/comp_tree.c
#)
TARGET_LINK_LIBRARIES(main ${FLEX_LIBRARIES})

# Use compiler flags for compiling a debug build (with debug symbols, so we can use gdb)
#SET(CMAKE_BUILD_TYPE Debug)

