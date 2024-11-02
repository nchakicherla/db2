#ifndef FIELD_TYPES_H
#define FIELD_TYPES_H

typedef enum {
	FT_TEXT,

	FT_I8,
	FT_I16,
	FT_I32,
	FT_I64,

	FT_U8,
	FT_U16,
	FT_U32,
	FT_U64,

	FT_FLOAT,
	FT_DOUBLE,

	FT_BOOLEAN,

	FT_DATE,
	FT_DATETIME,

	FT_BLOB,

	FT_UUID,

	FT_ERR
} FieldType;

#endif // FIELD_TYPES_H