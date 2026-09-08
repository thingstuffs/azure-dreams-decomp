/* Rec_func_8008F2D4_arg1: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_8008F2D4:arg1; 2 functions (town 2); span 0x10.
 * Reached as a parameter in: func_8008F50C:arg1 (1), func_8008F520:arg1 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8008F2D4_ARG1_H
#define REC_FUNC_8008F2D4_ARG1_H

#include "common.h"

typedef struct Rec_func_8008F2D4_arg1 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
} Rec_func_8008F2D4_arg1;

#endif
