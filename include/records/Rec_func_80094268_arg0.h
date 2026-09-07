/* Rec_func_80094268_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80094268:arg0; 122 functions (town 116, dungeon 12); span 0xA4.
 * Reached as a parameter in: func_800942B0:arg0 (2), func_800943B8:arg0 (2), func_8009455C:arg0 (2), func_80099CE0:arg0 (2), func_80099E70:arg0 (2), func_8009A1A4:arg0 (2), +113 more
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80094268_ARG0_H
#define REC_FUNC_80094268_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_80094268_arg0 {
    union { M2C_UNK * as_pm; void * as_pv; } unk_00;   /* read as M2C_UNK * by 16, void * by 1 */
    union { M2C_UNK * as_pm; void ** as_ppv; void * as_pv; } unk_04;   /* read as M2C_UNK * by 16, void ** by 1, void * by 1 */
    u8 pad_08[0x2];
    union { s16 as_s16; u16 as_u16; } unk_0A;   /* read as s16 by 27, u16 by 9 */
    u8 pad_0C[0x2];
    u16 unk_0E;
    union { s16 as_s16; u16 as_u16; } unk_10;   /* read as s16 by 8, u16 by 1 */
    u8 pad_12[0x2];
    s8 unk_14;
    s8 unk_15;
    s16 unk_16;
    u8 pad_18[0x14];
    void * unk_2C;
    u16 unk_30;
    u16 unk_32;
    union { s16 as_s16; u16 as_u16; } unk_34;   /* read as s16 by 2, u16 by 1 */
    u8 pad_36[0x8];
    union { s16 as_s16; u16 as_u16; } unk_3E;   /* read as s16 by 4, u16 by 2 */
    s32 unk_40;
    void * unk_44;
    u8 pad_48[0x4];
    u8 unk_4C;
    u8 unk_4D;
    u8 pad_4E[0x1];
    u8 unk_4F;
    union { M2C_UNK * as_pm; void * as_pv; s32 as_s32; } unk_50;   /* read as M2C_UNK * by 12, void * by 2, s32 by 1 */
    M2C_UNK * unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
    u8 pad_64[0x8];
    union { s16 as_s16; u16 as_u16; } unk_6C;   /* read as s16 by 14, u16 by 17 */
    u16 unk_6E;
    u8 pad_70[0x2];
    union { s16 as_s16; u16 as_u16; } unk_72;   /* read as s16 by 9, u16 by 2 */
    u8 pad_74[0x4];
    s32 * unk_78;
    union { M2C_UNK ** as_ppm; s32 ** as_pps32; s32 * as_ps32; void * as_pv; } unk_7C;   /* read as M2C_UNK ** by 1, s32 ** by 1, s32 * by 1, void * by 2 */
    void * unk_80;
    union { s16 as_s16; u16 as_u16; } unk_84;   /* read as s16 by 3, u16 by 2 */
    union { s16 as_s16; u16 as_u16; } unk_86;   /* read as s16 by 2, u16 by 2 */
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    s16 unk_8E;
    union { s16 as_s16; u16 as_u16; } unk_90;   /* read as s16 by 2, u16 by 4 */
    u8 unk_92;
    s8 unk_93;
    s8 unk_94;
    u8 unk_95;
    union { s8 as_s8; u8 as_u8; } unk_96;   /* read as s8 by 1, u8 by 4 */
    u8 pad_97[0x1];
    s8 * unk_98;
    u8 pad_9C[0x4];
    s32 unk_A0;
} Rec_func_80094268_arg0;

#endif
