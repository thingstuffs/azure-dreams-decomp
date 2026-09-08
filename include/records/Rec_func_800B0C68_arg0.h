/* Rec_func_800B0C68_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_800B0C68:arg0; 3 functions (town 5); span 0xD0.
 * Reached as a parameter in: func_800B0C68:arg0 (2), func_800B1188:arg0 (2), func_800B0D0C:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800B0C68_ARG0_H
#define REC_FUNC_800B0C68_ARG0_H

#include "common.h"

typedef struct Rec_func_800B0C68_arg0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xC0];
    union { void * as_pv; s32 as_s32; } unk_CC;   /* read as void * by 4, s32 by 1 */
} Rec_func_800B0C68_arg0;

#endif
