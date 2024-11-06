#ifndef CSV_READER_H
#define CSV_READER_H

#include "../lib/m_arena.h"
#include "../lib/string_helper.h"

#include <stddef.h>

typedef struct s_CSVRow {
	char **cols;
	size_t n_cols;
	struct s_CSVRow *prev;
	struct s_CSVRow *next;	
} CSVRow;

typedef struct s_CSVReader {
	char *text;
	CSVRow *head;
	CSVRow *tail;
	size_t n_rows;
	Arena p;
	char delim;
} CSVReader;

int initCSVReader(CSVReader *reader);
int resetCSVReader(CSVReader *reader);
int termCSVReader(CSVReader *reader);
int insertCSVRowAtTail(CSVReader *reader, CSVRow *row);
int insertCSVRowAtHead(CSVReader *reader, CSVRow *row);
CSVRow *getCSVRowAtIndex(CSVReader *reader, size_t index);
int removeCSVRowAtIndex(CSVReader *reader, size_t index);
int tryCSVRead(CSVReader *reader, const char *filename);
int setCSVDelim(CSVReader *reader, char delim);
void printCSVRow(CSVRow *row);

#endif // CSV_READER_H
