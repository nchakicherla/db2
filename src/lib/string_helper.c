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

	///printf("TEST: %s\n", input);

	size_t delim_len = strlen(delim);
	size_t safety_begins_len = strlen(safety_begins);
	size_t safety_ends_len = strlen(safety_ends);

	///printf("delim_len: %zu\n", delim_len);

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

	for(size_t i = 0; i < len - (delim_len - 1); i++) {
		/*
		printf("ITER: %zu\n", i);
		for(size_t t = 0; t < n_toks - 1; t++) {
			printf("ptr %zu: %p\n", t, (void *)helper.strs[t]);
		}
		*/
		//printf("i: %zu, c: %c\n", i, input[i]);
		if(priv_checkAllMatch(in_safety, safety_begins_len, false)) {
			if(subNStrMatch(&input[i], delim, delim_len)) {
				//printf("substr match!\n");
				//tok_end++;
				//tok_end = &input[i];

				size_t tok_len = tok_end - tok_start;
				temp_token = palloc(scratch, tok_len + 1);
				for(size_t w = 0; w < tok_len; w++) {
					temp_token[w] = *(tok_start + w);
				}
				temp_token[tok_len] = '\0';
				//printf("temp_token: %s\n", temp_token);
				//printf("tok_len: %zu\n", tok_len);

				//helper.strs[n_toks - 1] = palloc(scratch, tok_len + 1);
				//printf("here9\n");
				if(helper.used == helper.cap) {
					//size_t old_cap = helper.cap;
					priv_growStringArray(&helper, scratch);
				}
				helper.strs[n_toks - 1] = pNewStr(temp_token, scratch);
				helper.used++;
				//printf("strs[i]: %s\n", helper.strs[n_toks - 1]);

				tok_start = &input[i + 1];
				tok_end = &input[i];
				
				i += delim_len - 1;
				
				//printf("tok_start: %c\n", *tok_start);
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
	temp_token = palloc(scratch, tok_len + 1);
	for(size_t i = 0; i < tok_len; i++) {
		temp_token[i] = tok_start[i];
	}
	temp_token[tok_len] = '\0';
	//printf("%s\n", temp_token);

	if(helper.used == helper.cap) {
		priv_growStringArray(&helper, scratch);
	}
	helper.strs[n_toks - 1] = pNewStr(temp_token, scratch);
	helper.used++;

	*n_toks_out = n_toks;
	//printf("n_toks: %zu\n", n_toks);
/*
	for(size_t z = 0; z < n_toks; z++) {
		//printf("in loop\n");
		//printf("%s\n", helper.strs[z]);
		printf("%zu: %p\n", z, (void *)helper.strs[z]);
	}
*/
	return helper.strs;
}
