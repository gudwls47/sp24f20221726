#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get(kvs_t* kvs, const char* key)
{
	/* do program here */

	if (key == NULL) {
		fprintf(stderr, "Error: Key is NULL\n");
		return NULL;
	}

	if (kvs == NULL || kvs->list == NULL || kvs->list->header == NULL) {
		fprintf(stderr, "Error: Skiplist is not initialized properly\n");
		return NULL;
	}

	node_t *current = kvs->list->header;
	for (int i = kvs->list->level; i >= 0; i--) {
		while (current->forward[i] != NULL && strcmp(current->forward[i]->key, key) < 0) {
			current = current->forward[i];
		}
	}
	current = current->forward[0];

	if (current != NULL && strcmp(current->key, key) == 0) {
		return current->value;
	}

	return NULL;
	
}
