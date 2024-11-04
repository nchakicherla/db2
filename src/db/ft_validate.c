#include "../../include/db/ft_validate.h"

#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>

#define ALLOW_BLANK_TEXT true

bool FTValidateAsTEXT(char *field) {
	if(strlen(field) == 0 && !ALLOW_BLANK_TEXT) {
		return false;
	}
	return true;
}

bool FTValidateAsCHAR(char *field) {
	size_t len = strlen(field);
	if(len > 1) {
		return false;
	}
	if(len == 0) {
		return false;
	}
	if(isalpha(field[0])) {
		return true;
	}
	return false;
}

bool FTValidateAsI8(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	if(test < INT8_MIN) {
		return false;
	}
	if(test > INT8_MAX) {
		return false;
	}
	return true;
}

bool FTValidateAsI16(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	if(test < INT16_MIN) {
		return false;
	}
	if(test > INT16_MAX) {
		return false;
	}
	return true;
}

bool FTValidateAsI32(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	if(test < INT32_MIN) {
		return false;
	}
	if(test > INT32_MAX) {
		return false;
	}
	return true;
}

bool FTValidateAsI64(char *field) {
	char *end_ptr = field;

	strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	return true;
}

bool FTValidateAsU8(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	if(test < 0) {
		return false;
	}
	if(test > UINT8_MAX) {
		return false;
	}
	return true;
}

bool FTValidateAsU16(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	if(test < 0) {
		return false;
	}
	if(test > UINT16_MAX) {
		return false;
	}
	return true;
}

bool FTValidateAsU32(char *field) {
	long long int test;
	char *end_ptr = field;

   test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	if(test < 0) {
		return false;
	}
	if(test > UINT8_MAX) {
		return false;
	}
	return true;
}

bool FTValidateAsU64(char *field) {
	//unsigned long long int test;
	char *end_ptr = field;

	strtoull(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	return true;
}

bool FTValidateAsFLOAT(char *field) {
	char *end_ptr = field;

	strtof(field, &end_ptr);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	return true;
}

bool FTValidateAsDOUBLE(char *field) {
	char *end_ptr = field;

	strtod(field, &end_ptr);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	return true;
}

bool FTValidateAsBOOLEAN(char *field) {
	size_t len = strlen(field);
	if(len < 4 || len > 5) {
		return false;
	}

	char buffer[8] = {0};
	char *start_ptr = field;

	while(*start_ptr == ' ' || *start_ptr == '\t') {
		start_ptr++;
	}

	for(int i = 0; i < len; i++) {
		buffer[i] = tolower(start_ptr[i]);
	}
	buffer[len] = '\0';

	if(0 == strncmp(buffer, "true", 4)) {
		return true;
	}
	if(0 == strncmp(buffer, "false", 5)) {
		return true;
	}
	if(0 == strncmp(buffer, "1", 1)) {
		return true;
	}
	if(0 == strncmp(buffer, "0", 1)) {
		return true;
	}
	return false;
}

bool FTValidateAsDATE(char *field) {
	return false;
}

bool FTValidateAsTIME(char *field) {
	return false;
}

bool FTValidateAsDATETIME(char *field) {
	return false;
}

bool FTValidateAsBLOB(char *field) {
	return false;
}

bool FTValidateAsUUID(char *field) {
	return false;
}

bool FTValidateRow(CSVRow *row, FieldType *schema) {
	if(!schema) {
		return false;
	}

	bool stat = false;
	for(size_t i = 0; i < row->n_cols; i++) {
		stat = FTValidateAsType(row->cols[i], schema[i]);
		if(stat == false) {
			return false;
		}
	}
	return true;
}

bool FTValidateAsType(char *field, FieldType type) {
	bool stat = true;
	switch(type) {
		case FT_TEXT: {
			stat = FTValidateAsTEXT(field);
			break;
		}
		case FT_CHAR: {
			stat = FTValidateAsCHAR(field);
			break;
		}
		case FT_I8: {
			stat = FTValidateAsI8(field);
			break;
		}
		case FT_I16: {
			stat = FTValidateAsI16(field);
			break;
		}
		case FT_I32: {
			stat = FTValidateAsI32(field);
			break;
		}
		case FT_I64: {
			stat = FTValidateAsI64(field);
			break;
		}
		case FT_U8: {
			stat = FTValidateAsU8(field);
			break;
		}
		case FT_U16: {
			stat = FTValidateAsU16(field);
			break;
		}
		case FT_U32: {
			stat = FTValidateAsU32(field);
			break;
		}
		case FT_U64: {
			stat = FTValidateAsU64(field);
			break;
		}
		case FT_FLOAT: {
			stat = FTValidateAsFLOAT(field);
			break;
		}
		case FT_DOUBLE: {
			stat = FTValidateAsDOUBLE(field);
			break;
		}
		case FT_BOOLEAN: {
			stat = FTValidateAsBOOLEAN(field);
			break;
		}
		case FT_DATE: {
			stat = FTValidateAsDATE(field);
			break;
		}
		case FT_TIME: {
			stat = FTValidateAsTIME(field);
			break;
		}
		case FT_DATETIME: {
			stat = FTValidateAsDATETIME(field);
			break;
		}
		case FT_BLOB: {
			stat = FTValidateAsBLOB(field);
			break;
		}
		case FT_UUID: {
			stat = FTValidateAsUUID(field);
			break;
		}
		case FT_ERR:
		default:
			stat = false;
	}
	return stat;
}
