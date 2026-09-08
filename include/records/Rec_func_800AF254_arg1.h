/* Rec_func_800AF254_arg1: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_800AF254:arg1; 7 functions (town 9); span 0xAC.
 * Reached as a parameter in: func_800AF36C:arg0 (2), func_800AF8B0:arg0 (2), func_800AF674:arg0 (1), func_800AF860:arg0 (1), func_800AFD00:arg0 (1), func_800AFD5C:arg0 (1), +1 more
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800AF254_ARG1_H
#define REC_FUNC_800AF254_ARG1_H

#include "common.h"

typedef struct Rec_func_800AF254_arg1 {
    void * unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    u8 pad_14[0x4];
    s32 unk_18;
    u8 pad_1C[0x80];
    void * unk_9C;
    u8 pad_A0[0x8];
    union { void * as_pv; s32 as_s32; } unk_A8;   /* read as void * by 3, s32 by 2 */
} Rec_func_800AF254_arg1;

#endif
