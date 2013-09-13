typedef struct comp_simplelist_t {
	struct comp_simplelist_t *proximo; //!< next entry
	struct comp_tree *filho;	//!< pointer to the son
	
} simple_node;

simple_node* simpleCreatelist();

simple_node* simpleCreateNode();

simple_node* simpleInsert(simple_node* Node, simple_node* List);
