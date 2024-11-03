#ifndef FT_VALIDATE_H
#define FT_VALIDATE_H

#include <stdbool.h>

bool ft_validate_TEXT(char *field);
bool ft_validate_CHAR(char *field);

bool ft_validate_INT8(char *field);
bool ft_validate_INT16(char *field);
bool ft_validate_INT32(char *field);
bool ft_validate_INT64(char *field);

bool ft_validate_UINT8(char *field);
bool ft_validate_UINT16(char *field);
bool ft_validate_UINT32(char *field);
bool ft_validate_UINT64(char *field);

bool ft_validate_FLOAT(char *field);
bool ft_validate_DOUBLE(char *field);

bool ft_validate_BOOLEAN(char *field);

bool ft_validate_DATE(char *field);
bool ft_validate_TIME(char *field);
bool ft_validate_DATETIME(char *field);

bool ft_validate_BLOB(char *field);

bool ft_validate_UUID(char *field);

// bool ft_validate_ERR(char *field);

#endif // FT_VALIDATE_H
