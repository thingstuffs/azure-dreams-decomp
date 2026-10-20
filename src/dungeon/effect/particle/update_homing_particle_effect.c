#include "modules/dungeon_ovl_1852800.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_1852800.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/position_views.h"

extern int abs(int);

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_800DEA68[];
extern u8 D_800DED70[];
void *allocate_list_node();                     /* extern */
s32 register_node();                /* extern */
s32 func_80069EF8();                /* extern */
void apply_attack_power_and_element_effects(); /* extern */
void *scan_monster_along_heading();      /* extern */
s32 get_definition_entry_byte_13(s16);                         /* extern */
s32 play_sound_if_enabled();                     /* extern */
s32 sample_terrain_surface_height(s32, s32, s16);                   /* extern */

typedef struct S_func_81832800_1 {
    void *unk_00;
    u16 *unk_04;
    u8 pad_08[1];
    u8 unk_09;
    u16 unk_0A;
    u8 pad_0C[0x44];
    u16 unk_50;
    union { s16 as_s16; u16 as_u16; } unk_52;
} S_func_81832800_1;

typedef struct S_func_81832800_3 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} S_func_81832800_3;

typedef struct S_func_81832800_4 {
    union {
        s32 as_s32;
        struct {
            u8 pad_00[2];
            union { s16 as_s16; u16 as_u16; } unk_02;
        } parts;
    } unk_00;
    union {
        s32 as_s32;
        struct {
            u8 pad_04[2];
            union { s16 as_s16; u16 as_u16; } unk_06;
        } parts;
    } unk_04;
    union {
        s32 as_s32;
        struct {
            u8 pad_08[2];
            union { s16 as_s16; u16 as_u16; } unk_0A;
        } parts;
    } unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_func_81832800_4;

typedef struct S_func_81832800_5 {
    void *unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[2];
    u16 unk_14;
    u8 pad_16[6];
    union { s16 as_s16; u16 as_u16; } unk_1C;
    union { s16 as_s16; u16 as_u16; } unk_1E;
    u8 pad_20[4];
    u8 unk_24;
    u8 unk_25;
} S_func_81832800_5;

typedef struct S_func_81832800_6 {
    void *unk_00;
    u8 pad_04[8];
    u16 unk_0C;
    u16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x3A];
    s16 unk_4C;
} S_func_81832800_6;

typedef struct S_func_81832800_7 {
    u8 pad_00[4];
    s32 unk_04;
} S_func_81832800_7;

void (*const dungeon_1852800_entry)(S_func_81832800_1 *, S_func_81832800_4 *, void *) = decrement_flagged_item_parameters;

void decrement_flagged_item_parameters(S_func_81832800_1 *effect, S_func_81832800_4 *position, void *effect_sprite);
/* Advance the effect state, move toward its target, and animate spawned particles. */
s32 rand();                             /* extern */
s16 set_or_clear_actor_status_slot();        /* extern */
extern void func_800478B8(void *state);

void decrement_flagged_item_parameters(S_func_81832800_1 *effect, S_func_81832800_4 *position, void *effect_sprite) {
    S_func_81832800_3 *source_object;
    s32 step_x;
    s32 step_y;
    s32 ground_height;
    s16 state;
    s32 color;
    s32 height_delta;
    s32 spawn_value;
    s32 height_step;
    s32 jitter_base;
    s32 scale_random;
    s32 random_x;
    s32 random_y;
    s32 random_height;
    s32 jitter_count;
    s32 count;
    s32 rounded_x;
    s32 rounded_y;
    s32 rounded_height;
    s32 jitter_x;
    s32 jitter_y;
    s32 origin_x;
    s32 origin_y;
    u16 scale_y;
    u16 spawn_state;
    u16 scale_x;
    EntityRec *target;
    S_func_81832800_4 *jitter_position_x;
    S_func_81832800_4 *jitter_position_y;
    S_func_81832800_4 *burst_position;
    S_func_81832800_4 *burst_position_y;
    S_func_81832800_4 *target_position;
    S_func_81832800_5 *source_sprite;
    SpriteFrameState *sprite;
    S_func_81832800_6 *particle_data;
    EntityRec *source;
    S_func_81832800_3 *object;
    S_func_81832800_4 *particle_position;
    EntityRec *found_target;
    S_func_81832800_4 *height_position;
    u32 sprite_flags;
    s32 texture_word;
    void *particle_callback;
    S_func_81832800_7 *particle_texture;

    source = effect->unk_00;
    source_sprite = ((S_func_81832800_3 *) ((u8 *) source - 0x20))->unk_0C;
    count = (source->facing >> 9) & 7;
    step_x = dir_step_x[count];
    step_y = dir_step_y[count];
    spawn_state = effect->unk_0A;
    effect->unk_50 = (u16) (effect->unk_50 - 1);
    source_object = (S_func_81832800_3 *) ((u8 *) source - 0x20);
    if ((u32) (spawn_state - 1) < 3U) {
        count = 3;
        if ((s16) spawn_state < 3) {
            count = 5;
        }
        particle_callback = &update_shrinking_effect_sprite;
        particle_texture = (S_func_81832800_7 *) D_800DEA68;
        while (count >= 0) {
            object = allocate_list_node(0x312, ((u8 *)(&D_80083498)));
            if (object != NULL) {
                void *callback;
                S_func_81832800_4 *spawn_position;
                register_node(object, project_sprite_chain);
                sprite = object->unk_0C;
                spawn_position = object->unk_08;
                callback = particle_callback;
                object->unk_10 = callback;
                spawn_position->unk_00.as_s32 = (s32) position->unk_00.as_s32;
                particle_data = (S_func_81832800_6 *) ((u8 *) object + 0x20);
                jitter_count = 1;
                ((S_func_81832800_4 *) object->unk_08)->unk_04.as_s32 = (s32) position->unk_04.as_s32;
                do {
                    spawn_value = func_80069EF8();
                    jitter_position_x = object->unk_08;
                    jitter_x = spawn_value;
                    jitter_base = jitter_position_x->unk_00.parts.unk_02.as_u16 - 0x10;
                    if (spawn_value < 0) {
                        jitter_x = spawn_value + 0x1F;
                    }
                    jitter_position_x->unk_00.parts.unk_02.as_u16 = jitter_base + (spawn_value - ((jitter_x >> 5) << 5));
                    spawn_value = func_80069EF8(spawn_value, jitter_position_x, jitter_base);
                    jitter_position_y = object->unk_08;
                    jitter_y = spawn_value;
                    jitter_base = jitter_position_y->unk_04.parts.unk_06.as_u16 - 0x10;
                    if (spawn_value < 0) {
                        jitter_y = spawn_value + 0x1F;
                    }
                    jitter_position_y->unk_04.parts.unk_06.as_u16 = jitter_base + (spawn_value - ((jitter_y >> 5) << 5));
                    jitter_count -= 1;
                } while (jitter_count >= 0);
                particle_position = object->unk_08;
                ((S_func_81832800_4 *) object->unk_08)->unk_08.parts.unk_0A.as_s16 =
                    sample_terrain_surface_height(particle_position->unk_00.parts.unk_02.as_u16,
                    particle_position->unk_04.parts.unk_06.as_u16, (s16) (position->unk_08.parts.unk_0A.as_u16 - 0x30));
                height_position = object->unk_08;
                if (height_position->unk_08.parts.unk_0A.as_s16 >= 0x200) {
                    height_position->unk_08.parts.unk_0A.as_s16 = (s16) position->unk_08.parts.unk_0A.as_u16;
                }
                position->unk_08.parts.unk_0A.as_u16 =
                    (u16) ((S_func_81832800_4 *) object->unk_08)->unk_08.parts.unk_0A.as_s16;
                color = 0xC0C0C0;
                {
                    s32 scale = 0x1400;
                    sprite_flags = sprite->flags;
                    sprite->scale_y = (s16) scale;
                    sprite->scale_x = (s16) scale;
                    sprite->tpage_abr = 0;
                    sprite->color.word = color;
                    sprite->unk_00 = particle_texture;
                    sprite_flags |= 0xC;
                    sprite->flags = sprite_flags;
                    texture_word = particle_texture->unk_04;
                }
                sprite->unk_04 = 0;
                sprite->unk_05 = 0;
                sprite->source = texture_word;
                particle_data->unk_00 = effect;
                particle_data->unk_4C = 0;
            }
            count -= 1;
        }
    }
    state = (s16) effect->unk_0A;
    switch (state) {
    case 0:
        if (*effect->unk_04 & 0x80) {
            found_target = scan_monster_along_heading(source, source_sprite->unk_24, source_sprite->unk_25, source->facing,
                (s32)(s16) get_definition_entry_byte_13(6));
            source->target = found_target;
            if (found_target == NULL) {
                source->unk_72 = (u8) source_sprite->unk_24;
                source->unk_73 = (u8) source_sprite->unk_25;
            } else {
                sprite = ((S_func_81832800_3 *) ((u8 *) found_target - 0x20))->unk_0C;
                if (!(sprite->flags & 0x8000) || !(((S_func_81832800_5 *) effect_sprite)->unk_14 & 0x8000)) {
                    source->unk_72 = (u8) sprite->unk_24;
                    source->unk_73 = (u8) sprite->unk_25;
                } else {
                    effect->unk_0A = 0xF0;
                    return;
                }
            }
            position->unk_00.as_s32 = (s32) ((S_func_81832800_4 *) source_object->unk_08)->unk_00.as_s32;
            position->unk_04.as_s32 = (s32) ((S_func_81832800_4 *) source_object->unk_08)->unk_04.as_s32;
            position->unk_08.as_s32 = (s32) ((S_func_81832800_4 *) source_object->unk_08)->unk_08.as_s32;
            count = abs(source->unk_72 - source_sprite->unk_24);
            jitter_count = abs(source->unk_73 - source_sprite->unk_25);
            if (count < jitter_count) {
                count = jitter_count;
            }
            effect->unk_50 = count * 4;
            position->unk_0C = (s32) (step_x << 0x14);
            position->unk_10 = (s32) (step_y << 0x14);
            play_sound_if_enabled(0x300);
            effect->unk_0A += 1;
            return;
        }
        break;

    case 1:
        if ((s16) effect->unk_50 >= 0) {
            position->unk_00.as_s32 += position->unk_0C;
            position->unk_04.as_s32 += position->unk_10;
            return;
        }
        effect->unk_50 = 6;
        effect->unk_0A += 1;
        return;

    case 2:
        if ((s16) effect->unk_50 <= 0) {
            sprite_flags = 0x100000;
            target = source->target;
            if (target == NULL) {
                effect->unk_0A = 0xFF;
                return;
            }
            target->flags14 |= sprite_flags;
            effect->unk_50 = 0x14U;
            effect->unk_0A += 1;
            return;
        }
        return;

    case 3:
        count = 3;
        ground_height = (s16) sample_terrain_surface_height(position->unk_00.parts.unk_02.as_u16, position->unk_04.parts.unk_06.as_u16,
            (s16) (position->unk_08.parts.unk_0A.as_u16 - 0x30));
        do {
            object = allocate_list_node(0x312, ((u8 *)(&D_80083498)));
            if (object != NULL) {
                void *callback;
                register_node(object, project_sprite_chain);
                particle_data = (S_func_81832800_6 *) ((u8 *) object + 0x20);
                sprite = object->unk_0C;
                callback = &update_homing_brightening_effect;
                object->unk_10 = callback;
                rounded_x = func_80069EF8();
                random_x = rounded_x;
                burst_position = object->unk_08;
                origin_x = position->unk_00.parts.unk_02.as_u16;
                particle_data->unk_0C = origin_x;
                if (random_x < 0) {
                    rounded_x = random_x + 0x7F;
                }
                burst_position->unk_00.parts.unk_02.as_s16 = (s16) ((origin_x + (random_x - ((rounded_x >> 7) << 7)))
                    - 0x40);
                rounded_y = func_80069EF8((s32) origin_x, burst_position);
                random_y = rounded_y;
                burst_position_y = object->unk_08;
                origin_y = position->unk_04.parts.unk_06.as_u16;
                particle_data->unk_0E = origin_y;
                if (random_y < 0) {
                    rounded_y = random_y + 0x7F;
                }
                burst_position_y->unk_04.parts.unk_06.as_s16 = (s16) ((origin_y + (random_y - ((rounded_y >> 7) << 7)))
                    - 0x40);
                rounded_height = func_80069EF8((s32) origin_y, burst_position_y);
                random_height = rounded_height;
                burst_position = object->unk_08;
                particle_data->unk_10 = ground_height;
                if (random_height < 0) {
                    rounded_height = random_height + 0x3F;
                }
                burst_position->unk_08.parts.unk_0A.as_s16 = (s16) ((ground_height + (random_height - ((rounded_height
                    >> 6) << 6))) - 0x80);
                color = 0x101010;
                sprite_flags = sprite->flags;
                sprite->scale_y = 0x1000;
                sprite->scale_x = 0x1000;
                sprite->tpage_abr = 0x20;
                sprite->color.word = color;
                sprite->unk_00 = D_800DED70;
                sprite_flags |= 0xC;
                sprite->flags = sprite_flags;
                texture_word = (s32) ((S_func_81832800_7 *) D_800DED70)->unk_04;
                sprite->unk_04 = 0;
                sprite->unk_05 = 0;
                sprite->source = texture_word;
                object->unk_20 = effect;
                particle_data->unk_4C = 0;
            }
            count -= 1;
        } while (count >= 0);
        object = source->target - 0x20;
        target_position = object->unk_08;
        height_delta = target_position->unk_08.parts.unk_0A.as_s16 - 0x18;
        height_delta = ground_height - height_delta;
        height_step = height_delta / 10;
        target_position->unk_08.parts.unk_0A.as_s16 = (s16) ((u16) target_position->unk_08.parts.unk_0A.as_s16
            + height_step);
        sprite = object->unk_0C;
        if ((u16) sprite->scale_x >= 0x21C1U) {
            sprite->scale_x = 0x2000U;
        }
        scale_random = func_80069EF8();
        sprite->scale_x = (u16) (sprite->scale_x + ((scale_random & 0x1FF) + 0x100));
        if ((u16) sprite->scale_y < 0x76CU) {
            sprite->scale_y = 0x800U;
        }
        sprite->scale_y = (u16) (sprite->scale_y - ((func_80069EF8() & 0xFF) + 0x80));
        if ((s16) effect->unk_50 > 0) {
            return;
        }
        if (source->target == NULL) {
            effect->unk_0A = 0xFF;
            return;
        }
        apply_attack_power_and_element_effects(source->target, 8, effect->unk_09, 4, (s32) source->facing, source, 2);
        effect->unk_50 = 6U;
        effect->unk_0A = 0xF0;
        return;

    case 0xF0:
        sprite = ((S_func_81832800_3 *) ((u8 *) source->target - 0x20))->unk_0C;
        scale_x = sprite->scale_x;
        scale_y = sprite->scale_y;
        sprite->scale_x = (u16) (scale_x + ((s32) (0x1000 - scale_x) >> 2));
        sprite->scale_y = (u16) (scale_y + ((s32) (0x1000 - scale_y) >> 2));
        if ((s16) effect->unk_50 <= 0) {
            sprite->scale_y = 0x1000U;
            sprite->scale_x = 0x1000U;
            effect->unk_0A = 0xFFU;
            ((EntityRec *) source->target)->flags14 &= ~0x100000;
            return;
        }
        return;

    case 0xFF:
        if (effect->unk_52.as_s16 & 0x8000) {
            effect->unk_52.as_u16 &= 0x7FFF;
            return;
        }
        g_dungeon_status.unk_0C = 0;
        ((u16 *) ((u8 *) effect - 2))[0] = (u16) (((u16 *) ((u8 *) effect - 2))[0]
            | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}

/* cfail-repair: tf7-phase1-cache-v3 */

typedef struct S_81832FE8_0 {
    u8 pad_00[0x60];
    void * unk_60;
} S_81832FE8_0;   /* arg0 in func_800247E8 */

typedef struct S_81832FE8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_81832FE8_1;

/* Set flag 0x20 and apply a randomized effect to an eligible attached object. */
void func_800247E8(S_81832FE8_0 *owner) {
    s32 flags;
    S_81832FE8_1 *object;

    object = owner->unk_60;
    if (object != NULL) {
        flags = object->unk_14;
        if (flags & 0x20) return;
        if (flags & 1) {
            object->unk_1C = (s32) (object->unk_1C | 0x20);
            set_or_clear_actor_status_slot(owner->unk_60, 4, (rand() & 0x3F) | 0x20);
        }
    }
}

typedef struct StructInner {
    s8 pad0[0x52];
    u16 unk52;
} StructInner;

typedef struct StructA0 {
    StructInner *inner;
} StructA0;

typedef struct StructA2 {
    u8 pad0[0x14];
    u16 unk14;
    u8 pad16[0x1C - 0x14 - 2];
    u16 unk1C;
    u16 unk1E;
} StructA2;


/* Decreases paired state values by 0x80, invokes the state handler, and sets flags. */
void update_shrinking_effect_sprite(StructA0 *owner, void *unused, StructA2 *state) {
    u16 adjusted_value;

    adjusted_value = state->unk1E - 0x80;
    state->unk1E = adjusted_value;
    state->unk1C = adjusted_value;
    owner->inner->unk52 |= 0x8000;
    func_800478B8(state);
    if (state->unk14 & 0x6000) {
        ((u16 *)owner)[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

typedef struct S_818330F0_1 {
    void * unk_00;
    u8 pad_04[0x8];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} S_818330F0_1;   /* arg0 in update_homing_brightening_effect */

typedef struct S_818330F0_3 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_818330F0_3;

/* cfail-repair: tf7-phase1-cache-v3 */
/* Ease the position toward its target, brighten the primitive, and flag completion. */
void update_homing_brightening_effect(void *effect, void *position, SpriteFrameState *primitive) {
    s16 target_z;
    s16 current_z;
    void *owner;

    ((SignedPositionView *)position)->unk_02 = (s16) ((u16) ((SignedPositionView *)position)->unk_02
        + ((((S_818330F0_1 *)effect)->unk_0C - ((SignedPositionView *)position)->unk_02) / 12));
    ((SignedPositionView *)position)->unk_06 = (s16) ((u16) ((SignedPositionView *)position)->unk_06
        + ((((S_818330F0_1 *)effect)->unk_0E - ((SignedPositionView *)position)->unk_06) / 12));
    target_z = ((S_818330F0_1 *)effect)->unk_10;
    current_z = ((SignedPositionView *)position)->unk_0A;
    ((SignedPositionView *)position)->unk_0A = (s16) ((u16) ((SignedPositionView *)position)->unk_0A + ((target_z
        - current_z) / 10));
    primitive->color.word = (s32) (primitive->color.word
        + 0xC0C0C);
    owner = ((S_818330F0_1 *)effect)->unk_00;
    ((S_818330F0_3 *)owner)->unk_52 = (u16) (((S_818330F0_3 *)owner)->unk_52 | 0x8000);
    func_800478B8(primitive);
    if ((u8) primitive->color.word >= 0x91U) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((u16 *)effect)[-1] | 0x8000);
        object_flag_block.flags |= 0x8000;
    }
}
