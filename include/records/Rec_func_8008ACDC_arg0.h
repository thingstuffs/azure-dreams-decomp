/* Rec_func_8008ACDC_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_8008ACDC:arg0; 27 functions (dungeon 27); span 0x128.
 * Reached as a parameter in: func_8008C4C8:arg0 (1), func_8008ACDC:arg0 (1), func_8008B870:arg0 (1), func_8008C468:arg0 (1), func_8008C514:arg0 (1), func_8008CAA0:arg0 (1), +21 more
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8008ACDC_ARG0_H
#define REC_FUNC_8008ACDC_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_8008ACDC_arg0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x34];
    s32 unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x16];
    s16 unk_8A;
    union { M2C_UNK * as_pm; void * as_pv; s32 as_s32; } unk_8C;   /* read as M2C_UNK * by 4, void * by 3, s32 by 12 */
    u8 pad_90[0x6];
    union { s16 as_s16; u16 as_u16; } unk_96;   /* read as s16 by 11, u16 by 2 */
    u16 unk_98;
    union { s8 as_s8; u8 as_u8; } unk_9A;   /* read as s8 by 9, u8 by 7 */
    union { s8 as_s8; u8 as_u8; } unk_9B;   /* read as s8 by 12, u8 by 7 */
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
    union { s16 as_s16; u16 as_u16; } unk_A4;   /* read as s16 by 1, u16 by 1 */
    u8 pad_A6[0x16];
    void * unk_BC;
    u8 pad_C0[0x8];
    s32 unk_C8;
    u8 pad_CC[0x34];
    s16 unk_100;
    u8 pad_102[0x2];
    s32 unk_104;
    u8 pad_108[0x4];
    u16 unk_10C;
    u8 pad_10E[0x2];
    s32 unk_110;
    u8 pad_114[0x6];
    u16 unk_11A;
    u8 pad_11C[0x8];
    s32 unk_124;
} Rec_func_8008ACDC_arg0;

#endif
