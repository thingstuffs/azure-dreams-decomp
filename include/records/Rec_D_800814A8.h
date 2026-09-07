/* Rec_D_800814A8: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_800814A8; 106 functions (dungeon 106); span 0x10E.
 * Rooted at: D_800814A8 (105)
 * Reached as a parameter in: func_800A0134:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_800814A8_H
#define REC_D_800814A8_H

#include "common.h"

typedef struct Rec_D_800814A8 {
    union { void * as_pv; s32 as_s32; } unk_00;   /* read as void * by 2, s32 by 2 */
    u8 pad_04[0x26];
    union { s16 as_s16; u16 as_u16; } unk_2A;   /* read as s16 by 3, u16 by 10 */
    u8 pad_2C[0x2C];
    union { u8 * as_pu8; void * as_pv; s32 as_s32; } unk_58;   /* read as u8 * by 2, void * by 66, s32 by 15 */
    u8 pad_5C[0xE];
    s16 unk_6A;
    u8 pad_6C[0x1C];
    union { s16 as_s16; u16 as_u16; } unk_88;   /* read as s16 by 1, u16 by 1 */
    u8 pad_8A[0x10];
    u8 unk_9A;
    u8 pad_9B[0xB];
    u16 unk_A6;
    u8 unk_A8;
    u8 pad_A9[0x3];
    void * unk_AC;
    void * unk_B0;
    u8 pad_B4[0x40];
    s32 unk_F4;
    u8 pad_F8[0xA];
    u8 unk_102;
    u8 pad_103[0x9];
    u16 unk_10C;
} Rec_D_800814A8;

#endif
