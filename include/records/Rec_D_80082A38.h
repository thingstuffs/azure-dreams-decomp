/* Rec_D_80082A38: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_80082A38; 5 functions (slus 5); span 0x10C.
 * Reached as a parameter in: func_80034EB4:arg0 (1), func_80034F88:arg0 (1), func_80034FD0:arg0 (1), func_80034FE4:arg0 (1), func_80035060:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_80082A38_H
#define REC_D_80082A38_H

#include "common.h"

typedef struct Rec_D_80082A38 {
    s8 unk_00;
    s8 unk_01;
    u8 pad_02[0x1];
    s8 unk_03;
    u8 pad_04[0xC];
    s32 unk_10;
    u8 pad_14[0x20];
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x60];
    s32 unk_9C;
    u8 pad_A0[0x68];
    s32 unk_108;
} Rec_D_80082A38;

#endif
