/* Rec_D_80081FDC: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_80081FDC; 4 functions (slus 4); span 0x64.
 * Reached as a parameter in: func_80033C1C:arg0 (1), func_80036B10:arg1 (1), func_80036D4C:arg1 (1), func_8003719C:arg1 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_80081FDC_H
#define REC_D_80081FDC_H

#include "common.h"

typedef struct Rec_D_80081FDC {
    s32 unk_00;
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x2];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} Rec_D_80081FDC;

#endif
