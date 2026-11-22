#include "common.h"
#include "town/player.h"
#include "town/scene/collision.h"

typedef struct S_80095840_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x1A];
    union { void * s; s32 u; } unk_2C;   /* accessed as both */
} S_80095840_0;   /* out in select_adjacent_source_entry */

/*
 * Uses the angle table to select the source or an available alternate slot, rejecting entry types
 * one and three. Stores the selected pointer and returns two for the source, one for an alternate,
 * or zero with a cleared pointer.
 */
s32 select_adjacent_source_entry(void *destination, ColliderView *candidates)
{
    S_80095840_0 *result;
    s32 selection;
    s32 offset;
    s32 initial_angle;
    ColliderView *entry;
    ColliderView *selected;

    result = destination;
    initial_angle = result->unk_10;
    selection = initial_angle + 0x100;
    if (selection >= 0) {
        selection >>= 7;
        offset = 0x800D0000;
    } else {
        selection = (initial_angle + 0x2FF) >> 7;
        offset = 0x800D0000;
    }

    /* The eight face IDs at 0x800D0484 use -1 for diagonal directions. */
    offset += 0x484;
    selection &= 0x1C;
    selection += offset;
    offset = *(s32 *)selection;
    if (offset != -1) {
        if (candidates->pending_flags[0] != 0) {
            selected = candidates->slots[0];
            candidates->selected_entry = selected;
            candidates->selected_face = 0;
            entry = candidates->selected_entry;
            offset = selected->mode;
            if ((offset == 1) || (offset == 3)) {
                result->unk_2C.u = 0;
                selection = 0;
                return selection;
            }
            selection = 2;
            result->unk_2C.s = entry;
            return selection;
        }

        if (candidates->pending_flags[offset] != 0) {
            selected = candidates->slots[offset];
            candidates->selected_entry = selected;
            candidates->selected_face = offset;
            entry = candidates->selected_entry;
            offset = entry->mode;
            if ((offset != 1) && (offset != 3)) {
                selection = 1;
                result->unk_2C.s = entry;
                return selection;
            }
        }
    }
    result->unk_2C.u = 0;
    selection = 0;
    return selection;
}
