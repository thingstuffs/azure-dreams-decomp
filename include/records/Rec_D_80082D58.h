/* Rec_D_80082D58: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_80082D58; 19 functions (town 16, slus 2, dungeon 1); span 0xB0.
 * Rooted at: D_80082D58 (1)
 * Reached as a parameter in: func_80094A38:arg1 (1), func_8009B148:arg0 (1), func_8009B9BC:arg0 (1), func_8009D20C:arg0 (1), func_8009DD40:arg0 (1), func_8009ED7C:arg0 (1), +12 more
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_80082D58_H
#define REC_D_80082D58_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_D_80082D58 {
    s32 unk_00;
    s8 unk_04;
    u8 pad_05[0xB];
    s16 unk_10;
    u8 pad_12[0xA];
    s32 unk_1C;
    u8 pad_20[0x2D];
    u8 unk_4D;
    u8 pad_4E[0x2];
    union { M2C_UNK * as_pm; M2C_UNK (*as_x151a23)(void *, void *, M2C_UNK, M2C_UNK); M2C_UNK (*as_xcdccad)(void *, void *, M2C_UNK, void *); } unk_50;   /* read as M2C_UNK * by 2, M2C_UNK (*)(void *, void *, M2C_UNK, M2C_UNK) by 2, M2C_UNK (*)(void *, void *, M2C_UNK, void *) by 1 */
    u8 pad_54[0x4];
    void * unk_58;
    u8 pad_5C[0x4];
    s32 unk_60;
    s16 unk_64;
    s16 unk_66;
    s16 unk_68;
    u8 pad_6A[0x2];
    union { s16 as_s16; u16 as_u16; } unk_6C;   /* read as s16 by 1, u16 by 2 */
    u8 pad_6E[0x4];
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    s32 * unk_78;
    u8 pad_7C[0x8];
    u16 unk_84;
    u16 unk_86;
    u8 pad_88[0x8];
    union { s16 as_s16; u16 as_u16; } unk_90;   /* read as s16 by 2, u16 by 1 */
    u8 pad_92[0x5];
    s8 unk_97;
    union { s8 * as_ps8; u8 * as_pu8; void * as_pv; } unk_98;   /* read as s8 * by 3, u8 * by 2, void * by 1 */
    void * unk_9C;
    s32 unk_A0;
    u8 pad_A4[0x8];
    s32 unk_AC;
} Rec_D_80082D58;

#endif
