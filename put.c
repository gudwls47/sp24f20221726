#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int put(kvs_t* kvs, const char* key, const char* value)
{
	//printf("put: %s, %s\n", key, value);
	/* do program here */

	node_t *current = kvs->list->header;
	node_t *update[MAX_LEVEL + 1];
	memset(update, 0, sizeof(node_t*) * (MAX_LEVEL + 1));

	for (int i = kvs->list->level; i >= 0; i--) {
		while (current->forward[i] != NULL && strcmp(current->forward[i]->key, key) < 0) {
			current = current->forward[i];
		}
		update[i] = current;
	}
	current = current->forward[0];

	if (current != NULL && strcmp(current->key, key) == 0) {
		free(current->value);
		current->value = strdup(value);
		return 1;
	}

	int lvl = rand() % (MAX_LEVEL + 1);
	if (lvl > kvs->list->level) {
		for (int i = kvs->list->level + 1; i <= lvl; i++) {
			update[i] = kvs->list->header;
		}
		kvs->list->level = lvl;
	}

	node_t *newnode = createNode(lvl, key, value);
	for (int i = 0; i <= lvl; i++) {
		newnode->forward[i] = update[i]->forward[i];
		update[i]->forward[i] = newnode;
	}
	return 0;
}
