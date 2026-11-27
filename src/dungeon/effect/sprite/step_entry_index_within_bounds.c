#include "shared/sprite_frame_state.h"
#include "dungeon/effect/sprite/linked_object_chain.h"

/* Refresh the entry value and handle index stepping and bounds. */
void step_entry_index_within_bounds(SpriteFrameState *entry, s16 *step, s32 lower, s32 upper)
{
    s32 pending_update;
    LinkedSpriteSource *source;
    s8 index;

    source = entry->source;
    entry->frame_entry = &source->frames[entry->unk_04];
    if (*step > 0) {
        entry->unk_04++;
    } else if (*step < 0) {
        entry->unk_04--;
    }

    index = entry->unk_04;
    if (index < (s16)lower) {
        pending_update = entry->flags | 0x4000;
        entry->unk_04 = lower;
        entry->flags = pending_update;
        return;
    }
    if (index > (s16)upper) {
        pending_update = entry->flags | 0x4000;
        entry->unk_04 = upper;
        entry->flags = pending_update;
        return;
    }
    entry->flags &= 0xBFFF;
}
