#include "common.h"

extern void func_800A08A0(s32 spawn_mode);
extern s32 random_dungeon_range_16(u32 bound_a, u32 bound_b);

/* Initializes monster spawn rates with values 2 through 17 and a random number of value 1 entries. */
void spawn_initial_floor_monsters(void) {
    s32 repeat_count;
    s32 call_index;
    s32 scaled_value;

    repeat_count = random_dungeon_range_16(4, 8) & 0xFFFF;
    call_index = 0;
    do {
        scaled_value = (call_index + 2) << 0x10;
        func_800A08A0(scaled_value >> 0x10);
        call_index += 1;
    } while (call_index < 0x10);
    call_index = 0;
    if (call_index < repeat_count) {
        do {
            func_800A08A0(1);
            call_index += 1;
        } while (call_index < repeat_count);
    }
}
