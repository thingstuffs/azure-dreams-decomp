/* Rec_D_80083160: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_80083160; 7 functions (dungeon 7); span 0x8D4.
 * Rooted at: D_80083160 (7)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_80083160_H
#define REC_D_80083160_H

#include "common.h"

typedef struct Rec_D_80083160 {
    union { u8 * as_pu8; void * as_pv; } unk_00;   /* read as u8 * by 1, void * by 3 */
    u8 pad_04[0xC4];
    union { s16 as_s16; u16 as_u16; } unk_C8;   /* read as s16 by 1, u16 by 1 */
    u8 pad_CA[0x806];
    void * unk_8D0;
} Rec_D_80083160;

#endif
