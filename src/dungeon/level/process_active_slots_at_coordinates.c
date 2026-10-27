#include "common.h"

typedef struct {
    s8 unused0;
    u8 active;
    u8 unused2[2];
} Slot;

typedef struct {
    u8 unused0[6];
    u8 x;
    u8 y;
    u8 unused8[0x10];
} Status;

extern Status dungeon_floor_object_positions[];
extern Slot floor_objects[];
extern void clear_slot_and_detach_entity(s32 slot_index);

/* Process each active slot at the given coordinates. */
void process_active_slots_at_coordinates(s16 x, s16 y) {
    s32 slot_index;
    s16 target_y;
    s16 target_x;

    slot_index = 0;
    target_x = x;
    target_y = y;
    do {
        if ((floor_objects[slot_index].active != 0) &&
            (dungeon_floor_object_positions[slot_index].x == target_x) &&
            (dungeon_floor_object_positions[slot_index].y == target_y)) {
            clear_slot_and_detach_entity(slot_index);
        }
        slot_index += 1;
    } while (slot_index < 0x20);
}
