/* Rec_func_80172CC0_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80172CC0:arg0; 3 functions (dungeon 3); span 0xAA.
 * Reached as a parameter in: func_80172CC0:arg0 (2), func_80173678:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80172CC0_ARG0_H
#define REC_FUNC_80172CC0_ARG0_H

#include "common.h"

typedef struct Rec_func_80172CC0_arg0 {
    u8 pad_00[0x8C];
    union { void * as_pv; s32 as_s32; } unk_8C;   /* read as void * by 1, s32 by 1 */
    u8 pad_90[0x6];
    union { s16 as_s16; u16 as_u16; } unk_96;   /* read as s16 by 1, u16 by 1 */
    u16 unk_98;
    union { s8 as_s8; u8 as_u8; } unk_9A;   /* read as s8 by 1, u8 by 1 */
    union { s8 as_s8; u8 as_u8; } unk_9B;   /* read as s8 by 1, u8 by 1 */
    u8 pad_9C[0xC];
    u16 unk_A8;
} Rec_func_80172CC0_arg0;

#endif
