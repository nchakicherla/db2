#ifndef DATETIME_LOOKUPS_H
#define DATETIME_LOOKUPS_H

#include <stddef.h>

char *MONTHS_SHORT[] = {
	"jan",
	"feb",
	"mar",
	"apr",
	"may",
	"jun",
	"jul",
	"aug",
	"sep",
	"oct",
	"nov",
	"dec",
	NULL,
};

char *MONTHS_FULL[] = {
	"january",
	"february",
	"march",
	"april",
	"may",
	"june",
	"july",
	"august",
	"september",
	"october",
	"november",
	"december",
	NULL,
};

char *DAYS_SHORT[] = {
	"sun",
	"mon",
	"tue",
	"wed",
	"thu",
	"fri",
	"sat",
	NULL,
};

char *DAYS_FULL[] = {
	"sunday",
	"monday",
	"tuesday",
	"wednesday",
	"thursday",
	"friday",
	"saturday",
	NULL,
};

char *PERIOD[] = {
	"am",
	"pm",
	NULL,
};

struct s_SpecifierTablePair {
	char c;
	char **table;
};

struct s_SpecifierTablePair SpecifierTablePairs[] = {
	{'b', MONTHS_SHORT},
	{'B', MONTHS_FULL},
	{'u', DAYS_SHORT},
	{'U', DAYS_FULL},
	{'p', PERIOD}
};

#endif // DATETIME_LOOKUPS_H
