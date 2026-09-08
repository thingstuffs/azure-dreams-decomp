/* Rec_func_800243C4_arg1: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800243C4:arg1; 2 functions (dungeon 2); span 0xC.
 * Reached as a parameter in: func_800243C4:arg1 (1), func_80024ED4:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800243C4_ARG1_H
#define REC_FUNC_800243C4_ARG1_H

#include "common.h"

typedef struct Rec_func_800243C4_arg1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 as_s16; u16 as_u16; } unk_0A;   /* read as s16 by 1, u16 by 1 */
} Rec_func_800243C4_arg1;

#endif
