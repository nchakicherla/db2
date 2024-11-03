#include <stdio.h>

#include "../include/lib/m_arena.h"
#include "../include/lib/table.h"

#include "../include/db/db.h"
#include "../include/db/csv_reader.h"

int main(void) {

	CSVReader reader;
	initCSVReader(&reader);

	int ret = tryCSVRead(&reader, "./resources/csv/ttc_dataset.csv");
	if (ret == 0) {
		//printf("%s\n", reader.text);
	}

	termCSVReader(&reader);
	return 0;
}
