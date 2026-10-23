#include "shared/object_node.h"
#include "dungeon/effect/particle.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_sprite_data.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_81814EDC_0_pre {
    u16 unk_00;
} S_81814EDC_0_pre;   /* the 0x2 bytes before arg0 in update_spark_emitter_effect, addressed as arg0[-1] */

typedef struct S_81814EDC_0 {
    s16 unk_00;
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    s16 unk_08;
    u16 unk_0A;
    u8 pad_0C[0x9];
    u8 unk_15;
    u16 unk_16;
    u8 pad_18[0x14];
    s32 unk_2C;
    void * unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_81814EDC_0;   /* arg0 in update_spark_emitter_effect */

typedef struct S_81814EDC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xE];
    s16 unk_22;
} S_81814EDC_1;

   /* source in update_spark_emitter_effect */

typedef struct S_81814EDC_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_81814EDC_4;

typedef struct S_81814EDC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x4C];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_81814EDC_5;

typedef struct S_81814EDC_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_81814EDC_7_pre;   /* the 0x18 bytes before source_owner in update_spark_emitter_effect, addressed as source_owner[-1] */

typedef struct S_81814EDC_8 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81814EDC_8;

typedef struct S_81814EDC_9 {
    u8 pad_00[0xC];
    union { s8 s; u8 u; } unk_0C;   /* accessed as both */
    union { s8 s; u8 u; } unk_0D;   /* accessed as both */
    union { s8 s; u8 u; } unk_0E;   /* accessed as both */
} S_81814EDC_9;


typedef struct S_81814EDC_11 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81814EDC_11;

typedef struct S_81814EDC_12_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_81814EDC_12_pre;   /* the 0x18 bytes before ((S_81814EDC_0 *)arg0)->unk_30 in update_spark_emitter_effect, addressed as ((S_81814EDC_0 *)arg0)->unk_30[-1] */

extern u8 D_800DE938[];
M2C_UNK func_800245BC();
s32 register_node();
s32 rand();
void apply_attack_power_and_element_effects();
s32 check_adjacent_tile_height_clearance();
extern M2C_UNK D_80024280;

/* Spawns particles, moves the effect, and restores its owner after the fade. */
void update_spark_emitter_effect(void *effect, ObjectPosition *position) {
    s16 state;
    s16 effect_type;
    s32 spark_speed;
    s32 burst_speed;
    s32 spark_kind;
    s32 burst_kind;
    s32 effect_index;
    s32 neutral_color;
    s32 double_scale;
    s32 unit_scale;
    u16 ticks_left;
    u16 fade_ticks;
    void *owner;
    S_81814EDC_11 *owner_flags;
    S_81814EDC_9 *owner_sprite;
    SpriteFrameState *sprite;
    S_81814EDC_5 *debris;
    MovingPosition *owner_position;
    ObjectNodeHeader *particle;

    if (((S_81814EDC_0 *)effect)->unk_00 == 0) {
        if (!(((S_81814EDC_0 *)effect)->unk_0A & 1)) {
            spark_kind = rand() & 7;
            spark_speed = (rand() & 0xFF) | 0x80;
            func_800245BC(effect - 0x20, spark_kind, 0xF0, spark_speed, 0, 0,
                (s32) (s16) (-0x20 - (rand() & 0x1F)));
        }
        particle = allocate_flagged_object_node(0x212);
        if (particle != NULL) {
            ((S_81814EDC_1 *)particle)->unk_22 = 9;
            particle->unk_10 = &D_80024280;
            register_node(particle, project_sprite_chain);
            sprite = particle->sprite;
            sprite->flags = (u16) (sprite->flags | 0xC);
            debris = particle->position;
            {
                s32 random_offset = rand() & 0x1F;
                s32 coordinate;
                coordinate = ((u16) position->x.w.i);

                coordinate -= 0x10;
                coordinate += random_offset;
                ((S_81814EDC_4 *)debris)->unk_02 = (s16) coordinate;
            }
            {
                s32 random_offset = rand() & 0x1F;
                s32 coordinate;
                coordinate = ((u16) position->y.w.i);

                coordinate -= 0x10;
                coordinate += random_offset;
                ((S_81814EDC_4 *)debris)->unk_06 = (s16) coordinate;
            }
            {
                s32 random_offset = rand() & 7;
                s32 coordinate;
                coordinate = ((u16) position->z.w.i);

                coordinate -= 4;
                coordinate += random_offset;
                ((S_81814EDC_4 *)debris)->unk_0A.s = (s16) coordinate;
            }
            sprite = particle->sprite;
            sprite->scale_x = 0x2000;
            sprite->scale_y = 0x1000;
            sprite->color.c.b = 0x80;
            sprite->color.c.g = 0x80;
            sprite->color.c.r = 0x80;
            select_record_entry_and_value(sprite, D_800DE938, 0);
            advance_sprite_animation_and_textures(sprite);
            advance_sprite_animation_and_textures(sprite);
        }
        ticks_left = ((S_81814EDC_0 *)effect)->unk_02.s - 1;
        ((S_81814EDC_0 *)effect)->unk_02.s = ticks_left;
        if ((ticks_left << 0x10) <= 0) {
            effect_index = 0;
            if (((S_81814EDC_0 *)effect)->unk_08 != 0) {
loop_effects:
                effect_index += 1;
                burst_kind = rand() & 7;
                burst_speed = (rand() & 0xFF) | 0x80;
                func_800245BC(effect - 0x20, burst_kind, 0xF0, burst_speed, 0, 0,
                    (s32) (s16) (-0x20 - (rand() & 0x1F)));
                if (effect_index < 4) {
                    goto loop_effects;
                }
                effect_index = 0;
                do {
                    particle = allocate_flagged_object_node(0x212);
                    debris = ((void *)particle) + 0x20;
                    if (particle != NULL) {
                        s32 random_offset = 0xB;
                        s32 coordinate;

                        debris->unk_02 = 0xD;
                        owner_position = ((S_81814EDC_12_pre *)(((S_81814EDC_0 *)effect)->unk_30))[-1].unk_00;
                        particle->unk_10 = &D_80024280;
                        register_node(particle, project_sprite_chain);
                        sprite = particle->sprite;
                        sprite->flags = (u16) (sprite->flags | 0xC);
                        debris->unk_58 = (s32) (((rand() & 0x7FFF) << 5) + 0xFFF80000);
                        debris->unk_5C = (s32) (((rand() & 0x7FFF) << 5) + 0xFFF80000);
                        debris->unk_60 = (s32) (((rand() & 0x3FFF) << 5) + 0xFFF80000);
                        debris = particle->position;
                        random_offset = rand() & 0xF;
                        coordinate = owner_position->unk_02;
                        coordinate -= 8;
                        coordinate += random_offset;
                        debris->unk_02 = (s16) coordinate;
                        random_offset = rand() & 1;
                        coordinate = owner_position->unk_06;
                        coordinate -= 1;
                        coordinate += random_offset;
                        debris->unk_06 = (s16) coordinate;
                        debris->unk_0A = (s16) (owner_position->unk_0A - 0x20);
                        sprite = particle->sprite;
                        sprite->scale_y = 0x1000;
                        sprite->scale_x = 0x1000;
                        sprite->color.c.b = 0x80;
                        sprite->color.c.g = 0x80;
                        sprite->color.c.r = 0x80;
                        select_record_entry_and_value(sprite, effect_sprite_sources, 0);
                    }
                    effect_index += 1;
                } while (effect_index < 2);
                unit_scale = 0x1000;
                effect_index = 0;
                neutral_color = 0x80;
                double_scale = 0x2000;
                do {
                    particle = allocate_flagged_object_node(0x212);
                    if (particle != NULL) {
                        s32 random_offset = 0xB;
                        s32 coordinate;

                        ((S_81814EDC_1 *)particle)->unk_22 = random_offset;
                        owner_position = ((S_81814EDC_7_pre *)(((S_81814EDC_0 *)effect)->unk_30))[-1].unk_00;
                        particle->unk_10 = &D_80024280;
                        register_node(particle, project_sprite_chain);
                        sprite = particle->sprite;
                        sprite->flags = (u16) (sprite->flags | 0xC);
                        debris = particle->position;
                        random_offset = rand() & 0xF;
                        coordinate = owner_position->unk_02;
                        coordinate -= 8;
                        coordinate += random_offset;
                        ((S_81814EDC_4 *)debris)->unk_02 = (s16) coordinate;
                        random_offset = rand() & 1;
                        coordinate = owner_position->unk_06;
                        coordinate -= 1;
                        coordinate += random_offset;
                        ((S_81814EDC_4 *)debris)->unk_06 = (s16) coordinate;
                        ((S_81814EDC_4 *)debris)->unk_0A.u = (u16) owner_position->unk_0A;
                        sprite = particle->sprite;
                        sprite->color.c.b = neutral_color;
                        sprite->color.c.g = neutral_color;
                        sprite->color.c.r = neutral_color;
                        sprite->unk_06 = 7;
                        if (effect_index == 0) {
                            sprite->scale_x = unit_scale;
                            sprite->scale_y = double_scale;
                            ((S_81814EDC_4 *)debris)->unk_0A.u -= 0x14;
                        } else {
                            sprite->scale_x = double_scale;
                            sprite->scale_y = unit_scale;
                        }
                        select_record_entry_and_value(sprite, D_800DE938, 0);
                    }
                    effect_index += 1;
                } while (effect_index < 2);
                effect_type = (s16) ((S_81814EDC_0 *)effect)->unk_0A;
                if (effect_type == 4) {
                    apply_attack_power_and_element_effects(((S_81814EDC_0 *)effect)->unk_30, 0x10, ((S_81814EDC_0 *)effect)->unk_15, 1,
                        (s32) (s16) (((S_81814EDC_0 *)effect)->unk_16 << 9), ((S_81814EDC_0 *)effect)->unk_2C, 2);
                    if ((s16) ((S_81814EDC_0 *)effect)->unk_0A == effect_type) {
                        owner = ((S_81814EDC_0 *)effect)->unk_30;
                        ((S_81814EDC_0 *)effect)->unk_00 = 1;
                        owner_sprite = ((SpriteLinkPrefixView *)owner)[-1].unk_00;
                        ((S_81814EDC_8 *)owner)->unk_1C = (s32) (((S_81814EDC_8 *)owner)->unk_1C | 0x10000000);
                        owner_sprite->unk_0E.s = 0x30;
                        owner_sprite->unk_0D.s = 0x30;
                        owner_sprite->unk_0C.s = 0x30;
                        ((S_81814EDC_0 *)effect)->unk_02.u = 0;
                    } else {
                        ((S_81814EDC_0_pre *)effect)[-1].unk_00 =
                            (u16) (((S_81814EDC_0_pre *)effect)[-1].unk_00 | 0x8000);
                        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                        return;
                    }
                } else {
                    ((S_81814EDC_0_pre *)effect)[-1].unk_00 = (u16) (((S_81814EDC_0_pre *)effect)[-1].unk_00 | 0x8000);
                    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                    return;
                }
            } else {
                ((S_81814EDC_0 *)effect)->unk_00 = 1;
            }
        }
        {

            if ((check_adjacent_tile_height_clearance(((u16) position->x.w.i), ((u16) position->y.w.i),
                (s16) ((u16) position->z.w.i), ((S_81814EDC_0 *)effect)->unk_30) << 0x10) == 0) {
                {
                    s32 velocity = ((S_81814EDC_0 *)effect)->unk_58;
                    position->x.v = (s32) (position->x.v
                        + velocity);
                }
                position->y.v = (s32) (position->y.v
                    + ((S_81814EDC_0 *)effect)->unk_5C);
                position->z.v = (s32) (position->z.v
                    + ((S_81814EDC_0 *)effect)->unk_60);
            } else {
                ((S_81814EDC_0_pre *)effect)[-1].unk_00 = (u16) (((S_81814EDC_0_pre *)effect)[-1].unk_00 | 0x8000);
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
                return;
            }
        }
    }
    state = ((S_81814EDC_0 *)effect)->unk_00;
    if (state == 1) {
        fade_ticks = ((S_81814EDC_0 *)effect)->unk_02.s + 1;
        ((S_81814EDC_0 *)effect)->unk_02.s = fade_ticks;
        if ((s16) fade_ticks >= 0x15) {
            if (((s16) ((S_81814EDC_0 *)effect)->unk_0A == 4) && (((S_81814EDC_0 *)effect)->unk_08 == state)) {
                owner_flags = ((S_81814EDC_0 *)effect)->unk_30;
                owner_flags->unk_1C = (s32) (owner_flags->unk_1C & 0xEFFFFFFF);
                owner_sprite = ((S_81814EDC_12_pre *)(((S_81814EDC_0 *)effect)->unk_30))[-1].unk_04;
                owner_sprite->unk_0E.u = 0x80;
                owner_sprite->unk_0D.u = 0x80;
                owner_sprite->unk_0C.u = 0x80;
            }
            ((S_81814EDC_0_pre *)effect)[-1].unk_00 = (u16) (((S_81814EDC_0_pre *)effect)[-1].unk_00 | 0x8000);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}
