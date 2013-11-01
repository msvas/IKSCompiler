#include <stdint.h>

//! Structure that defines a list node
typedef struct comp_program_t {
	struct comp_program_t *next; //!< next entry
	char *instruction;
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

/**
 * Concatenates two lists.
 * @param primeiraLista: pointer to the list that goes first in the new structure.
 * @param segundaLista: pointer to the list that is inserted after the first one.
 * @return pointer to the new list beginning.
 */
comp_program* joinLists(comp_program* primeiraLista, comp_program* segundaLista);

/**
 * Prints all the keys in the list.
 * @param inicioLista: pointer to the first node in the list.
 */
void printList();

<<<<<<< HEAD
void createOutputFile();

=======
>>>>>>> a80b2e786de2553567ba86e4fee484278a5b9869
