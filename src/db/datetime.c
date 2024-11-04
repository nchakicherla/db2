#include "../../include/db/datetime.h"
#include "../../include/db/datetime_lookups.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>

struct s_priv_SearchReturn {
	int n;
	int locs[8];
};

struct s_priv_SearchReturn priv_findCharInString(char *str, char c) { // limited to 8 max
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

void priv_writeCharsAtIdx(char *dest, char *src, int n) {
	for(int i = 0; i < n; i++) {
		dest[i] = src[i];
	}
}

void initDateTimeFormat(DateTimeFormat *dt_fmt) {
	dt_fmt->str[0] = '\0';
	dt_fmt->flags = 0;
}

int setDateTimeFormat(DateTimeFormat *dt_fmt, char *spec) {
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

void setFlag(DateTimeFormat *dt_fmt, uint8_t flag) {
	dt_fmt->flags |= flag;
}

bool checkFlag(DateTimeFormat *dt_fmt, uint8_t flag) {
	return dt_fmt->flags & flag;
}

DateTimeFormat guessFormat(char *string) {
	DateTimeFormat output = {0};
	size_t len = strlen(string);
	if(len + 1 > DT_FMT_SIZE) {
		return output;
	}

	int output_idx = 0;
	char *it = string;
	struct s_priv_SearchReturn res;

	while(*it != '\0' && (it - string) < DT_FMT_SIZE) {
		while(!isalpha(*it) && !isdigit(*it) && *it != '\0') {
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
				if(res.locs[0] == 2 && res.locs[1] == 5) { // 24-hour:minute:second
					priv_writeCharsAtIdx(&output.str[output_idx], "%H:%M:%S", 8);
					output_idx += 8;
					it+= 8;
					continue;
				}
			}
			if(res.n == 1) {
				if(res.locs[0] == 2 && !isdigit(*(it + 7))) { // minute:second
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
					priv_writeCharsAtIdx(&output.str[output_idx], "%d/%m/%y", 8);
					output_idx += 8;
					it+= 10;
					continue;
				}
				// day/month/year
				if(res.locs[0] == 2 && res.locs[1] == 5 && !isdigit(*(it + 8))) {
					priv_writeCharsAtIdx(&output.str[output_idx], "%d/%m/%y", 8);
					output_idx += 8;
					it+= 10;
					continue;
				}
			}
			if(res.n == 1) {
				if(res.locs[0] == 2 && !isdigit(*(it + 5))) { // month/day
					priv_writeCharsAtIdx(&output.str[output_idx], "%m/%d", 5);
					output_idx += 5;
					it+= 5;
					continue;
				}
			}
		}
		if(isalpha(*it)) {
			output.str[output_idx] = *it;
			output_idx++;
		}
		if(*it == '\0') {
			break;
		}
		it++;
	}
	output.str[output_idx] = '\0';
	return output;
}
