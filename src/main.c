#include <stdio.h>

#include "../include/lib/m_arena.h"
#include "../include/lib/table.h"

#include "../include/db/db.h"
#include "../include/db/csv_reader.h"

#include "../include/db/ft_enum.h"
#include "../include/db/ft_labels.h"
#include "../include/db/ft_validate.h"
#include "../include/db/datetime.h"

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
	FT_TEXT,
};

int main(void) {

	CSVReader reader;
	initCSVReader(&reader);

	printf("(%d) try csv read\n", tryCSVRead(&reader, "./resources/csv/ttc_dataset.csv"));
	printf("(%p) get row at %d\n", (void *)getCSVRowAtIndex(&reader, 235), 235);
	
	CSVRow *res_good = getCSVRowAtIndex(&reader, 235);
	printRow(res_good);

	printf("(%d) try reset csv\n", resetCSVReader(&reader));
	CSVRow *res_bad = getCSVRowAtIndex(&reader, 235);
	printRow(res_bad);

	printf("(%d) re-try csv read\n", tryCSVRead(&reader, "./resources/csv/ttc_dataset.csv"));
	res_good = getCSVRowAtIndex(&reader, 42);
	
	printf("row->n_cols: %zu\n", res_good->n_cols);

	bool validation = false;
	printRow(res_good);
	validation = FTValidateRow(res_good, test_schema, (sizeof(test_schema) / sizeof(FieldType)));
	if(validation) {
		printf("validation passed!\n");
	}
	if(!validation) {
		printf("validation failed!\n");
	}

	DateTimeFmt fmt;
	initDateTimeFmt(&fmt);

	char *test_date = "03-01";
	fmt = guessFormat(test_date);
	printf("trying guessFormat on \'%s\'\n", test_date);
	printf("fmt.str: \'%s\'\n", fmt.str);

	printf("(%d) re-try csv read\n", tryCSVRead(&reader, "./resources/csv/test.csv"));
	res_good = getCSVRowAtIndex(&reader, 0);
	printRow(res_good);

	termCSVReader(&reader);
	return 0;
}

/*
	//printf("(%d) try reset csv\n", resetCSVReader(&reader));

	size_t counter = 1;
	for (size_t i = 100; i < 130; i++) {
		printf("(%p) get row at %zu\n", (void *)getCSVRowAtIndex(&reader, i), i);
		printf("(%d) remove row at %zu\n", removeRowAtIndex(&reader, i), i);
		counter++;
	}
*/
