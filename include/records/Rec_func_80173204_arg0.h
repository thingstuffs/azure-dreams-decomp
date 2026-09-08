/* Rec_func_80173204_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80173204:arg0; 2 functions (dungeon 2); span 0xA8.
 * Reached as a parameter in: func_80173A20:actor (1), func_80173204:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80173204_ARG0_H
#define REC_FUNC_80173204_ARG0_H

#include "common.h"

typedef struct Rec_func_80173204_arg0 {
    u8 pad_00[0x8C];
    union { u8 * as_pu8; void * as_pv; } unk_8C;   /* read as u8 * by 1, void * by 1 */
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
} Rec_func_80173204_arg0;

#endif
