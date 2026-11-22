#include "common.h"
#include "shared/object_node.h"
#include "town/scene/collection.h"
#include "town/scene/object.h"
#include "town/data.h"
#include "town/devkit/old_minigame_imports.h"
/* Submit the linked value and retire the text node when the sequence finishes. */
void tick_timed_object_and_mark_complete(TownCollectionText *entry)
{
    s16 selector;
    u16 value;
    u16 next_value;
    TownCollectionSequence *sequence;

    sequence = entry->sequence;
    func_80058588(*entry->value, func_80071424(entry->text), entry->text);
    selector = entry->state;
    switch (selector) {
    case 0:
        value = entry->timer - 1;
        entry->timer = value;
        if ((value << 0x10) > 0) {
            return;
        }
        next_value = entry->state + 1;
        entry->flags &= 0xFFFD;
        entry->state = next_value;
        return;
    case 1:
        if (sequence->flags & TOWN_COLLECTION_FINISHED) {
            u16 *flags = &NODE_HEADER(entry)->flags;
            *flags |= 0x8000;
            /* This image stores to the absolute address of scene_object_flags. */
            *(s32 *)0x80084D5C = scene_object_flags | 0x8000;
        }
    }
}
