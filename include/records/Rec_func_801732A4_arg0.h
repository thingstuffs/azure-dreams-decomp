/* Rec_func_801732A4_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_801732A4:arg0; 2 functions (dungeon 2); span 0xBC.
 * Reached as a parameter in: func_80173CEC:arg0 (1), func_801732A4:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_801732A4_ARG0_H
#define REC_FUNC_801732A4_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_801732A4_arg0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x40];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    void * unk_A0;
    u8 pad_A4[0x2];
    s16 unk_A6;
    u8 pad_A8[0x2];
    u16 unk_AA;
    void * unk_AC;
    u8 pad_B0[0xB];
    s8 unk_BB;
} Rec_func_801732A4_arg0;

#endif
