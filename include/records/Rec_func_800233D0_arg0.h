/* Rec_func_800233D0_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:main:func_800233D0:arg0; 2 functions (main 3); span 0x1A8.
 * Reached as a parameter in: func_80023600:arg0 (2), func_800233D0:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800233D0_ARG0_H
#define REC_FUNC_800233D0_ARG0_H

#include "common.h"

typedef struct Rec_func_800233D0_arg0 {
    u8 pad_00[0x80];
    s32 unk_80;
    s32 unk_84;
    u8 pad_88[0x118];
    void * unk_1A0;
    void * unk_1A4;
} Rec_func_800233D0_arg0;

#endif
