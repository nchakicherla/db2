#ifndef DATETIME_H
#define DATETIME_H

#include <inttypes.h>
#include <stdbool.h>

#define DT_FMT_SIZE 31
#define FLAG_AMPM (1 << 1)
/*
ISO 8601 		"%Y-%m-%d %H:%M:%S"

%Y, %y 			YEAR 4-digit, 2-digit
%B, %b, %m 		MONTH  full, abbreviated, 2-digit
%d 				DAY of month

%U, %u 			DAY of week full, abbreviated // added

%H, %I 			HOUR 24-hour, 12-hour
%M 				MINUTE
%S 				SECOND

%G 				CENTI-SECOND // added

%p 				AM/PM

%Z 				TIMEZONE // won't implement
*/

typedef struct s_DateTimeFmt {
	char str[DT_FMT_SIZE];
	uint8_t flags;
} DateTimeFmt;

typedef struct s_DateTime {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	int8_t hour;
	int8_t minute;
	int8_t second;
	int8_t ctsecond;
} DateTime;

void initDateTimeFmt(DateTimeFmt *dt_fmt);
int setDateTimeFmt(DateTimeFmt *dt_fmt, char *spec);
void setDateTimeFmtFlag(DateTimeFmt *dt_fmt, uint8_t flag, bool setting);
bool checkDateTimeFmtFlag(DateTimeFmt *dt_fmt, uint8_t flag);
DateTimeFmt guessDateTimeFmt(char *string);

#endif // DATETIME_H
