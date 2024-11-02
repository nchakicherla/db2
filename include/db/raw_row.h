#ifndef RAW_ROW_H
#define RAW_ROW_H

typedef struct s_RawFieldNode {
	char* start;
	char* len;
	struct s_RawFieldNode *next;
} RawFieldNode;

#endif // RAW_ROW_H