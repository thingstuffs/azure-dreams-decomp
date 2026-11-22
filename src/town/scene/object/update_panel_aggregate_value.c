#include "common.h"
#include "shared/object_node.h"
#include "town/scene/collection.h"
#include "town/scene/object.h"
#include "town/data.h"
#include "town/devkit/old_minigame_imports.h"

extern s16 D_80530000[];

/* Waits for a delay, passes the eight-entry sum to func_80058588, and handles a linked cleanup flag. */
void update_panel_aggregate_value(TownCollectionText *entry) {
    s16 *value_ptr;
    s16 current_state;
    s32 remaining;
    s32 total;
    u16 countdown;
    u16 next_state;
    u16 flags;
    TownCollectionSequence *sequence;

    total = 0;
    remaining = 7;
    value_ptr = &D_80530000[0x333];
    sequence = entry->sequence;
    do {
        total += *value_ptr;
        value_ptr -= 1;
        remaining -= 1;
    } while (remaining >= 0);
    current_state = entry->state;
    switch (current_state) {
    case 0:
        countdown = entry->timer - 1;
        entry->timer = countdown;
        if ((countdown << 0x10) > 0) {
            return;
        }
        next_state = entry->state;
        flags = entry->flags;
        next_state += 1;
        flags &= 0xFFFD;
        entry->flags = flags;
        entry->state = next_state;
        return;
    case 1:
        func_80058588(total, func_80071424(entry->text), entry->text);
        if (sequence->flags & TOWN_COLLECTION_FINISHED) {
            u16 *node_flags = &NODE_HEADER(entry)->flags;
            *node_flags |= 0x8000;
            scene_object_flags |= 0x8000;
        }
        return;
    default:
        return;
    }
}
/* MECHANISM: The page-base symbol plus &D_80530000[0x333] emits retail's entry lui/addiu in v1.
   A noreturn tail ABI and explicit label order preserve default/state-0/state-1 CFG and jump slots.
   Split state/flags RMW temporaries establish the retail v1/v0 lifetimes and flags/state store order. */
