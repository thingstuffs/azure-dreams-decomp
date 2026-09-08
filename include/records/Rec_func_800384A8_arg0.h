/* Rec_func_800384A8_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:slus:func_800384A8:arg0; 2 functions (slus 2); span 0x14.
 * Reached as a parameter in: func_800384A8:arg0 (1), func_80038538:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800384A8_ARG0_H
#define REC_FUNC_800384A8_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_800384A8_arg0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} Rec_func_800384A8_arg0;

#endif
