/* Rec_func_800AB014_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_800AB014:arg0; 2 functions (town 2); span 0x92.
 * Reached as a parameter in: func_800AB014:arg0 (1), func_800AB708:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800AB014_ARG0_H
#define REC_FUNC_800AB014_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_800AB014_arg0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0x4];
    union { s16 as_s16; u16 as_u16; } unk_72;   /* read as s16 by 1, u16 by 1 */
    u8 pad_74[0x1C];
    s16 unk_90;
} Rec_func_800AB014_arg0;

#endif
