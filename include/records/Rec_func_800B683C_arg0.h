/* Rec_func_800B683C_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_800B683C:arg0; 4 functions (town 5); span 0xE0.
 * Reached as a parameter in: func_800B683C:arg0 (2), func_800B68C8:arg0 (1), func_800B6E3C:arg0 (1), func_800B6F54:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800B683C_ARG0_H
#define REC_FUNC_800B683C_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_800B683C_arg0 {
    M2C_UNK * unk_00;
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x80];
    void * unk_98;
    u8 pad_9C[0x34];
    s32 unk_D0;
    s32 unk_D4;
    u8 pad_D8[0x4];
    s32 unk_DC;
} Rec_func_800B683C_arg0;

#endif
