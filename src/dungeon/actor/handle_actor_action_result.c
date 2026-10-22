#include "common.h"
#include "dungeon/system.h"

extern s32 fade_actor_to_removal(s32 value_a, s32 value_b, void *ptr, s32 value_c);

void handle_actor_action_result(s32 value_a, s32 value_b, void *ptr, s32 value_c) {
    if (fade_actor_to_removal(value_a, value_b, ptr, value_c) != 0) {
        decrement_bounded_counter();
        return;
    }

    *(s16 *)((u8 *)ptr + 0x12) = 0;
}
