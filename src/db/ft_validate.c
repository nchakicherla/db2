#include "../../include/db/ft_validate.h"

#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>

#define ALLOW_BLANK_TEXT true

bool FTValidateTEXT(char *field) {
	if(strlen(field) == 0 && !ALLOW_BLANK_TEXT) {
		return false;
	}
	return true;
}
bool FTValidateCHAR(char *field) {
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

bool FTValidateINT8(char *field) {
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
bool FTValidateINT16(char *field) {
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
bool FTValidateINT32(char *field) {
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
bool FTValidateINT64(char *field) {
	//long long int test;
	char *end_ptr = field;

	//test = strtoll(field, &end_ptr, 0);
	strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	return true;
}

bool FTValidateUINT8(char *field) {
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
bool FTValidateUINT16(char *field) {
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
bool FTValidateUINT32(char *field) {
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
bool FTValidateUINT64(char *field) {
	//unsigned long long int test;
	char *end_ptr = field;

	//test = strtoull(field, &end_ptr, 0);
	strtoull(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	return true;
}

bool FTValidateFLOAT(char *field) {
	char *end_ptr = field;

	strtof(field, &end_ptr);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	return true;
}
bool FTValidateDOUBLE(char *field) {
	char *end_ptr = field;

	strtod(field, &end_ptr);

	if(end_ptr == field || *end_ptr != '\0') {
		return false;
	}
	return true;
}

bool FTValidateBOOLEAN(char *field) {
	size_t len = strlen(field);
	if(len < 4 || len > 5) {
		return false;
	}

	char buffer[8] = {0};
	for(int i = 0; i < len; i++) {
		buffer[i] = tolower(field[i]);
	}
	buffer[len] = '\0';

	int res = strncmp(buffer, "true", 4);
	if(res == 0) {
		return true;
	}
	res = strncmp(buffer, "false", 5);
	if(res == 0) {
		return true;
	}
	return false;
}

bool FTValidateDATE(char *field) {
	return false;
}
bool FTValidateTIME(char *field) {
	return false;
}
bool FTValidateDATETIME(char *field) {
	return false;
}

bool FTValidateBLOB(char *field) {
	return false;
}

bool FTValidateUUID(char *field) {
	return false;
}

/*
bool FTValidateERR(char *field) {
	return true;	
}
*/

bool FTValidateRow(CSVRow *row, FieldType *schema) {
	if(!schema) {
		return false;
	}

	bool stat = false;
	for(size_t i = 0; i < row->n_cols; i++) {
		switch(schema[i]) {
			case FT_TEXT: {
				stat = FTValidateTEXT(row->cols[i]);
				break;
			}
			case FT_CHAR: {
				stat = FTValidateCHAR(row->cols[i]);
				break;
			}
			case FT_I8: {
				stat = FTValidateINT8(row->cols[i]);
				break;
			}
			case FT_I16: {
				stat = FTValidateINT16(row->cols[i]);
				break;
			}
			case FT_I32: {
				stat = FTValidateINT32(row->cols[i]);
				break;
			}
			case FT_I64: {
				stat = FTValidateINT64(row->cols[i]);
				break;
			}
			case FT_U8: {
				stat = FTValidateUINT8(row->cols[i]);
				break;
			}
			case FT_U16: {
				stat = FTValidateUINT16(row->cols[i]);
				break;
			}
			case FT_U32: {
				stat = FTValidateUINT32(row->cols[i]);
				break;
			}
			case FT_U64: {
				stat = FTValidateUINT64(row->cols[i]);
				break;
			}
			case FT_FLOAT: {
				stat = FTValidateFLOAT(row->cols[i]);
				break;
			}
			case FT_DOUBLE: {
				stat = FTValidateDOUBLE(row->cols[i]);
				break;
			}
			case FT_BOOLEAN: {
				stat = FTValidateBOOLEAN(row->cols[i]);
				break;
			}
			case FT_DATE: {
				stat = FTValidateDATE(row->cols[i]);
				break;
			}
			case FT_TIME: {
				stat = FTValidateTIME(row->cols[i]);
				break;
			}
			case FT_DATETIME: {
				stat = FTValidateDATETIME(row->cols[i]);
				break;
			}
			case FT_BLOB: {
				stat = FTValidateBLOB(row->cols[i]);
				break;
			}
			case FT_UUID: {
				stat = FTValidateUUID(row->cols[i]);
				break;
			}
			case FT_ERR:
			default:
				stat = false;
		}
		if(stat == false) {
			return false;
		}
	}
	return true;
}
