#include "common.h"
#include "engine/texture.h"

/* D_80083D08: array of 6 8-byte entries; field flags4 (offset 4) is a status/flags
 * short whose bit0 is cleared here. Layout reconciled with siblings that access the
 * same array (bind_sprite_resource_slot_record / mark_sprite_resources_for_purge / find_free_sprite_resource_slot / find_sprite_resource_slot_by_id). */
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 flags4;
    s16 id6;
} S_80048224;

extern S_80048224 sprite_resource_slots[6];

/* Clear flag bit 0 in the slot matching slot_id and return 1 if found, else 0. */
s32 retain_sprite_resource_in_cache(s16 slot_id) {
    s32 slot_index = find_sprite_resource_slot_by_id(slot_id);

    if (slot_index != -1) {
        sprite_resource_slots[slot_index].flags4 &= ~1;
        return 1;
    }
    return 0;
}
