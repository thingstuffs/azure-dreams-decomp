/* Rec_func_80034F58_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:slus:func_80034F58:arg0; 2 functions (slus 3); span 0x14.
 * Reached as a parameter in: func_80035068:arg0 (2), func_80035888:arg4 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80034F58_ARG0_H
#define REC_FUNC_80034F58_ARG0_H

#include "common.h"

typedef struct Rec_func_80034F58_arg0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0xE];
    void * unk_10;
} Rec_func_80034F58_arg0;

#endif
