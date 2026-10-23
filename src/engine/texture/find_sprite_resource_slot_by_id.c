#include "common.h"
#include "engine/texture.h"

/* struct element of D_80083D08: only the s16 field at offset 6 is read by this function */
typedef struct {
    u8 unk0[6];
    s16 unk6;
} S_80047BC0;

extern S_80047BC0 sprite_resource_slots[6];

/* Searches six sprite_resource_slots for the requested ID and returns its index, or -1 when absent. */
s32 find_sprite_resource_slot_by_id(s32 slot_id) {
    S_80047BC0 *slot;
    s32 match_index = -1;
    s32 slot_index = 0;
    slot = sprite_resource_slots;

    for (; slot_index < 6; slot_index++, slot++) {
        if (slot->unk6 == slot_id) {
            match_index = slot_index;
            break;
        }
    }
    return match_index;
}
