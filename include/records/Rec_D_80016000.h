/* Rec_D_80016000: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_80126000; 130 functions (town 129, dungeon 7, slus 1); span 0x44.
 * Rooted at: D_80016000 (129), D_800DECF8 (2), D_80081484 (1), D_800DEA68 (1), D_800DEC50 (1), D_800DED70 (1)
 * Reached as a parameter in: func_800A6620:arg0 (1), func_800463EC:arg1 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_80016000_H
#define REC_D_80016000_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_D_80016000 {
    union { struct { void ** v; } at00_ppv; struct { void * v; } at00_pv; struct { s32 v; } at00_s32; struct { volatile s32 v; } at00_vs32; struct { u8 pad[0x2]; s16 v; } at02_s16; struct { u8 pad[0x3]; u8 v; } at03_u8; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { u32 v; } at00_u32; struct { u8 pad[0x2]; s16 v; } at02_s16; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; s16 v; } at02_s16; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
    u8 pad_18[0x4];
    union { void ** as_ppv; void * as_pv; } unk_1C;   /* read as void ** by 1, void * by 20 */
    void * unk_20;
    void * unk_24;
    M2C_UNK * unk_28;
    M2C_UNK * unk_2C;
    union { s32 * as_ps32; s32 as_s32; } unk_30;   /* read as s32 * by 1, s32 by 1 */
    M2C_UNK * unk_34;
    union { s8 * as_ps8; void * as_pv; s32 as_s32; } unk_38;   /* read as s8 * by 1, void * by 23, s32 by 2 */
    u8 pad_3C[0x4];
    union { u8 * as_pu8; void * as_pv; s32 as_s32; } unk_40;   /* read as u8 * by 1, void * by 5, s32 by 11 */
} Rec_D_80016000;

#endif
