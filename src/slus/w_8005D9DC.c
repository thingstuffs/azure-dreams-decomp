#include "common.h"

/* Entry layout for the list pointed to by D_800799BC: word0 packs a
 * 0x80000000 "skip" flag, a 0x40000000 "stop" flag, and a 28-bit base
 * value; word1 is a count added to the base to form a range. */
typedef struct S_800799BC {
    u32 flags;
    u32 count;
} S_800799BC;

extern s32 D_80079980[3]; /* index 0 only used; array padding forces hi/lo codegen (matches sibling convention) */
extern S_800799BC *D_800799BC[3]; /* index 0 only used; array padding forces hi/lo codegen (matches D_80079980 convention) */

/* Returns whether the shifted value precedes or lies within an active list entry range. */
s32 func_8005D9DC(u32 value)
{
    S_800799BC *list;
    S_800799BC *entry;
    u32 skip_mask, stop_mask, base_mask;

    value = value << D_80079980[0];

    list = D_800799BC[0];
    if (list == 0) {
        return 0;
    }

    skip_mask = 0x80000000;
    stop_mask = 0x40000000;
    base_mask = 0x0FFFFFFF;

    entry = list;
    while (1) {
        u32 flags = entry->flags;

        if (!(flags & skip_mask)) {
            u32 base;

            if (flags & stop_mask) {
                goto retfalse;
            }

            base = flags & base_mask;
            if (base >= value) {
                return 1;
            }
            if (value < base + entry->count) {
                return 1;
            }
        }

        entry++;
    }
retfalse:
    return 0;
}
