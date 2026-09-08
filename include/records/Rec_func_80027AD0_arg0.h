/* Rec_func_80027AD0_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80027AD0:arg0; 3 functions (dungeon 3); span 0x8C.
 * Reached as a parameter in: func_80027C94:arg0 (1), func_800280FC:arg0 (1), func_8002823C:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80027AD0_ARG0_H
#define REC_FUNC_80027AD0_ARG0_H

#include "common.h"

typedef struct Rec_func_80027AD0_arg0 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x38];
    s32 unk_40;
    u8 pad_44[0x8];
    s32 unk_4C;
    u8 pad_50[0x38];
    s32 unk_88;
} Rec_func_80027AD0_arg0;

#endif
