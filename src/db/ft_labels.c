#include "../../include/db/ft_labels.h"

static char *FieldTypeLabels[] = {
	"TEXT",
	"CHAR",

	"INT8",
	"INT16",
	"INT32",
	"INT64",

	"UINT8",
	"UINT16",
	"UINT32",
	"UINT64",

	"FLOAT",
	"DOUBLE",

	"BOOLEAN",

	"DATE",
	"TIME",
	"DATETIME",

	"BLOB",

	"UUID",

	"ERR",
};

char* getFieldTypeLabel(int type) {
	return FieldTypeLabels[type];
}
