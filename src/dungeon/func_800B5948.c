#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[0x10];
    s16 unk10;
    s16 unk12;
    u8 pad14[6];
    u16 unk1A;
    s16 unk1C;
    u16 unk1E;
    s16 unk20;
} Func800B5948Object;

extern void update_map_cell_flags_with_item_limit(s16, s16, s32);
extern void clear_slot_and_detach_entity(s16);

/* Updates the object's countdown and triggers an effect when it expires. */
void update_timed_tile_effect(Func800B5948Object *object, s32 unused, Func800B5948Object *related_object) {
    u16 ticks_left;

    if (g_dungeon_status.flags & 0x10) {
        ticks_left = object->unk1E - 1;
        object->unk1E = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            if (object->unk1C == 1) {
                update_map_cell_flags_with_item_limit(object->unk10, object->unk12, 2);
            } else {
                update_map_cell_flags_with_item_limit(object->unk10, object->unk12, 0x10);
            }
            clear_slot_and_detach_entity(object->unk20);
            return;
        }
    }
    related_object->unk1A = related_object->unk1A + 0x40;
}
