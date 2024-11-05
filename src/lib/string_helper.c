#include "../../include/lib/string_helper.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define DEF_STRING_ARRAY_CAP 8

struct s_StringArray {
	size_t used;
	size_t cap;
	char **strs;
};

static int priv_growStringArray(struct s_StringArray *arr, Arena *scratch) {
	char **new_ptr = NULL;
	size_t old_cap = arr->cap;
	if(!(new_ptr = pGrowAlloc(arr->strs, old_cap * sizeof(char *), 2 * old_cap * sizeof(char *), scratch))) {
		return 1;
	}
	for(size_t i = old_cap; i < 2 * old_cap; i++) {
		new_ptr[i] = NULL;
	}
	arr->strs = new_ptr;
	arr->cap = 2 * old_cap;
	return 0;
}

static bool priv_checkAllMatch(int *vals, size_t n, int check) {
	for(size_t i = 0; i < n; i++) {
		if(vals[i] != check) {
			return false;
		}
	}
	return true;
}

bool subNStrMatch(char *search, char *find, size_t n) {
	for(size_t i = 0; i < n; i++) {
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

	struct s_StringArray helper = {0, 0, NULL};
	helper.strs = pzalloc(scratch, DEF_STRING_ARRAY_CAP * sizeof(char *));
	helper.cap = DEF_STRING_ARRAY_CAP;

	size_t n_toks = 1;
	//bool *in_safety = palloc(scratch, safety_begins_len * sizeof(bool));
	int *in_safety = palloc(scratch, safety_begins_len * sizeof(int));
	char *tok_start = input;
	char *tok_end = input;

	char *temp_token = NULL;

	for(size_t i = 0; i < safety_begins_len; i++) {
		//in_safety[i] = false;
		in_safety[i] = 0;
	}

	for(size_t i = 0; i < len - (delim_len - 1); i++) {
		if(priv_checkAllMatch(in_safety, safety_begins_len, false)) {
			if(subNStrMatch(&input[i], delim, delim_len)) {

				size_t tok_len = tok_end - tok_start;
				temp_token = palloc(scratch, tok_len + 1);
				for(size_t w = 0; w < tok_len; w++) {
					temp_token[w] = *(tok_start + w);
				}
				temp_token[tok_len] = '\0';

				if(helper.used == helper.cap) {
					priv_growStringArray(&helper, scratch);
				}
				helper.strs[n_toks - 1] = pNewStr(temp_token, scratch);
				helper.used++;

				tok_start = &input[i + delim_len];
				tok_end = &input[i];
				
				i += delim_len - 1;
				
				n_toks++;
			}
		}
		// check all start and end safeties char arrays if current char is contained, flip switch if safety is encountered
		for(int j = 0; j < safety_begins_len; j++) {
			if(!in_safety[j] && input[i] == safety_begins[j]) {
				//in_safety[j] = true;
				in_safety[j]++;
				break;
			}
			if(in_safety[j] && input[i] == safety_ends[j]) {
				//in_safety[j] = false;
				in_safety[j]--;
				break;
			}
		}
		tok_end++;
	}
	size_t tok_len = len  - (tok_start - input);
	temp_token = palloc(scratch, tok_len + 1);
	for(size_t i = 0; i < tok_len; i++) {
		temp_token[i] = tok_start[i];
	}
	temp_token[tok_len] = '\0';

	if(helper.used == helper.cap) {
		priv_growStringArray(&helper, scratch);
	}
	helper.strs[n_toks - 1] = pNewStr(temp_token, scratch);
	helper.used++;

	*n_toks_out = n_toks;

	return helper.strs;
}
