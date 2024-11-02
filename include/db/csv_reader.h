#ifndef CSV_READER_H
#define CSV_READER_H

#include "../lib/mempool.h"
#include <stddef.h>

typedef struct s_CSVReader {
	char *text;
	size_t n_rows;
	MemPool *pool;
} CSVReader;

#endif // CSV_READER_H