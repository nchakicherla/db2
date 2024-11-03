#ifndef MEMPOOL_H
#define MEMPOOL_H

#include <stdlib.h>
#include <string.h>

struct s_Block;

typedef struct s_Arena {
	size_t bytes_used;
	size_t bytes_allocd;

	void *next_free;
	size_t next_free_size;
	size_t last_block_size;
	struct s_Block *last_block;
	struct s_Block *first_block;
} Arena;

typedef struct s_Block {
	void *data;
	size_t data_size;
	struct s_Block *next;
} Block;

int initArena(Arena *pool);
int resetArena(Arena *pool);
int termArena(Arena *pool);
void *palloc(Arena *pool, size_t size);
void *pzalloc(Arena *pool, size_t size);
void *pGrowAlloc(void *ptr, size_t old_size, size_t new_size, Arena *pool);
char *pNewStr(char *str, Arena *pool);
size_t getBytesUsed(Arena *pool);
size_t getBytesAllocd(Arena *pool);
void printPoolInfo(Arena *pool);

#endif // MEMPOOL_H
