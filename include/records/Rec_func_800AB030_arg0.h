/* Rec_func_800AB030_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_800AB030:arg0; 2 functions (town 2); span 0x92.
 * Reached as a parameter in: func_800AB030:arg0 (1), func_800AB5C0:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800AB030_ARG0_H
#define REC_FUNC_800AB030_ARG0_H

#include "common.h"

typedef struct Rec_func_800AB030_arg0 {
    u8 pad_00[0x50];
    void * unk_50;
    u8 pad_54[0x16];
    u16 unk_6A;
    u16 unk_6C;
    u8 pad_6E[0x22];
    s16 unk_90;
} Rec_func_800AB030_arg0;

#endif
