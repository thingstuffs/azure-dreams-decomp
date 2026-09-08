/* Rec_func_800A0668_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_800A0668:arg0; 3 functions (town 3); span 0x9C.
 * Reached as a parameter in: func_800A0668:arg0 (1), func_800A0E3C:arg0 (1), func_800A0F10:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800A0668_ARG0_H
#define REC_FUNC_800A0668_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_800A0668_arg0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
    u8 pad_6E[0x4];
    u16 unk_72;
    u8 pad_74[0x21];
    u8 unk_95;
    u8 pad_96[0x2];
    void * unk_98;
} Rec_func_800A0668_arg0;

#endif
