#ifndef FT_VALIDATE_H
#define FT_VALIDATE_H

#include "./ft_enum.h"
#include "./csv_reader.h"

#include <stdbool.h>


bool FTValidateTEXT(char *field);
bool FTValidateCHAR(char *field);

bool FTValidateINT8(char *field);
bool FTValidateINT16(char *field);
bool FTValidateINT32(char *field);
bool FTValidateINT64(char *field);

bool FTValidateUINT8(char *field);
bool FTValidateUINT16(char *field);
bool FTValidateUINT32(char *field);
bool FTValidateUINT64(char *field);

bool FTValidateFLOAT(char *field);
bool FTValidateDOUBLE(char *field);

bool FTValidateBOOLEAN(char *field);

bool FTValidateDATE(char *field);
bool FTValidateTIME(char *field);
bool FTValidateDATETIME(char *field);

bool FTValidateBLOB(char *field);

bool FTValidateUUID(char *field);

// bool FTValidateERR(char *field);

bool FTValidateRow(CSVRow *row, FieldType *schema);

#endif // FT_VALIDATE_H
