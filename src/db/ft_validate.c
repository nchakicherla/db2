#include "../../include/db/ft_validate.h"

#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <stdlib.h>

bool ft_validate_TEXT(char *field) {
	return true;
}
bool ft_validate_CHAR(char *field) {
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

bool ft_validate_INT8(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr == '\0') {
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
bool ft_validate_INT16(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr == '\0') {
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
bool ft_validate_INT32(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr == '\0') {
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
bool ft_validate_INT64(char *field) {
	//long long int test;
	char *end_ptr = field;

	//test = strtoll(field, &end_ptr, 0);
	strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr == '\0') {
		return false;
	}
	return true;
}

bool ft_validate_UINT8(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr == '\0') {
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
bool ft_validate_UINT16(char *field) {
	long long int test;
	char *end_ptr = field;

	test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr == '\0') {
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
bool ft_validate_UINT32(char *field) {
	long long int test;
	char *end_ptr = field;

   test = strtoll(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr == '\0') {
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
bool ft_validate_UINT64(char *field) {
	//unsigned long long int test;
	char *end_ptr = field;

	//test = strtoull(field, &end_ptr, 0);
	strtoull(field, &end_ptr, 0);

	if(end_ptr == field || *end_ptr == '\0') {
		return false;
	}
	return true;
}

bool ft_validate_FLOAT(char *field);
bool ft_validate_DOUBLE(char *field);

bool ft_validate_BOOLEAN(char *field);

bool ft_validate_DATE(char *field);
bool ft_validate_TIME(char *field);
bool ft_validate_DATETIME(char *field);

bool ft_validate_BLOB(char *field);

bool ft_validate_UUID(char *field);

/*
bool ft_validate_ERR(char *field) {
	return true;	
}
*/