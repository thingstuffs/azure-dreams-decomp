/* Rec_func_800AA258_arg2: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800AA258:arg2; 18 functions (dungeon 18); span 0x30.
 * Reached as a parameter in: func_801736F4:arg2 (2), func_800AA6B4:arg2 (1), func_800AA888:arg2 (1), func_800D8C64:arg2 (1), func_80173AAC:arg2 (1), func_80173E00:arg2 (1), +11 more
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800AA258_ARG2_H
#define REC_FUNC_800AA258_ARG2_H

#include "common.h"

typedef struct Rec_func_800AA258_arg2 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u8 * unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    union { s8 as_s8; u8 as_u8; } unk_26;   /* read as s8 by 2, u8 by 1 */
    u8 pad_27[0x1];
    s32 unk_28;
    union { u8 * as_pu8; void * as_pv; s32 as_s32; } unk_2C;   /* read as u8 * by 1, void * by 5, s32 by 1 */
} Rec_func_800AA258_arg2;

#endif
