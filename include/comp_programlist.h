#include <stdint.h>

//! Structure that defines a list node
typedef struct comp_program_t {
	struct comp_program_t *next; //!< next entry
	char *instruction;
	int lider;
	struct comp_program_t *previous; //!< previous entry
} comp_program;

/**
 * Creates a list.
 * @return a pointer to the list.
 */
comp_program* createList(void);

/**
 * Creates a list node.
 * @param chave: node key.
 * @return pointer to the node created.
 */
comp_program* createNode(char *instruction);

comp_program* insertNodeExternal(char *instruction, comp_program* list);

/**
 * Insert the node into the list.
 * @param novoNodo: pointer to the inserted node.
 * @param inicioLista: pointer to the first node in the list.
 * @return pointer to the first node in the list.
 */
comp_program* insertNode(char *instruction);

/**
 * Excludes the node from the list.
 * @param nodoExcluido: pointer to the deleted node.
 * @param inicioLista: pointer to the first node in the list.
 * @return pointer to the list beginning.
 */
comp_program* deleteNode(comp_program* nodoExcluido);

comp_program* getNode();

/**
 * Concatenates two lists.
 * @param primeiraLista: pointer to the list that goes first in the new structure.
 * @param segundaLista: pointer to the list that is inserted after the first one.
 * @return pointer to the new list beginning.
 */
comp_program* joinLists(comp_program* primeiraLista, comp_program* segundaLista);

void printListExternal(comp_program* list);

/**
 * Prints all the keys in the list.
 * @param inicioLista: pointer to the first node in the list.
 */
void printList();

void createOutputFile();

comp_program *getLista();

void *saveList(comp_program *list);

