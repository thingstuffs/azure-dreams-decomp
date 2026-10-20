#include "dungeon/level/generate.h"

void initialize_random_room_slot(void *room, s32 rng_arg1)
{
    u8 *slot_data;
    s16 raw_size;
    s16 size;
    s32 room_area;
    s32 random_bonus;
    s32 x_offset;
    s32 y_roll;
    s32 slot_index;
    int y_offset;
    u8 *slot_info;
    if (!((D_800E296C) & 0x10000000)) {
        random_bonus = generate_random_value() & 7;
        room_area = (*((u16 *) (((s8 *) room) + 6))) * (*((u16 *) (((s8 *) room) + 4)));
        raw_size = (room_area >> 2) + random_bonus;
        size = raw_size;
        if (raw_size >= 0x1D) {
            size = 0x1C;
        }
        slot_index = 0;
        for (; slot_index < 0x20; slot_index++) {
            slot_info = (u8 *)((u32 *)((u8 *)D_800E3648) + slot_index);
            slot_data = (u8 *)((u8 *)D_800E39C8) + slot_index * 0x18;
            if ((*((u8 *) (((s8 *) slot_info) + 1))) == 0) {
                x_offset = random_dungeon_range_16(0, ((*((u16 *) (((s8 *) room) + 4))) - 1) & 0xFFFF) & 0xFFFF;
                y_roll = random_dungeon_range_16(0, ((*((u16 *) (((s8 *) room) + 6))) - 1) & 0xFFFF);
                y_offset = y_roll & 0xFFFF;
                *((s8 *) (((s8 *) slot_data) + 6)) = (s8) ((*((u8 *) (((s8 *) room) + 0))) + x_offset);
                *((s8 *) (((s8 *) slot_data) + 7)) = (s8) ((*((u8 *) (((s8 *) room) + 2))) + y_offset);
                *((u8 *) (((s8 *) slot_info) + 0)) = 0x13;
                *((u8 *) (((s8 *) slot_info) + 1)) = 0x15U;
                *((u8 *) (((s8 *) slot_info) + 3)) = (u8) 0xC0;
                *((s8 *) (((s8 *) slot_info) + 2)) = (s8) size;
                *((s32 *) (((s8 *) slot_data) + 8)) = 0;
                return;
            }
        }
    }
}
