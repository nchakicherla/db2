#include "../../include/db/datetime.h"

#include <string.h>

void initDateTimeFormat(DateTimeFormat *dt_fmt) {
	for(int i = 0; i < DT_FMT_SIZE; i++) {
		dt_fmt->fmt[i] = '\0';
	}
	dt_fmt->flags = 0;
}

int setDateTimeFormat(DateTimeFormat *dt_fmt, char *spec) {
	size_t len = strlen(spec);
	if(len + 1 > DT_FMT_SIZE) {
		return 1;
	}
	for(int i = 0; i < len; i++) {
		dt_fmt->fmt[i] = spec[i];
	}
	dt_fmt->fmt[len] = '\0';
	return 0;
}

void setFlag(DateTimeFormat *dt_fmt, uint8_t flag) {
	dt_fmt->flags |= flag;
}

bool checkFlag(DateTimeFormat *dt_fmt, uint8_t flag) {
	return dt_fmt->flags & flag;
}
