/* Rec_func_8009431C_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_8009431C:arg0; 3 functions (town 2, dungeon 1); span 0x30.
 * Reached as a parameter in: func_80090A74:arg0 (1), func_800A5638:arg0 (1), func_8009431C:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8009431C_ARG0_H
#define REC_FUNC_8009431C_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_8009431C_arg0 {
    union { M2C_UNK * as_pm; M2C_UNK (*as_x78b360)(void *, void *, M2C_UNK); } unk_00;   /* read as M2C_UNK * by 1, M2C_UNK (*)(void *, void *, M2C_UNK) by 1 */
    u8 pad_04[0x6];
    s16 unk_0A;
    u8 pad_0C[0x20];
    s32 unk_2C;
} Rec_func_8009431C_arg0;

#endif
