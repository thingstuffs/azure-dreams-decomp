/* Rec_func_80026CF0_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80026CF0:arg0; 2 functions (main 1, dungeon 1); span 0x14.
 * Reached as a parameter in: func_80026E90:arg0 (1), func_80026CF0:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80026CF0_ARG0_H
#define REC_FUNC_80026CF0_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_80026CF0_arg0 {
    s32 unk_00;
    u8 pad_04[0x8];
    M2C_UNK ** unk_0C;
    s32 * unk_10;
} Rec_func_80026CF0_arg0;

#endif
