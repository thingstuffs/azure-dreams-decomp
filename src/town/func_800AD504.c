#include "common.h"


extern s8 scale_random_to_unsigned_halfword_limit();
extern void update_actor_surface_motion();
extern void select_object_value_by_height_band();

/* Randomize color during an update, then reset it when the timer expires or state changes. */
void randomize_person_color(void *object, s32 context, s32 update_param, void *color_data) {
    s32 previous_state;
    s16 ticks_left;

    *(s8 *)((s8 *)color_data + 0xC) = scale_random_to_unsigned_halfword_limit(0x100);
    *(s8 *)((s8 *)color_data + 0xD) = scale_random_to_unsigned_halfword_limit(0x100);
    *(s8 *)((s8 *)color_data + 0xE) = scale_random_to_unsigned_halfword_limit(0x100);
    previous_state = *(s32 *)((s8 *)object + 0x50);
    update_actor_surface_motion(object, context, update_param, color_data);
    ticks_left = *(u16 *)((s8 *)object + 0x6C) - 1;
    *(u16 *)((s8 *)object + 0x6C) = ticks_left;
    if ((ticks_left < 0) || (*(s32 *)((s8 *)object + 0x50) != previous_state)) {
        select_object_value_by_height_band(object, context, update_param, color_data);
        *(u8 *)((u8 *)color_data + 0xC) = 0x80;
        *(u8 *)((u8 *)color_data + 0xD) = 0x80;
        *(u8 *)((u8 *)color_data + 0xE) = 0x80;
    }
}
