/* Rec_D_800E3D7C: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_80174704; 537 functions (dungeon 569, town 73); span 0x12C.
 * Rooted at: D_800E3D7C (18), D_80083780 (6), D_80083498 (2), D_80174704 (1)
 * Reached as a parameter in: BODY_NAME:arg0 (5), func_800930F0:arg0 (2), func_800AA888:arg3 (2), func_800B3D10:arg2 (2), func_80170E54:arg3 (2), func_80172258:arg3 (2), +589 more
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_800E3D7C_H
#define REC_D_800E3D7C_H

#include "common.h"

typedef struct Rec_D_800E3D7C {
    union { struct { void * v; } at00_pv; struct { s32 v; } at00_s32; struct { u8 v; } at00_u8; struct { volatile s32 v; } at00_vs32; struct { u8 pad[0x1]; u8 v; } at01_u8; struct { u8 pad[0x2]; s16 v; } at02_s16; struct { u8 pad[0x2]; u16 v; } at02_u16; struct { u8 pad[0x2]; u8 v; } at02_u8; struct { u8 pad[0x3]; u8 v; } at03_u8; } unk_00;   /* overlapping accesses */
    union { struct { u16 * v; } at00_pu16; struct { s32 v; } at00_s32; struct { u8 pad[0x2]; s16 v; } at02_s16; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_04;   /* overlapping accesses */
    union { struct { void * v; } at00_pv; struct { s16 v; } at00_s16; struct { s32 v; } at00_s32; struct { u8 pad[0x1]; u8 v; } at01_u8; struct { u8 pad[0x2]; s16 v; } at02_s16; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_08;   /* overlapping accesses */
    union { s32 as_s32; u32 as_u32; volatile s32 as_vs32; } unk_0C;   /* read as s32 by 176, u32 by 1, volatile s32 by 1 */
    union { struct { s32 v; } at00_s32; struct { volatile s32 v; } at00_vs32; struct { u8 pad[0x1]; u8 v; } at01_u8; struct { u8 pad[0x2]; u8 v; } at02_u8; struct { u8 pad[0x3]; u8 v; } at03_u8; } unk_10;   /* overlapping accesses */
    union { s32 as_s32; u16 as_u16; u32 as_u32; } unk_14;   /* read as s32 by 219, u16 by 1, u32 by 4 */
    s32 unk_18;
    union { s32 as_s32; u32 as_u32; } unk_1C;   /* read as s32 by 125, u32 by 74 */
    s16 unk_20;
    u8 pad_22[0x2];
    union { struct { s16 v; } at00_s16; struct { u8 pad[0x1]; u8 v; } at01_u8; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 unk_27;
    u8 unk_28;
    u8 unk_29;
    union { s16 as_s16; u16 as_u16; } unk_2A;   /* read as s16 by 227, u16 by 8 */
    s16 unk_2C;
    u8 pad_2E[0x4];
    s16 unk_32;
    u8 pad_34[0xD];
    s8 unk_41;
    s8 unk_42;
    u8 unk_43;
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_44;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { s8 v; } at00_s8; struct { u8 v; } at00_u8; struct { u8 pad[0x1]; s8 v; } at01_s8; struct { u8 pad[0x1]; u8 v; } at01_u8; struct { u8 pad[0x3]; u8 v; } at03_u8; } unk_48;   /* overlapping accesses */
    union { void * as_pv; s32 as_s32; } unk_4C;   /* read as void * by 4, s32 by 3 */
    union { struct { u8 * v; } at00_pu8; struct { void * v; } at00_pv; struct { s32 v; } at00_s32; struct { u16 v; } at00_u16; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_50;   /* overlapping accesses */
    union { s32 as_s32; u32 as_u32; } unk_54;   /* read as s32 by 1, u32 by 1 */
    void * unk_58;
    s32 unk_5C;
    union { u8 * as_pu8; void * as_pv; s32 as_s32; } unk_60;   /* read as u8 * by 1, void * by 14, s32 by 6 */
    union { s16 as_s16; u16 as_u16; } unk_64;   /* read as s16 by 63, u16 by 3 */
    u8 pad_66[0x2];
    u8 unk_68;
    u8 unk_69;
    union { s16 as_s16; u16 as_u16; } unk_6A;   /* read as s16 by 4, u16 by 41 */
    u8 pad_6C[0x1];
    union { s8 as_s8; u8 as_u8; } unk_6D;   /* read as s8 by 74, u8 by 47 */
    u8 pad_6E[0x3];
    union { s8 as_s8; u8 as_u8; } unk_71;   /* read as s8 by 2, u8 by 50 */
    union { s8 as_s8; u8 as_u8; } unk_72;   /* read as s8 by 5, u8 by 1 */
    union { s8 as_s8; u8 as_u8; } unk_73;   /* read as s8 by 5, u8 by 1 */
    u8 pad_74[0x10];
    union { s8 as_s8; u8 as_u8; } unk_84;   /* read as s8 by 20, u8 by 7 */
    union { s8 as_s8; u8 as_u8; } unk_85;   /* read as s8 by 21, u8 by 6 */
    u8 pad_86[0x2];
    union { s16 as_s16; u16 as_u16; } unk_88;   /* read as s16 by 16, u16 by 11 */
    union { s16 as_s16; u16 as_u16; } unk_8A;   /* read as s16 by 3, u16 by 3 */
    u8 pad_8C[0xA];
    u16 unk_96;
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; s16 v; } at02_s16; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_A4;   /* overlapping accesses */
    u8 pad_A8[0x2];
    s16 unk_AA;
    u8 pad_AC[0x1C];
    void * unk_C8;
    u8 pad_CC[0x6];
    u8 unk_D2;
    u8 pad_D3[0x5];
    s32 unk_D8;
    u8 pad_DC[0x28];
    s32 unk_104;
    u8 pad_108[0x8];
    s32 unk_110;
    u8 pad_114[0x14];
    s32 unk_128;
} Rec_D_800E3D7C;

#endif
