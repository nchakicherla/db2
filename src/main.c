#include <stdio.h>

#include "common.h"
#include "./lib/mempool.h"

int main(void) {

	printf("hello, db2\n");

	MemPool p;
	initMemPool(&p);

	int *ptr = palloc(&p, sizeof(int));
	*ptr = 1;
	printf("%d\n", *ptr);

	termMemPool(&p);
	return 0;
}
