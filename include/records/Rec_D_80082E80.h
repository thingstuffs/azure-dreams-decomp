/* Rec_D_80082E80: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_800848F8; 377 functions (dungeon 357, town 26); span 0xA9.
 * Rooted at: D_80082E80 (2), D_8008148C (1)
 * Reached as a parameter in: func_80172258:arg2 (2), func_80172620:arg2 (2), func_80172288:arg2 (2), func_80172CC0:arg2 (2), func_80172290:arg2 (2), func_801749A8:arg3 (2), +363 more
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_80082E80_H
#define REC_D_80082E80_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_D_80082E80 {
    s32 unk_00;
    union { s8 as_s8; u8 as_u8; } unk_04;   /* read as s8 by 55, u8 by 1 */
    union { s8 as_s8; u8 as_u8; } unk_05;   /* read as s8 by 7, u8 by 6 */
    union { s16 as_s16; u16 as_u16; } unk_06;   /* read as s16 by 5, u16 by 1 */
    s32 unk_08;
    union { struct { s32 v; } at00_s32; struct { s8 v; } at00_s8; struct { u8 v; } at00_u8; struct { u8 pad[0x1]; s8 v; } at01_s8; struct { u8 pad[0x1]; u8 v; } at01_u8; struct { u8 pad[0x2]; s8 v; } at02_s8; struct { u8 pad[0x2]; u8 v; } at02_u8; struct { u8 pad[0x3]; s8 v; } at03_s8; } unk_0C;   /* overlapping accesses */
    union { s16 as_s16; u16 as_u16; } unk_10;   /* read as s16 by 4, u16 by 2 */
    union { struct { s16 v; } at00_s16; struct { u16 v; } at00_u16; struct { u8 pad[0x1]; u8 v; } at01_u8; } unk_12;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { u16 v; } at00_u16; struct { u32 v; } at00_u32; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_14;   /* overlapping accesses */
    u16 unk_18;
    union { s16 as_s16; u16 as_u16; } unk_1A;   /* read as s16 by 3, u16 by 5 */
    union { struct { s16 v; } at00_s16; struct { s32 v; } at00_s32; struct { u16 v; } at00_u16; struct { u32 v; } at00_u32; struct { u8 pad[0x2]; s16 v; } at02_s16; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_1C;   /* overlapping accesses */
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    union { s8 as_s8; u8 as_u8; } unk_26;   /* read as s8 by 15, u8 by 1 */
    u8 pad_27[0x1];
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_28;   /* overlapping accesses */
    union { M2C_UNK * as_pm; u8 * as_pu8; void * as_pv; s32 as_s32; } unk_2C;   /* read as M2C_UNK * by 6, u8 * by 86, void * by 10, s32 by 3 */
    u8 pad_30[0x13];
    u8 unk_43;
    s8 unk_44;
    u8 pad_45[0x1B];
    union { void * as_pv; s32 as_s32; } unk_60;   /* read as void * by 4, s32 by 2 */
    u8 pad_64[0x6];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
    u8 pad_6E[0x1A];
    union { s16 as_s16; u16 as_u16; } unk_88;   /* read as s16 by 1, u16 by 2 */
    u16 unk_8A;
    u8 pad_8C[0x1C];
    u8 unk_A8;
} Rec_D_80082E80;

#endif
