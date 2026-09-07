#include "common.h"

/* Left-shifts a0 by the global shift amount, then scans the list at
 * D_800799BC for an entry whose masked base value is >= the shifted a0,
 * or whose [base, base+count) range contains it, returning 1 if found.
 * Entries with the skip bit set are ignored; an entry with the stop bit
 * set (and not skip), or reaching a NULL list, terminates the scan with 0. */
/* Entry layout for the list pointed to by D_800799BC: word0 packs a
 * 0x80000000 "skip" flag, a 0x40000000 "stop" flag, and a 28-bit base
 * value; word1 is a count added to the base to form a range. */
typedef struct S_800799BC {
    u32 flags;
    u32 count;
} S_800799BC;

extern s32 D_80079980[3]; /* index 0 only used; array padding forces hi/lo codegen (matches sibling convention) */
extern S_800799BC *D_800799BC[3]; /* index 0 only used; array padding forces hi/lo codegen (matches D_80079980 convention) */

s32 func_8005D9DC(u32 a0)
{
    S_800799BC *list;
    S_800799BC *entry;
    u32 skipMask, stopMask, baseMask;

    a0 = a0 << D_80079980[0];

    list = D_800799BC[0];
    if (list == 0) {
        return 0;
    }

    skipMask = 0x80000000;
    stopMask = 0x40000000;
    baseMask = 0x0FFFFFFF;

    entry = list;
    while (1) {
        u32 flags = entry->flags;

        if (!(flags & skipMask)) {
            u32 base;

            if (flags & stopMask) {
                goto retfalse;
            }

            base = flags & baseMask;
            if (base >= a0) {
                return 1;
            }
            if (a0 < base + entry->count) {
                return 1;
            }
        }

        entry++;
    }
retfalse:
    return 0;
}
