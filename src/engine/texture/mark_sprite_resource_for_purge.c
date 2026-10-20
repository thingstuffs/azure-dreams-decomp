#include "common.h"

typedef struct {
    s32 flag;
    u16 status;
    u16 pad6;
} S_80083D08;

extern S_80083D08 sprite_resource_slots[6];

extern s32 find_sprite_resource_slot_by_id(s32 slot_id);

/* Set status bit 0 for the entry matching the lookup key, if found. */
void mark_sprite_resource_for_purge(s16 lookup_key) {
    s32 entry_index = find_sprite_resource_slot_by_id(lookup_key);

    if (entry_index != -1) {
        sprite_resource_slots[entry_index].status = sprite_resource_slots[entry_index].status | 1;
    }
}
