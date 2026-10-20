#include "common.h"

extern s32 fade_actor_to_removal(s32 value_a, s32 value_b, void *ptr, s32 value_c);
extern void decrement_event_counter(void);

void fade_actor_removal_and_decrement_event(s32 value_a, s32 value_b, void *ptr, s32 value_c) {
    if (fade_actor_to_removal(value_a, value_b, ptr, value_c) != 0) {
        decrement_event_counter();
        return;
    }

    *(s16 *)((u8 *)ptr + 0x12) = 0;
}
