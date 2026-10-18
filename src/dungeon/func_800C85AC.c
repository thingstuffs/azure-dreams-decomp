#include "modules/trap_effects_candidate.h"
#include "common.h"




extern u8 D_800DF870[];

extern s32 generate_random_value(void);
extern void display_fixed_item_action_message();
extern s32 play_sound_if_enabled();
extern void attempt_action_six_if_eligible(void *, s32, s32);
extern void spawn_vertical_particle_burst(s16 x, s16 y, s16 z, s32 sprite_id, s16 play_sound);

/* Applies a chance-based effect, with visual and sound feedback for unflagged entries. */
s32 apply_chance_based_trap_effect(void *state, s32 rng_arg1, s32 rng_arg2, s32 rng_arg3)
{
    s16 roll;
    s32 random_value;
    s32 effect_amount;
    Entry *entry;

    if (!D_800E3D40 &&
        (random_value = generate_random_value() & 0xffff,
         *(u8 *)((u8 *)state + 3))) {
        s32 remainder;
        remainder = random_value % *(u8 *)((u8 *)state + 3);
        roll = remainder;
    } else {
        roll = 0;
    }
    if (roll < 0x30) {
        effect_amount = 0x20;
        if (D_800E3D40 != 0) {
            effect_amount = 0x400;
        }
        attempt_action_six_if_eligible(state, effect_amount, 0x10);

        entry = *(Entry **)((u8 *)state - 0x14);
        if (!(entry->flags & 0x8000)) {
            spawn_vertical_particle_burst((entry->x << 6) | 0x20,
                          (entry->y << 6) | 0x20,
                          *(s16 *)((u8 *)state + 0x88), D_800DF870, 0);
            play_sound_if_enabled(0x70A);
            return 1;
        }
        return 1;
    }

    if (*(u8 *)((u8 *)state + 0x13) == 0) {
        display_fixed_item_action_message();
    }
    return 1;
}
