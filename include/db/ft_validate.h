#ifndef FT_VALIDATE_H
#define FT_VALIDATE_H

#include "./ft_enum.h"
#include "./csv_reader.h"

#include <stdbool.h>

bool FTValidateAsTEXT(char *field);
bool FTValidateAsCHAR(char *field);
bool FTValidateAsI8(char *field);
bool FTValidateAsI16(char *field);
bool FTValidateAsI32(char *field);
bool FTValidateAsI64(char *field);
bool FTValidateAsU8(char *field);
bool FTValidateAsU16(char *field);
bool FTValidateAsU32(char *field);
bool FTValidateAsU64(char *field);
bool FTValidateAsFLOAT(char *field);
bool FTValidateAsDOUBLE(char *field);
bool FTValidateAsBOOLEAN(char *field);
bool FTValidateAsDATE(char *field);
bool FTValidateAsTIME(char *field);
bool FTValidateAsDATETIME(char *field);
bool FTValidateAsBLOB(char *field);
bool FTValidateAsUUID(char *field);
bool FTValidateRow(CSVRow *row, FieldType *schema, size_t schema_len);
bool FTValidateAsType(char *field, FieldType type);

#endif // FT_VALIDATE_H
