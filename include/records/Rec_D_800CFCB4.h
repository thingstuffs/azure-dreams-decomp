/* Rec_D_800CFCB4: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_800CFCB4; 15 functions (town 15); span 0xAC.
 * Reached as a parameter in: func_8008F01C:arg0 (1), func_8008F0D4:arg0 (1), func_8008F104:arg0 (1), func_8008F27C:arg0 (1), func_8009567C:arg0 (1), func_8009B2C4:arg1 (1), +9 more
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_800CFCB4_H
#define REC_D_800CFCB4_H

#include "common.h"

typedef struct Rec_D_800CFCB4 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    void * unk_10;
    s8 unk_14;
    s8 unk_15;
    u8 pad_16[0x2];
    s32 unk_18;
    u8 pad_1C[0x4];
    void * unk_20;
    u8 pad_24[0x11];
    s8 unk_35;
    u8 pad_36[0x5];
    u8 unk_3B;
    u8 pad_3C[0xC];
    void * unk_48;
    s8 unk_4C;
    union { s8 as_s8; u8 as_u8; } unk_4D;   /* read as s8 by 1, u8 by 1 */
    u8 pad_4E[0x2];
    s32 unk_50;
    u8 pad_54[0x18];
    union { s16 as_s16; u16 as_u16; } unk_6C;   /* read as s16 by 1, u16 by 1 */
    u8 pad_6E[0x16];
    u16 unk_84;
    u16 unk_86;
    u8 pad_88[0xC];
    u8 unk_94;
    u8 unk_95;
    u8 pad_96[0x2];
    s8 * unk_98;
    u8 pad_9C[0x4];
    s32 unk_A0;
    s32 unk_A4;
    s32 unk_A8;
} Rec_D_800CFCB4;

#endif
