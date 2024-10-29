#include "kvs.h"
#include <stdio.h>
#include <stdlib.h>

int close(kvs_t* kvs)
{
	/* do program */

	if (kvs == NULL) return -1;
	node_t *current = kvs->list->header;
	while (current) {
		node_t *next = current->forward[0];
		free(current->value);
		current->value = NULL;
		free(current->forward);
		free(current); 
		current = next;
	}
	free(kvs);
	kvs = NULL;
	return 0;
}
