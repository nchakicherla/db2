#include "../../include/db/csv_reader.h"

#include "../../include/lib/file.h"
#include <string.h>

int initCSVReader(CSVReader *reader) {
	reader->text = NULL;
	reader->n_rows = 0;
	if(0 != initArena(&(reader->p))) {
		return 1;
	}
	reader->delim = ',';
	return 0;
}

int termCSVReader(CSVReader *reader) {
	termArena(&(reader->p));
	return 0;
}

int tryCSVRead(CSVReader *reader, const char *filename) {
	reader->text = pReadFile(filename, &(reader->p));
	if(!reader->text) {
		return 1;
	}

	printf("len: %zu\n", strlen(reader->text));
	return 0;
}