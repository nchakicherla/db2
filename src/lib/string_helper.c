#include "../../include/lib/string_helper.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static bool priv_checkAllMatch(bool *vals, size_t n, bool check) {
	for(size_t i = 0; i < n; i++) {
		if(vals[i] != check) {
			return false;
		}
	}
	return true;
}

bool subNStrMatch(char *search, char *find, size_t n) {
	for(size_t i = 0; i < n; i++) {
		//printf("search: %c, find: %c\n", search[i], find[i]);
		if(search[i] != find[i]) {
			return false;
		}
	}
	return true;
}

char **tryStringSplit(char *input, size_t len, char *delim, char *safety_begins, char *safety_ends, Arena *scratch, size_t *n_toks_out) {

	size_t delim_len = strlen(delim);
	size_t safety_begins_len = strlen(safety_begins);
	size_t safety_ends_len = strlen(safety_ends);

	if(safety_begins_len != safety_ends_len) {
		return NULL;
	}
	if(delim_len > len) {
		return NULL;
	}

	size_t n_toks = 1;
	bool *in_safety = palloc(scratch, safety_begins_len * sizeof(bool));
	char *tok_start = input;
	char *tok_end = input;

	char *temp_token = NULL;

	for(size_t i = 0; i < safety_begins_len; i++) {
		in_safety[i] = false;
	}

	for(size_t i = 0; i < len - delim_len; i++) {
		//printf("%c", input[i]);
		if(priv_checkAllMatch(in_safety, safety_begins_len, false)) {
			if(subNStrMatch(&input[i], delim, delim_len)) {

				//tok_end++;
				tok_end = &input[i];

				size_t tok_len = tok_end - tok_start;
				temp_token = palloc(scratch, tok_len + 1);
				for(size_t w = 0; w < tok_len; w++) {
					temp_token[w] = *(tok_start + w);
				}
				temp_token[tok_len] = '\0';
				printf("%s\n", temp_token);

				i += delim_len;
				tok_start = &input[i];
				tok_end = tok_start;
				n_toks++;
				continue;
			}
		}
		for(int j = 0; j < safety_begins_len; j++) {
			if(!in_safety[j] && input[i] == safety_begins[j]) {
				in_safety[j] = true;
				break;
			}
			if(in_safety[j] && input[i] == safety_ends[j]) {
				in_safety[j] = false;
				break;
			}
		}
		tok_end++;
	}
	size_t tok_len = len  - (tok_start - input);
	temp_token = palloc(scratch, tok_len);
	for(size_t i = 0; i < tok_len; i++) {
		temp_token[i] = tok_start[i];
	}
	temp_token[tok_len] = '\0';
	printf("%s\n", temp_token);


	*n_toks_out = n_toks;
	printf("n_toks: %zu\n", n_toks);

	return NULL;
}