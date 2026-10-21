#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_8185C860_0 {
    void * unk_00;
    u8 pad_04[0x6C];
    s32 unk_70;
} S_8185C860_0;



s32 check_entity_interaction_compatibility();
s32 check_entity_eligibility();
s32 generate_random_value();
s32 try_apply_status_effect();
extern u8 current_spell_effect_variant;

/* Apply a randomized effect to eligible targets within two tiles of the center. */
void apply_randomized_effect_near_center(s16 center_x, s16 center_y, s32 source, s32 power) {
    s32 effect_code;
    s16 base_value;
    s32 effect_value;
    s32 distance_x;
    s32 distance_y;
    u8 *target;
    MovingTile *position;

    target = ((u8 *)dungeon_actor_ring_anchor);
    base_value = (s16)(((u32)(power & 0xFF) >> 2) + 0x10);
    do {
        if ((check_entity_interaction_compatibility(source, target) << 0x10) != 0) {
            position = ((S_8185C860_0 *)((u8 *)target - 0x14))->unk_00;
            distance_x = position->unk_24 - center_x;
            if (distance_x < 0) {
                distance_x = 0 - distance_x;
            }
            if (distance_x < 3) {
                distance_y = position->unk_25 - center_y;
                if (distance_y < 0) {
                    distance_y = 0 - distance_y;
                }
                if (distance_y < 3) {
                    if ((check_entity_eligibility(target) << 0x10) != 0) {
                        effect_value = base_value + (generate_random_value() & 3);
                        effect_code = 0x20;
                        if (current_spell_effect_variant == 0xFF) {
                            effect_code = 0xFF;
                        }
                        try_apply_status_effect(target, effect_code, effect_value);
                    }
                }
            }
        }
        target = ((S_8185C860_0 *)((u8 *)target - 0x14))->unk_70 + 0x20;
    } while (target != ((u8 *)dungeon_actor_ring_anchor));
}

