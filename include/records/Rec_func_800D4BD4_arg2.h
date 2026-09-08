/* Rec_func_800D4BD4_arg2: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800D4BD4:arg2; 3 functions (dungeon 3); span 0xC.
 * Reached as a parameter in: func_800D4BD4:arg2 (1), func_800D4DE8:arg1 (1), func_800D5294:arg1 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800D4BD4_ARG2_H
#define REC_FUNC_800D4BD4_ARG2_H

#include "common.h"

typedef struct Rec_func_800D4BD4_arg2 {
    u8 pad_00[0x2];
    union { s16 as_s16; u16 as_u16; } unk_02;   /* read as s16 by 2, u16 by 1 */
    u8 pad_04[0x2];
    union { s16 as_s16; u16 as_u16; } unk_06;   /* read as s16 by 2, u16 by 1 */
    u8 pad_08[0x2];
    union { s16 as_s16; u16 as_u16; } unk_0A;   /* read as s16 by 2, u16 by 1 */
} Rec_func_800D4BD4_arg2;

#endif
