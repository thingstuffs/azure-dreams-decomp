#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s8 M2C_UNK8;
extern u8 D_800E3648[];
s32 func_800A6D30(void *, s32, s32, s32);
s32 func_800A6DA4();
extern u8 D_800E39C8[];
/* Initializes a free slot at a random position within the room. */
void func_8001CFB8(void *room, s32 rng_arg1, s32 rng_arg2, s32 rng_arg3)
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
        random_bonus = func_800A6D30(room, rng_arg1, rng_arg2, rng_arg3) & 7;
        room_area = (*((u16 *) (((s8 *) room) + 6))) * (*((u16 *) (((s8 *) room) + 4)));
        raw_size = (room_area >> 2) + random_bonus;
        size = raw_size;
        if (raw_size >= 0x1D) {
            size = 0x1C;
        }
        slot_index = 0;
        slot_info = D_800E3648;
        slot_data = &D_800E39C8;
check_slot:
        if ((*((u8 *) (((s8 *) slot_info) + 1))) == 0) {
            x_offset = func_800A6DA4(0, ((*((u16 *) (((s8 *) room) + 4))) - 1) & 0xFFFF, room_area) & 0xFFFF;
            y_roll = func_800A6DA4(0, ((*((u16 *) (((s8 *) room) + 6))) - 1) & 0xFFFF);
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
        slot_index += 1;
        slot_info += 4;
        slot_data += 0x18;
        if (slot_index >= 0x20) {
        }
        else {
            goto check_slot;
        }
    }
}
