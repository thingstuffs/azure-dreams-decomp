/* Rec_D_80082EB0: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_80082EB0; 4 functions (dungeon 4); span 0xC.
 * Rooted at: D_80082EB0 (4)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_80082EB0_H
#define REC_D_80082EB0_H

#include "common.h"

typedef struct Rec_D_80082EB0 {
    union { void * as_pv; s32 as_s32; } unk_00;   /* read as void * by 2, s32 by 1 */
    void * unk_04;
    s32 unk_08;
} Rec_D_80082EB0;

#endif
