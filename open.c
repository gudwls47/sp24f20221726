#include "kvs.h"


kvs_t* open()
{
	kvs_t* kvs = (kvs_t*) malloc (sizeof(kvs_t));

	if(!kvs) {
		printf("Failed to allocate memory for kvs\n");
		return NULL;
	}

	kvs->list = createSkiplist();
	if (!kvs->list) {
		free(kvs);
		printf("Failed to create skiplist\n");
		return NULL;
	}

	printf("Open: kvs initialized with an empty skiplist\n");

	return kvs;
}
