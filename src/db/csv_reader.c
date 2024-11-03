#include "../../include/db/csv_reader.h"

#include "../../include/lib/file.h"
#include <string.h>

int initCSVReader(CSVReader *reader) {
	reader->text = NULL;
	reader->head = NULL;
	reader->tail = NULL;
	reader->n_rows = 0;
	if(0 != initArena(&reader->p)) {
		return 1;
	}
	reader->delim = ',';
	return 0;
}

int resetCSVReader(CSVReader *reader) {
	reader->text = NULL;
	reader->head = NULL;
	reader->tail = NULL;
	reader->n_rows = 0;
	resetArena(&reader->p);
	// keep delim same
	return 0;
}

int termCSVReader(CSVReader *reader) {
	termArena(&(reader->p));
	return 0;
}

int insertRowAtTail(CSVReader *reader, CSVRow *row) {
	//printf("in insert\n");
	if(reader->tail) {
		//printf("true\n");
		reader->tail->next = row;
		row->prev = reader->tail;
		reader->tail = row;
	}
	else if(!reader->tail) {
		reader->head = row;
		reader->tail = row;
	}
	reader->n_rows++;
	return 0;
}

int insertRowAtHead(CSVReader *reader, CSVRow *row) {
	if(reader->head) {
		reader->head->prev = row;
		row->next = reader->head;
		reader->head = row;
	}
	else if(!reader->head) {
		reader->head = row;
		reader->tail = row;
	}
	reader->n_rows++;
	return 0;
}

CSVRow *getRowAtIndex(CSVReader *reader, size_t index) {
	size_t n = reader->n_rows;
	if(index >= n) {
		return NULL;
	}

	CSVRow *curr = reader->head;
	size_t counter = 0;

	if(index > n / 2) {
		curr = reader->tail;
		counter = n;
		while(counter != index) {
			curr = curr->prev;
			counter--;
		}
		return curr;
	}
	while(counter != index) {
		curr = curr->next;
		counter++;
	}
	return curr;
}

int removeRowAtIndex(CSVReader *reader, size_t index) {
	size_t n = reader->n_rows;
	if(index >= n) {
		return 1;
	}

	CSVRow *curr = reader->head;
	size_t counter = 0;

	if(index > n / 2) {
		curr = reader->tail;
		counter = n;
		while(counter != index) {
			curr = curr->prev;
			counter--;
		}
	}
	else if (index <= n / 2) {
		while(counter != index) {
			curr = curr->next;
			counter++;
		}
	}

	if(curr->prev) {
		curr->prev = curr->next;
	}
	if(curr->next) {
		curr->next = curr->prev;
	}

	reader->n_rows--;
	return 0;
}

int tryCSVRead(CSVReader *reader, const char *filename) {
	reader->text = pReadFile(filename, &(reader->p));
	if(!reader->text) {
		return 1;
	}
/*
	size_t n_rows = 1;
	char *it = reader->text;
	while(*it != '\0') {
		if(*it == '\n') {
			n_rows++;
		}
		it++;
	}
	reader->n_rows = n_rows;
*/
	Arena scratch;
	initArena(&scratch);

	char *start = reader->text;
	char *end = reader->text;

	char *temp_line = NULL;
	CSVRow *temp_row = NULL;

	while(*start != '\0') {
		while(*end != 0x03 && *end != '\r' && *end != '\n' && *end != '\0') {
			end++;
		}
		temp_line = palloc(&scratch, (end - start) + 1);
		memcpy(temp_line, start, end - start);
		temp_line[end - start] = '\0';

		size_t n_tok = 0;
		char delim_str[2] = {reader->delim, '\0'};

		char **split_string = tryStringSplit(temp_line, end - start, delim_str, "\"[", "\"]", &scratch, &n_tok);
		if(!split_string) {
			return 2;
		}
/*
		printf("out of split_string\n");
		if(split_string) {
			printf("%p\n", (void *)split_string);
		}
		printf("%zu ", n_tok);
*/
		temp_row = palloc(&reader->p, sizeof(CSVRow));
		temp_row->cols = palloc(&reader->p, n_tok * sizeof(char *));
		temp_row->n_cols = n_tok;

		for(size_t i = 0; i < n_tok; i++) {
			temp_row->cols[i] = pNewStr(split_string[i], &reader->p); // copy strings from temporary scratch Arena onto CSVReader-specific Arena
			//printf("%s\n", temp_row->cols[i]);
		}
		
		insertRowAtTail(reader, temp_row);
		
		//int ret = insertRowAtTail(reader, temp_row);
		//printRow(temp_row);
		//printf("(%d) insert row %zu\n", ret, reader->n_rows);
		//printf("n_rows: %zu\n", reader->n_rows);

		if(*end == '\0') {
			break;
		}
		while(*end == 0x03 || *end == '\r' || *end == '\n' /*|| *end == ' '*/) {
			end++;
		}
		start = end;
	}

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

void printRow(CSVRow *row) {
	if(!row) {
		printf("None\n");
		return;
	}
	for(size_t i = 0; i < row->n_cols; i++) {
		printf("%s ", row->cols[i]);
		if(i != row->n_cols - 1) {
			printf("| ");
		}
	}
	printf("\n");
}
