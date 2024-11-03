#ifndef FT_ENUM_H
#define FT_ENUM_H

typedef enum {
	FT_TEXT,
	FT_CHAR,

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
	FT_TIME,
	FT_DATETIME,

	FT_BLOB,

	FT_UUID,

	FT_ERR
} FieldType;

#endif // FT_ENUM_H
