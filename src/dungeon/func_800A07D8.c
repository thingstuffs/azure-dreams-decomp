#include "modules/dungeon_engine_dungeon_util_fragment_c05e4.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern s32 lookup_item_category_mapped_value(u8, u8);
extern void clear_slot_and_update_linked_state(void *);
extern s32 play_sound_if_enabled(s32);
extern void place_item_at_valid_floor_position(u16, u16, s16, s32, void *);

/* Processes a target using the linked object's position, then decrements the shared count. */
void apply_item_effect_at_entity_position(void *object_context, void *target) {
    void *object;

    object = *(void **)((s8 *)object_context - 0x18);
    place_item_at_valid_floor_position(*(u16 *)((s8 *)object + 2) >> 6,
                  *(u16 *)((s8 *)object + 6) >> 6,
                  *(s16 *)((s8 *)object + 0xA),
                  lookup_item_category_mapped_value(*((u8 *)target + 1), *(u8 *)target), target);
    play_sound_if_enabled(0x50C);
    clear_slot_and_update_linked_state(target);
    g_dungeon_status.unk_0A--;
}
