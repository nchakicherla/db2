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
	//printf("len: %zu\n", strlen(reader->text));
	size_t n_rows = 1;
	char *it = reader->text;
	while(*it != '\0') {
		if(*it == '\n') {
			n_rows++;
		}
		it++;
	}
	reader->n_rows = n_rows;
	//printf("n_rows: %zu\n", reader->n_rows);

	Arena scratch;
	initArena(&scratch);

	char *start = reader->text;
	char *end = reader->text;

	char *temp_line = NULL;

	while(*start != '\0') {
		while(*end != '\n' && *end != '\0') {
			end++;
		}
		printf("line len: %zu\n", end - start);
		temp_line = palloc(&scratch, (end - start) + 1);
		memcpy(temp_line, start, (end - start));
		temp_line[end - start] = '\0';

		printf("CURRENT LINE: %s\n\n", temp_line);

		if(*end == '\0') {
			break;
		}
		end++;
		start = end;
	}
	printf("\n");

	termArena(&scratch);

	return 0;
}



int setDelim(CSVReader *reader, char delim) {
	if(delim != ',' && delim != ';') {
		return 1;
	}
	reader->delim = delim;
	return 0;
}
