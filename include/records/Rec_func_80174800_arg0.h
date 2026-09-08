/* Rec_func_80174800_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80174800:arg0; 2 functions (dungeon 2); span 0xB2.
 * Reached as a parameter in: func_80174B20:arg0 (1), func_80174800:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80174800_ARG0_H
#define REC_FUNC_80174800_ARG0_H

#include "common.h"

typedef struct Rec_func_80174800_arg0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x48];
    void * unk_5C;
    u8 pad_60[0x36];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    void * unk_AC;
    s16 unk_B0;
} Rec_func_80174800_arg0;

#endif
