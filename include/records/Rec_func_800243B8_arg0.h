/* Rec_func_800243B8_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800243B8:arg0; 2 functions (dungeon 2); span 0x16.
 * Reached as a parameter in: func_800243B8:arg0 (1), func_80024660:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800243B8_ARG0_H
#define REC_FUNC_800243B8_ARG0_H

#include "common.h"

typedef struct Rec_func_800243B8_arg0 {
    void * unk_00;
    u16 * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    s16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    union { s16 as_s16; u16 as_u16; } unk_12;   /* read as s16 by 1, u16 by 1 */
    s16 unk_14;
} Rec_func_800243B8_arg0;

#endif
