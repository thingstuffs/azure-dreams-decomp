/* Rec_func_8008D024_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_8008D024:arg0; 6 functions (dungeon 6); span 0x122.
 * Reached as a parameter in: func_8008D024:arg0 (1), func_8008D330:arg0 (1), func_8008D9F0:arg0 (1), func_80090C10:arg0 (1), func_80091920:arg0 (1), func_800956B8:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8008D024_ARG0_H
#define REC_FUNC_8008D024_ARG0_H

#include "common.h"

typedef struct Rec_func_8008D024_arg0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x40];
    void * unk_60;
    u8 pad_64[0x28];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    union { s8 as_s8; u8 as_u8; } unk_9B;   /* read as s8 by 4, u8 by 1 */
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x8];
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x8];
    void * unk_BC;
    u8 pad_C0[0x8];
    void * unk_C8;
    u8 pad_CC[0x38];
    void * unk_104;
    u8 pad_108[0x8];
    void * unk_110;
    u8 pad_114[0xC];
    s16 unk_120;
} Rec_func_8008D024_arg0;

#endif
