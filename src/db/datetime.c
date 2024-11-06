#include "../../include/db/datetime.h"
#include "../../include/db/datetime_lookups.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

struct s_priv_SearchReturn { // can store max 8 locations
	int n;
	int locs[8];
};

static struct s_priv_SearchReturn priv_findCharInString(char *str, char c) { // limited to 8 max
	struct s_priv_SearchReturn output = {0};
	size_t len = strlen(str);
	if(len == 0) {
		return output;
	}

	int count = 0;
	for(size_t i = 0; i < len; i++) {
		if(str[i] == c) {
			output.locs[count] = i;
			count++;
		}
	}

	output.n = count;
	return output;
}

static void priv_writeCharsAtIdx(char *dest, char *src, int n) {
	for(int i = 0; i < n; i++) {
		dest[i] = src[i];
	}
}

static bool priv_isLeapYear(uint16_t year) {
	if(year % 4 == 0) {
		if(year % 100 == 0) {
			if(year % 400 == 0) {
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

void initDateTimeFmt(DateTimeFmt *dt_fmt) {
	dt_fmt->str[0] = '\0';
	dt_fmt->flags = 0;
}

#define UNSIGNED_DT_MEMBER_INIT 0
#define SIGNED_DT_MEMBER_INIT -1

void initDateTime(DateTime *dt) {
	// unsigned
	dt->year = UNSIGNED_DT_MEMBER_INIT;
	dt->month = UNSIGNED_DT_MEMBER_INIT;
	dt->day = UNSIGNED_DT_MEMBER_INIT;
	// signed
	dt->hour = SIGNED_DT_MEMBER_INIT;
	dt->minute = SIGNED_DT_MEMBER_INIT;
	dt->second = SIGNED_DT_MEMBER_INIT;
	dt->ctsecond = SIGNED_DT_MEMBER_INIT;
}

#undef UNSIGNED_DT_MEMBER_INIT
#undef SIGNED_DT_MEMBER_INIT

int setDateTimeFmt(DateTimeFmt *dt_fmt, char *spec) {
	size_t len = strlen(spec);
	if(len + 1 > DT_FMT_SIZE) {
		return 1;
	}
	for(int i = 0; i < len; i++) {
		dt_fmt->str[i] = spec[i];
	}
	dt_fmt->str[len] = '\0';
	return 0;
}

void setDateTimeFmtFlag(DateTimeFmt *dt_fmt, uint8_t flag, bool setting) {
	//dt_fmt->flags |= flag;
	setting ? (dt_fmt->flags |= flag) : (dt_fmt->flags &= ~flag);
}

bool checkDateTimeFmtFlag(DateTimeFmt *dt_fmt, uint8_t flag) {
	return dt_fmt->flags & flag;
}

DateTimeFmt guessDateTimeFmt(char *string) {
	DateTimeFmt output = {0};
	size_t len = strlen(string);
	if(len + 1 > DT_FMT_SIZE) {
		return output;
	}

	int output_idx = 0;
	char *it = string;
	struct s_priv_SearchReturn res;

	while(*it != '\0' && (it - string) < DT_FMT_SIZE) {
		while(*it != '\0' && !isalpha(*it) && !isdigit(*it)) {
			output.str[output_idx] = *it;
			output_idx++;
			it++;
		}
		if(isdigit(*it)) {

			res = priv_findCharInString(it, '-');
			if(res.n == 2) {
				if(res.locs[0] == 4 && res.locs[1] == 7) { // YEAR-month-day
					priv_writeCharsAtIdx(&output.str[output_idx], "%Y-%m-%d", 8);
					output_idx += 8;
					it+= 10;
					continue;
				}
				if(res.locs[0] == 2 && res.locs[1] == 5) { // year-month-day
					priv_writeCharsAtIdx(&output.str[output_idx], "%y-%m-%d", 8);
					output_idx += 8;
					it+= 8;
					continue;
				}
			}
			if(res.n == 1) {
				if(res.locs[0] == 4 && !isdigit(*(it + 7))) { // YEAR-month
					priv_writeCharsAtIdx(&output.str[output_idx], "%Y-%m", 5);
					output_idx += 5;
					it+= 7;
					continue;
				}
				if(res.locs[0] == 2 && !isdigit(*(it + 5))) { // month-day
					priv_writeCharsAtIdx(&output.str[output_idx], "%m-%d", 5);
					output_idx += 5;
					it+= 5;
					continue;
				}
			}

			res = priv_findCharInString(it, ':');
			if(res.n == 2) {
				// 24-hour:minute:second
				if(res.locs[0] == 2 && res.locs[1] == 5) {
					priv_writeCharsAtIdx(&output.str[output_idx], "%H:%M:%S", 8);
					output_idx += 8;
					it+= 8;
					continue;
				}
			}
			if(res.n == 1) {
				// minute:second
				if(res.locs[0] == 2 && !isdigit(*(it + 7))) {
					priv_writeCharsAtIdx(&output.str[output_idx], "%M:%S", 5);
					output_idx += 5;
					it+= 5;
					continue;
				}
			}

			res = priv_findCharInString(it, '/');
			if(res.n == 2) {
				// YEAR/month/day
				if(res.locs[0] == 4 && res.locs[1] == 7) {
					priv_writeCharsAtIdx(&output.str[output_idx], "%Y/%m/%d", 8);
					output_idx += 8;
					it+= 10;
					continue;
				}
				// day/month/YEAR
				if(res.locs[0] == 2 && res.locs[1] == 5 && isdigit(*(it + 8)) && isdigit(*(it + 9))) {
					priv_writeCharsAtIdx(&output.str[output_idx], "%d/%m/%Y", 8);
					output_idx += 8;
					it+= 10;
					continue;
				}
				// day/month/year
				if(res.locs[0] == 2 && res.locs[1] == 5 && !isdigit(*(it + 8))) {
					priv_writeCharsAtIdx(&output.str[output_idx], "%d/%m/%y", 8);
					output_idx += 8;
					it+= 8;
					continue;
				}
			}
			if(res.n == 1) {
				// month/day
				if(res.locs[0] == 2 && !isdigit(*(it + 5))) {
					priv_writeCharsAtIdx(&output.str[output_idx], "%m/%d", 5);
					output_idx += 5;
					it+= 5;
					continue;
				}
			}
			it++;
		}
		if(isalpha(*it)) {
			size_t keyword_len = 0;
			char* reset = it;
			while(isalpha(*it)) {
				keyword_len++;
				it++;
			}
			it = reset;

			int matched_table = -1;
			for(int i = 0; i < sizeof(SpecifierTablePairs) / sizeof(SpecifierTablePairs[0]); i++) {
				int j = 0; // i - SpecifierTablePair index, j - index within table
				while(SpecifierTablePairs[i].table[j] != NULL) {
					if(0 == strncmp(SpecifierTablePairs[i].table[j], it, keyword_len)) {
						matched_table = i;
						break;
					}
					j++;
				}
				if(matched_table > -1) {
					priv_writeCharsAtIdx(&output.str[output_idx], "%", 1);
					output_idx++;
					char tmp[2] = {SpecifierTablePairs[i].c, '\0'};
					priv_writeCharsAtIdx(&output.str[output_idx], tmp, 1);
					output_idx++;
					while(isalpha(*it)) {
						it++;
					}
					break;
				}
			}
		}
	}
	output.str[output_idx] = '\0';
	return output;
}
