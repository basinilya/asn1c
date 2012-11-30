/*-
 * Copyright (c) 2003, 2005 Lev Walkin <vlm@lionet.info>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */
#ifndef	_INTEGER_H_
#define	_INTEGER_H_

#include <asn_application.h>
#include <asn_codecs_prim.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef ASN__PRIMITIVE_TYPE_t INTEGER_t;

extern asn_TYPE_descriptor_t asn_DEF_INTEGER;

/* Map with <tag> to integer value association */
typedef struct asn_INTEGER_enum_map_s {
	long		 nat_value;	/* associated native integer value */
	size_t		 enum_len;	/* strlen("tag") */
	const char	*enum_name;	/* "tag" */
} asn_INTEGER_enum_map_t;

/* This type describes an enumeration for INTEGER and ENUMERATED types */
typedef struct asn_INTEGER_specifics_s {
	asn_INTEGER_enum_map_t *value2enum;	/* N -> "tag"; sorted by N */
	unsigned int *enum2value;		/* "tag" => N; sorted by tag */
	int map_count;				/* Elements in either map */
	int extension;				/* This map is extensible */
	int strict_enumeration;			/* Enumeration set is fixed */
	int field_width;			/* Size of native integer */
	int field_unsigned;			/* Signed=0, unsigned=1 */
} asn_INTEGER_specifics_t;

asn_struct_print_f INTEGER_print;
ber_type_decoder_f INTEGER_decode_ber;
der_type_encoder_f INTEGER_encode_der;
xer_type_decoder_f INTEGER_decode_xer;
xer_type_encoder_f INTEGER_encode_xer;
per_type_decoder_f INTEGER_decode_uper;
per_type_encoder_f INTEGER_encode_uper;

/***********************************
 * Some handy conversion routines. *
 ***********************************/

#if 1
typedef long long asn_longlong;
typedef unsigned long long asn_ulonglong;

/* LONG_LONG_MAX is not always defined (not if STRICT_ANSI, for example).
   But we can find it either under the correct ANSI name, or under GNU
   C's internal name.  */
#ifdef LONG_LONG_MAX
# define ASN_LONGLONG_MAX LONG_LONG_MAX
#else
# ifdef LLONG_MAX
#  define ASN_LONGLONG_MAX LLONG_MAX
# else
#  ifdef __GNUC__
#   define ASN_LONGLONG_MAX __LONG_LONG_MAX__
#  endif
# endif
#endif

#define ASN_LONGLONG_FMT "%lld"
#define ASN_ULONGLONG_FMT "%llu"

#else
typedef long asn_longlong;
typedef unsigned long asn_ulonglong;
#define ASN_LONGLONG_MAX LONG_MAX
#define ASN_LONGLONG_FMT "%ld"
#define ASN_ULONGLONG_FMT "%lu"
#endif

/*
 * Returns 0 if it was possible to convert, -1 otherwise.
 * -1/EINVAL: Mandatory argument missing
 * -1/ERANGE: Value encoded is out of range for long representation
 * -1/ENOMEM: Memory allocation failed (in asn_long2INTEGER()).
 */
int asn_INTEGER2long(const INTEGER_t *i, long *l);
int asn_INTEGER2ulong(const INTEGER_t *i, unsigned long *l);
int asn_long2INTEGER(INTEGER_t *i, asn_longlong l);
int asn_ulong2INTEGER(INTEGER_t *i, asn_ulonglong l);

/*
 * Convert the integer value into the corresponding enumeration map entry.
 */
const asn_INTEGER_enum_map_t *INTEGER_map_value2enum(asn_INTEGER_specifics_t *specs, long value);

#ifdef __cplusplus
}
#endif

#endif	/* _INTEGER_H_ */
