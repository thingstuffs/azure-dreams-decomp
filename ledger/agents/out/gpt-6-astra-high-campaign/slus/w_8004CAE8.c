#include "common.h"

typedef struct S_8004CAE8 {
    /* 0x0 */ u8 flags;   /* bit 0x20 = enabled/active entry, bit 0x80 = last entry */
    /* 0x1 */ u8 pad1[5];
    /* 0x6 */ u16 id;
    /* 0x8 */ u8 pad2[4];
} S_8004CAE8; /* size 0xC (12) */

/* Returns the first active record with the requested ID, or NULL at the end of the array. */
S_8004CAE8 *func_8004CAE8(S_8004CAE8 *entry, u32 target_id) {
    for (;;) {
        if ((entry->flags & 0x20) && entry->id == target_id) {
            return entry;
        }
        if (entry->flags & 0x80) {
            break;
        }
        entry = (S_8004CAE8 *)((u8 *)entry + 0xC);
    }
    return (S_8004CAE8 *)0;
}
