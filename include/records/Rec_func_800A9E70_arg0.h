/* Rec_func_800A9E70_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800A9E70:arg0; 62 functions (dungeon 62); span 0xB6.
 * Reached as a parameter in: func_80170E54:arg0 (2), func_800A9E70:arg0 (1), func_800AA258:arg0 (1), func_800AA5E4:arg0 (1), func_800AA6B4:arg0 (1), func_800AA888:arg0 (1), +55 more
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800A9E70_ARG0_H
#define REC_FUNC_800A9E70_ARG0_H

#include "common.h"

typedef struct Rec_func_800A9E70_arg0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x26];
    s32 unk_8C;
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; s16 v; } at02_s16; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_90;   /* overlapping accesses */
    s16 unk_94;
    union { s16 as_s16; u16 as_u16; } unk_96;   /* read as s16 by 12, u16 by 1 */
    u16 unk_98;
    union { s8 as_s8; u8 as_u8; } unk_9A;   /* read as s8 by 29, u8 by 28 */
    union { s8 as_s8; u8 as_u8; } unk_9B;   /* read as s8 by 31, u8 by 20 */
    union { s8 as_s8; u8 as_u8; } unk_9C;   /* read as s8 by 3, u8 by 1 */
    u8 pad_9D[0x1];
    union { s16 as_s16; u16 as_u16; } unk_9E;   /* read as s16 by 5, u16 by 1 */
    union { struct { void * v; } at00_pv; struct { s16 v; } at00_s16; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_A0;   /* overlapping accesses */
    s16 unk_A4;
    u8 unk_A6;
    u8 pad_A7[0x1];
    s16 unk_A8;
    s16 unk_AA;
    u8 unk_AC;
    u8 unk_AD;
    s16 unk_AE;
    u8 unk_B0;
    u8 pad_B1[0x2];
    u8 unk_B3;
    u8 unk_B4;
    u8 unk_B5;
} Rec_func_800A9E70_arg0;

#endif
