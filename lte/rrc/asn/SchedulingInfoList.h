/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "EUTRA-RRC-Definitions"
 * 	found in "EUTRA-RRC-Definitions.asn"
 */

#ifndef	_SchedulingInfoList_H_
#define	_SchedulingInfoList_H_


#include <asn_application.h>

/* Including external dependencies */
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SchedulingInfo;

/* SchedulingInfoList */
typedef struct SchedulingInfoList {
	A_SEQUENCE_OF(struct SchedulingInfo) list;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SchedulingInfoList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SchedulingInfoList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SchedulingInfo.h"

#endif	/* _SchedulingInfoList_H_ */
#include <asn_internal.h>
