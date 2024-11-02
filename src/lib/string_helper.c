#include "../../include/lib/string_helper.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct s_StringArray {
	size_t used;
	size_t cap;
	char **strs;
};

static int priv_growStringArray(struct s_StringArray *arr, Arena *scratch) {
	char **new_ptr = NULL;
	if(!(new_ptr = pGrowAlloc(arr->strs, arr->cap, 2 * arr->cap, scratch))) {
		return 1;
	}
	arr->strs = new_ptr;
	arr->cap = 2 * arr->cap;
	return 0;
}

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

	struct s_StringArray helper = {0, 0, NULL};
	helper.strs = pzalloc(scratch, 8 * sizeof(char *));
	helper.cap = 8;
	//printf("%p\n", (void *)&helper);

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
				//printf("%s\n", temp_token);

				//helper.strs[n_toks - 1] = palloc(scratch, tok_len + 1);
				printf("here\n");
				if(n_toks > helper.cap) {
					priv_growStringArray(&helper, scratch);
				}
				helper.strs[n_toks - 1] = pNewStr(temp_token, scratch);
				helper.used++;

				i += delim_len;
				tok_start = &input[i];
				tok_end = tok_start;
				n_toks++;
				//continue;
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
	//printf("%s\n", temp_token);

	if(n_toks >= helper.cap) {
		priv_growStringArray(&helper, scratch);
	}
	helper.strs[n_toks - 1] = pNewStr(temp_token, scratch);
	helper.used++;

	*n_toks_out = n_toks;
	//printf("n_toks: %zu\n", n_toks);

	for(size_t z = 0; z < n_toks; z++) {
		printf("%s\n", helper.strs[z]);
	}

	return NULL;
}