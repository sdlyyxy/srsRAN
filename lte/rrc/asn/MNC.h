/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 */

#ifndef	_MNC_H_
#define	_MNC_H_


#include <asn_application.h>

/* Including external dependencies */
#include "MCC-MNC-Digit.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MNC */
typedef struct MNC {
	A_SEQUENCE_OF(MCC_MNC_Digit_t) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} MNC_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_MNC;

#ifdef __cplusplus
}
#endif

#endif	/* _MNC_H_ */
#include <asn_internal.h>
