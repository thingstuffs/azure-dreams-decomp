/* Initializes randomized effect motion and resets appearance when its countdown expires. */
/* inferred-strong G00570: randomized_effect_motion_g00570; joins PD:town/engine:800D0B20; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0B20. */
#include "town/menu/randomized_effect_motion_g00570.h"
#include "town/player/position.h"

/* Initializes the object record and a randomized motion vector. */
void initialize_randomized_motion_vector(u8 *obj, s32 *vec, SpriteFrameState *record)
{
    s32 tilt_angle;
    s32 scale;
    s32 direction_angle;
    s32 direction_term;
    s32 init_value;
    SpriteSourceEntry *init_entry;
    s32 product;
    s32 scale_numerator;
    s32 scale_sample;
    s32 unit_scale;

    unit_scale = 0x1000;
    record->scale_y = unit_scale;
    record->color.word = 0x808080;
    record->scale_x = unit_scale;
    record->source = D_800D0B50[((S_800A3508_1 *)obj)->unk_22];
    record->unk_00 = 0;
    record->unk_04 = 0;
    record->frame_ticks = 0;

    init_entry = D_800D0B20[((S_800A3508_1 *)obj)->unk_22];
    if (init_entry != 0) {
        select_record_entry_and_value(record, init_entry, 0);
    }

    register_node(obj - 0x20, project_sprite_chain);

    if (((S_800A3508_1 *)obj)->unk_22 < 4) {
        init_value = scale_random_to_unsigned_halfword_limit(0x1000);
        tilt_angle = 0x400;
        direction_angle = D_800D0B18[((S_800A3508_1 *)obj)->unk_22] + (init_value & 0xFFFF);
    } else {
        direction_angle = scale_random_to_unsigned_halfword_limit(0x1000) & 0xFFFF;
        tilt_angle = scale_random_to_unsigned_halfword_limit(0x1000) & 0xFFFF;
    }
    scale_sample = scale_random_to_unsigned_halfword_limit(0x1000) & 0xFFFF;
    scale_numerator = scale_sample + 0x1000;
    if (scale_numerator < 0) {
        scale_numerator = scale_sample + 0x101F;
    }
    scale = (s32)scale_numerator >> 5;
    product = rsin(direction_angle) * rsin(tilt_angle);
    if (product < 0) {
        product += 0xFFF;
    }
    vec[3] = product >> 12;

    direction_term = rcos(direction_angle);
    product = direction_term * rsin(tilt_angle);
    vec[4] = (product / 4096);

    vec[5] = rcos(tilt_angle);
    vec[3] *= scale;
    vec[4] *= scale;
    vec[5] *= scale;

    (*(s32 *)((u8 *)obj + 0x2C)) = vec[3] / 23;
    ((S_800A3508_1 *)obj)->unk_30 = vec[4] / 23;
    ((S_800A3508_1 *)obj)->unk_34 = vec[5] / 23;
    ((S_800A3508_1 *)obj)->unk_24 = 0x18;
    ((S_800A3508_1 *)obj)->unk_00 = D_800A378C;

    add_motion_deltas_to_position((ObjectPosition *)vec);
    add_motion_deltas_to_position((ObjectPosition *)vec);
}

/* Updates the transform until the countdown expires, then resets appearance and advances state. */
void advance_motion_and_reset_appearance(S_800A378C_0 *state, ObjectPosition *transform, SpriteFrameState *appearance) {
    s32 ticks_left;

    ticks_left = state->unk_24 - 1;
    state->unk_24 = ticks_left;
    if (ticks_left < 0) {
        transform->velocity_x = 0;
        transform->velocity_y = 0;
        transform->velocity_z = 0;
        appearance->color.c.b = 0x40;
        appearance->color.c.g = 0x40;
        appearance->color.c.r = 0x40;
        appearance->tpage_abr = 0x20;
        appearance->flags = (u16) (appearance->flags | 0x1C);
        state->unk_00 = &D_800A38A8;
        transform->velocity_x = 0;
        transform->velocity_y = 0;
        transform->velocity_z =
            ((((u16) scale_random_to_unsigned_halfword_limit(0x1000)) << 1) + 0x2000) << 4;
        return;
    }
    transform->velocity_x = (s32) (transform->velocity_x - state->unk_2C);
    transform->velocity_y = (s32) (transform->velocity_y - state->unk_30);
    transform->velocity_z = (s32) (transform->velocity_z - state->unk_34);
    add_motion_deltas_to_position(transform);
    if (D_800D0B20[state->unk_22] != 0) {
        advance_sprite_animation_and_textures(appearance);
    }
}
