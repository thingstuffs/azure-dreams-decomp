/* Rec_func_800AD058_arg2: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800AD058:arg2; 4 functions (dungeon 4); span 0x30.
 * Reached as a parameter in: func_801736EC:arg2 (1), func_80174BF8:arg2 (1), func_80174D48:arg1 (1), func_8017390C:arg2 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800AD058_ARG2_H
#define REC_FUNC_800AD058_ARG2_H

#include "common.h"

typedef struct Rec_func_800AD058_arg2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} Rec_func_800AD058_arg2;

#endif
