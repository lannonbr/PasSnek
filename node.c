#include "node.h"
#include "tree.h"
#include "statement.h"
#include <stdlib.h>
#include <string.h>
#include "pascal.tab.h"

node_t *make_node(int type, char* name) {
	node_t * newNode = (node_t *) malloc(sizeof(node_t));

	newNode->type = type;
	newNode->name = name;

	return newNode;
}

// Add a node to the front of a node_list
node_t *insert_node(node_t * head, int type, char* name, int offset) {
	node_t * node = make_node(type, name);
	node->next = head;
	node->offset = offset;
	return node;
}

// Search a node list for a node with a particular string
node_t *search_node(node_t * head, char* name) {
	node_t* node = head;

	while(node != NULL) {
		if(!strcmp(node->name, name)) {
			return node;
		}
		node = node->next;
	}

	return NULL;
}

void free_node(node_t *node) {
	if(node == NULL)
		return;

	free(node);
}
