/* Rec_func_800C9F34_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800C9F34:arg0; 3 functions (dungeon 3); span 0x9C.
 * Reached as a parameter in: func_800C9F34:arg0 (1), func_800CA0DC:arg0 (1), func_800CAA94:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800C9F34_ARG0_H
#define REC_FUNC_800C9F34_ARG0_H

#include "common.h"

typedef struct Rec_func_800C9F34_arg0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x6C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    union { s8 as_s8; u8 as_u8; } unk_9A;   /* read as s8 by 2, u8 by 1 */
    s8 unk_9B;
} Rec_func_800C9F34_arg0;

#endif
