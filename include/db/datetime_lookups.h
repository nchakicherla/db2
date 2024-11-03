#ifndef DATETIME_LOOKUPS_H
#define DATETIME_LOOKUPS_H

#include <stddef.h>

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

char *PERIOD[] = {
	"am",
	"pm",
	NULL,
};

struct s_CharTablePair {
	char c;
	char **literal;
};

struct s_CharTablePair table[] = {
	{'B', MONTHS_FULL},
	{'b', MONTHS_SHORT},
	{'U', DAYS_FULL},
	{'u', DAYS_SHORT},
	{'p', PERIOD},
	{0}
};

#endif // DATETIME_LOOKUPS_H