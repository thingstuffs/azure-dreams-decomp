/* Rec_func_80036210_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:slus:func_80036210:arg0; 2 functions (slus 3); span 0x78.
 * Reached as a parameter in: func_80036210:arg0 (2), func_80036B10:arg2 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80036210_ARG0_H
#define REC_FUNC_80036210_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_80036210_arg0 {
    u8 pad_00[0x4C];
    s8 unk_4C;
    u8 pad_4D[0x1B];
    M2C_UNK * unk_68;
    u8 pad_6C[0x8];
    union { M2C_UNK * as_pm; void * as_pv; } unk_74;   /* read as M2C_UNK * by 1, void * by 1 */
} Rec_func_80036210_arg0;

#endif
