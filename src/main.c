#include <stdio.h>

#include "../include/lib/m_arena.h"
#include "../include/lib/table.h"

#include "../include/db/db.h"
#include "../include/db/csv_reader.h"

#include "../include/db/ft_enum.h"
#include "../include/db/ft_labels.h"
#include "../include/db/ft_validate.h"

FieldType test_schema[26] = {
	FT_TEXT,
	FT_TEXT,
	FT_TEXT,
	FT_TEXT,
	FT_TEXT,

	FT_TEXT,
	FT_U8,
	FT_BOOLEAN,
	FT_FLOAT,
	FT_FLOAT,
	FT_TEXT,
	FT_FLOAT,
	FT_TEXT,
	FT_FLOAT,
	FT_FLOAT,

	FT_DOUBLE,
	FT_FLOAT,
	FT_FLOAT,
	FT_FLOAT,

	FT_I8,
	FT_TEXT,

	FT_TEXT,
	FT_TEXT,
	FT_TEXT,
	FT_TEXT,
	FT_TEXT

};

int main(void) {

	CSVReader reader;
	initCSVReader(&reader);

	printf("(%d) try csv read\n", tryCSVRead(&reader, "./resources/csv/ttc_dataset.csv"));
	printf("(%p) get row at %zu\n", (void *)getRowAtIndex(&reader, 235), (size_t)235);
	
	CSVRow *res_good = getRowAtIndex(&reader, 235);
	printRow(res_good);

	printf("(%d) try reset csv\n", resetCSVReader(&reader));
	CSVRow *res_bad = getRowAtIndex(&reader, 235);
	printRow(res_bad);

	printf("(%d) re-try csv read\n", tryCSVRead(&reader, "./resources/csv/ttc_dataset.csv"));
	res_good = getRowAtIndex(&reader, 1);
	printf("n columns: %zu\n", res_good->n_cols);

	bool validation = false;
	printRow(res_good);
	validation = FTValidateRow(res_good, test_schema);
	if(validation) {
		printf("passed!\n");
	}
	if(!validation) {
		printf("failed!\n");
	}

	termCSVReader(&reader);
	return 0;
}

/*
	//printf("(%d) try reset csv\n", resetCSVReader(&reader));

	size_t counter = 1;
	for (size_t i = 100; i < 130; i++) {
		printf("(%p) get row at %zu\n", (void *)getRowAtIndex(&reader, i), i);
		printf("(%d) remove row at %zu\n", removeRowAtIndex(&reader, i), i);
		counter++;
	}
*/