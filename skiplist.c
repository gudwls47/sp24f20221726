#include "kvs.h"

node_t* createNode(int level, const char *key, const char *value) {
	node_t *n = (node_t*) malloc(sizeof(node_t));
	strcpy(n->key, key);
	n->value = strdup(value);
	n->forward = (node_t**) malloc(sizeof(node_t*) * (level + 1));
	for (int i = 0; i <= level; i++) {
		n->forward[i] = NULL;
	}
	return n;
}

skiplist_t* createSkiplist() {
	skiplist_t* list = (skiplist_t*)malloc(sizeof(skiplist_t));
	if (!list) return NULL;
	list->header = createNode(MAX_LEVEL, "", "");
	list->level = 0;
	list->items = 0;
	return list;
}
