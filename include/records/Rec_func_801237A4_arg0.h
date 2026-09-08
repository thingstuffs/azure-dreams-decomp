/* Rec_func_801237A4_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_801237A4:arg0; 6 functions (town 4, dungeon 2); span 0x5C.
 * Reached as a parameter in: func_80125DDC:arg0 (1), func_80125FB8:arg0 (1), func_801260E8:arg0 (1), func_80126620:arg0 (1), func_801237A4:arg0 (1), func_801237E8:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_801237A4_ARG0_H
#define REC_FUNC_801237A4_ARG0_H

#include "common.h"

typedef struct Rec_func_801237A4_arg0 {
    u8 pad_00[0x4];
    union { s16 as_s16; u16 as_u16; } unk_04;   /* read as s16 by 1, u16 by 3 */
    s16 unk_06;
    s16 unk_08;
    u8 unk_0A;
    u8 unk_0B;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
    u8 unk_11;
    u8 unk_12;
    u8 unk_13;
    u8 unk_14;
    u8 unk_15;
    u8 unk_16;
    u8 unk_17;
    u8 unk_18;
    u8 pad_19[0x3F];
    void * unk_58;
} Rec_func_801237A4_arg0;

#endif
