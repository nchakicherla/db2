#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

#include "m_arena.h"

char *pReadFile(const char *name, Arena *pool);

int writeFileChars(char *name, char *source);

FILE *checkFileOpen(char *name, char *mode);

#endif // FILE_H
