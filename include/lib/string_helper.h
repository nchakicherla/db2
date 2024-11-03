#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include "m_arena.h"

#include <stdbool.h>

bool subNStrMatch(char *search, char *find, size_t n);

char **tryStringSplit(char *input, size_t len, char *delim, char *safety_begins, char *safety_ends, Arena *scratch, size_t *n_toks_out);

#endif // STRING_HELPER_H
