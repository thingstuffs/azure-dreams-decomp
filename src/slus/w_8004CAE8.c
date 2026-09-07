#include "common.h"

typedef struct S_8004CAE8 {
    /* 0x0 */ u8 flags;   /* bit 0x20 = enabled/active entry, bit 0x80 = last entry */
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} S_8004CAE8; /* size 0xC (12) */

/* Walk a fixed-stride (12-byte) array of flagged records looking for the first
 * one with the "active" bit (0x20) set whose id field matches a1. Stops after
 * the record flagged 0x80 (marks the last entry). Returns a pointer to the
 * matching record, or NULL if none found. */
S_8004CAE8 *func_8004CAE8(S_8004CAE8 *a0, u32 a1) {
    for (;;) {
        if ((a0->flags & 0x20) && a0->id == a1) {
            return a0;
        }
        if (a0->flags & 0x80) {
            break;
        }
        a0 = (S_8004CAE8 *)((u8 *)a0 + 0xC);
    }
    return (S_8004CAE8 *)0;
}
