#include "common.h"

#include "engine/texture.h"

typedef struct AnimationChildEntry {
    u8 flags;
    u8 pad01[5];
    s16 id;
    void *source;
} AnimationChildEntry;

typedef struct AnimationChildSlot {
    u8 pad00[2];
    s16 type;
    AnimationChildEntry *entries;
} AnimationChildSlot;

typedef struct AnimationChildTable {
    u32 *words;
    s32 first_slot_word;
    AnimationChildSlot *end;
} AnimationChildTable;

/*
 * Walks type-two table slots and their 12-byte nodes through flag 0x80, replacing the value only
 * for nodes with flag 0x20 and the requested ID.
 */
void set_animation_child_source(SpriteFrameState *owner, void *value, s32 entry_id) {
    /* The sprite stores the resource address as a 32-bit game word. */
    AnimationChildTable **resource = (AnimationChildTable **)(unsigned long)(u32)owner->animation_resource;
    AnimationChildTable *table = *resource;
    AnimationChildSlot *slot = (AnimationChildSlot *)(table->words + table->first_slot_word);
    AnimationChildEntry *entry;
    AnimationChildEntry *current;

    if (slot < table->end) {
        do {
            if (slot->type == 2) {
                entry = slot->entries;
                current = entry;
                do {
                    if ((entry->flags & 0x20) && current->id == entry_id) {
                        current->source = value;
                    }
                    current++;
                } while (!((entry++)->flags & 0x80));
            }
            /* Fetch the bound through the current resource after updating the slot. */
            resource = (AnimationChildTable **)(unsigned long)(u32)owner->animation_resource;
            slot++;
        } while (slot < (*resource)->end);
    }
}
