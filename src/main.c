#include <stdio.h>

#include "../include/lib/m_arena.h"
#include "../include/lib/table.h"

#include "../include/db/db.h"
#include "../include/db/csv_reader.h"

int main(void) {

	CSVReader reader;
	initCSVReader(&reader);

	tryCSVRead(&reader, "./resources/csv/tyler_the_creator_dataset.csv");

	termCSVReader(&reader);
	return 0;
}
