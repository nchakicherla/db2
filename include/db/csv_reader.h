#ifndef CSV_READER_H
#define CSV_READER_H

#include "../lib/m_arena.h"
#include <stddef.h>

typedef struct s_CSVRow {
	char **cols;
	size_t n_cols;
} CSVRow;

typedef struct s_CSVReader {
	char *text;
	CSVRow *rows;
	size_t n_rows;
	Arena p;
	char delim;
} CSVReader;

int initCSVReader(CSVReader *reader);

int termCSVReader(CSVReader *reader);

int tryCSVRead(CSVReader *reader, const char *filename);



#endif // CSV_READER_H