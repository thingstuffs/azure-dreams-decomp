/* Rec_func_8009EE9C_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_8009EE9C:arg0; 3 functions (town 3); span 0xA4.
 * Reached as a parameter in: func_8009EE9C:arg0 (1), func_8009F1C0:arg0 (1), func_8009F48C:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8009EE9C_ARG0_H
#define REC_FUNC_8009EE9C_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_8009EE9C_arg0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x2];
    union { M2C_UNK * as_pm; void * as_pv; } unk_50;   /* read as M2C_UNK * by 1, void * by 1 */
    u8 pad_54[0x18];
    s16 unk_6C;
    u8 pad_6E[0x27];
    u8 unk_95;
    u8 pad_96[0xA];
    s32 unk_A0;
} Rec_func_8009EE9C_arg0;

#endif
