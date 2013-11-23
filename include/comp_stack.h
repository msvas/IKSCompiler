/*
 * \authors Marcelo Vasques 
 * @file   comp_stack.h
 * @brief  Stack structures and manipulation functions prototypes.
 */

#include "comp_tree.h"

typedef struct comp_stack_node_t {
	struct comp_stack_node_t *next;
	ACTREG aR;
	struct comp_stack_node_t *previous;
} comp_stack_node;

comp_stack_node* createStack();

comp_stack_node* newStackNode(ACTREG functReg);

comp_stack_node* pushStackNode(comp_stack_node* framePointer, comp_stack_node* stackPointer, ACTREG functReg);

comp_stack_node* popStackNode(comp_stack_node* framePointer, comp_stack_node* stackPointer);
