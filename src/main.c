#include <stdio.h>

#include "../include/lib/m_arena.h"
#include "../include/lib/table.h"

#include "../include/db/db.h"
#include "../include/db/csv_reader.h"

int main(void) {

	CSVReader reader;
	initCSVReader(&reader);

	printf("(%d) try csv read\n", tryCSVRead(&reader, "./resources/csv/ttc_dataset.csv"));

	size_t counter = 1;
	for (size_t i = 100; i < 110; i++) {
		//printf("(%p) get row at %zu\n", (void *)getRowAtIndex(&reader, i), i);
		//printf("(%d) remove row at %zu\n", removeRowAtIndex(&reader, i), i);
		counter++;
	}

	termCSVReader(&reader);
	return 0;
}
