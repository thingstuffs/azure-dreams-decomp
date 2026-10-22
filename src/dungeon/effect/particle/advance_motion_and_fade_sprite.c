/* Staged target effects, moving sprite fades, linked quad rendering, and five-point animation. */
#include "dungeon/effect/particle/advance_motion_and_fade_sprite.h"
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/advance_motion_and_fade_sprite.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_effect_views.h"

typedef struct S_func_81856800_1 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union {
        s16 s16_0A;
        u16 u16_0A;
    } unk_0A;
    u8 pad_0C[0x44];
    union {
        s16 s16_50;
        u16 u16_50;
    } unk_50;
    union {
        s16 s16_52;
        u16 u16_52;
    } unk_52;
} S_func_81856800_1;

typedef struct S_func_81856800_2 {
    union {
        s32 s32_00;
        struct {
            u8 pad_00[0x2];
            u16 unk_02;
        } u16_02;
    } unk_00;
    union {
        s32 s32_04;
        struct {
            u8 pad_04[0x2];
            u16 unk_06;
        } u16_06;
    } unk_04;
    union {
        s32 s32_08;
        struct {
            u8 pad_08[0x2];
            u16 unk_0A;
        } u16_0A;
    } unk_08;
    union {
        s32 s32_0C;
        struct {
            u8 pad_0C[0x2];
            s16 unk_0E;
        } s16_0E;
    } unk_0C;
    union {
        s32 s32_10;
        struct {
            u8 pad_10[0x2];
            s16 unk_12;
        } s16_12;
    } unk_10;
    union {
        s32 s32_14;
        struct {
            u8 pad_14[0x2];
            s16 unk_16;
        } s16_16;
    } unk_14;
} S_func_81856800_2;

typedef struct S_func_81856800_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    union {
        s8 s8_72;
        u8 u8_72;
    } unk_72;
    union {
        s8 s8_73;
        u8 u8_73;
    } unk_73;
} S_func_81856800_3;

typedef struct S_func_81856800_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_func_81856800_4;



typedef struct S_func_81856800_6 {
    void * unk_00;
    union {
        u16 u16_04;
        u8 u8_04;
        struct {
            u8 pad_04[0x1];
            u8 unk_05;
        } u8_05;
    } unk_04;
    u16 unk_06;
    union {
        void * ptr_08;
        u16 u16_08;
    } unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x14];
    s32 unk_34;
    s16 unk_38;
    s16 unk_3A;
    s16 unk_3C;
    s16 unk_3E;
    u16 unk_40;
    s16 unk_42;
    u8 pad_44[0x2];
    u16 unk_46;
    u16 unk_48;
    u16 unk_4A;
} S_func_81856800_6;

typedef struct S_func_81856800_7 {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u16 unk_4A;
    u16 unk_4C;
} S_func_81856800_7;

typedef struct S_func_81856800_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_func_81856800_8;





typedef struct S_func_81856800_11 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
} S_func_81856800_11;


#ifdef __mips__
typedef union {
    long long value;
    struct {
        s32 hi;
        u32 lo;
    } words;
} MipsProduct;
#endif

extern s32 func_80069EF8(void);
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);

extern void apply_attack_power_and_element_effects(void *, s32, u8, s32, s32, void *, s32);


extern u8 D_800DEE38[];
extern u8 D_800DEC50[];
extern u8 D_800DEC70[];

extern void fade_packed_object_color_to_zero(void *);
extern void animate_jittering_five_point_effect();

void func_80024020(S_func_81856800_1 *action, S_func_81856800_2 *motion_arg);

/* Native module entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol add_flag_adjusted_target_value).  The state table of the switch below follows
 * it at 0x80024008 (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_1876800_entry)(S_func_81856800_1 *, S_func_81856800_2 *) = func_80024020;

/* Updates a staged movement effect, spawning particles and applying its final action. */
void func_80024020(S_func_81856800_1 *action, S_func_81856800_2 *motion_arg)
{
#ifdef __mips__
    S_func_81856800_2 *motion;
#else
    S_func_81856800_2 *motion;
#endif
    S_func_81856800_3 *object;
    MovingTile *owner;
    S_func_81856800_4 *object_base;
    S_func_81856800_4 *effect;
    S_func_81856800_6 *part;
#ifdef __mips__
    S_func_81856800_7 *particle_data;
#endif
    EffectObjectPayloadView *model;
    S_func_81856800_11 *src_point;
    s16 coord_offset[3];
    s32 state;
    s32 index;
    s32 target_height;
    s32 height_limit;
    s32 timer;
    s32 next_state;
    s32 next_timer;
    s32 page_or_magic;
    s32 t1_reserve;
    s32 t2_reserve;
    s32 t3_reserve;
    s32 t4_reserve;
    s32 t5_reserve;
    s32 t6_reserve;
    s32 t7_reserve;
    s32 t8_reserve;
    s32 t9_reserve;
    object = action->unk_00;
    state = action->unk_0A.s16_0A;
    owner = ((S_func_81856800_4 *)((u8 *)object - 32))->unk_0C;
    object_base = (S_func_81856800_4 *)((u8 *)object - 32);

    if (state != 0 && state != 5) {
        {
#ifndef __mips__
            S_func_81856800_7 *particle_data;
#endif
            s32 frame_index;
            u16 flags;

            index = 7;
            do {
                effect = allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
                if (effect != 0) {
                    particle_data = (S_func_81856800_7 *)((u8 *)effect + 32);
                    part = effect->unk_0C;
                    {
                        void *effect_type = advance_motion_and_fade_sprite;

                        effect->unk_10 = effect_type;
                    }
                    ((S_func_81856800_2 *)effect->unk_08)->unk_00.s32_00 =
                        motion_arg->unk_00.s32_00 +
                        (((func_80069EF8() & 0x1FF) - 255) << 13);
                    ((S_func_81856800_2 *)effect->unk_08)->unk_04.s32_04 =
                        motion_arg->unk_04.s32_04 +
                        (((func_80069EF8() & 0x1FF) - 255) << 13);
                    ((S_func_81856800_2 *)effect->unk_08)->unk_08.s32_08 =
                        motion_arg->unk_08.s32_08 -
                        (((func_80069EF8() & 0x1FF) - 255) << 14) +
                        (s32)0xFFE00000;
                    flags = part->unk_14;
                    part->unk_1E = 2048;
                    part->unk_1C = 2048;
                    flags |= 0xC;
                    part->unk_14 = flags;
                    if (index & 1) {
                        void *texture;

                        {

                            part->unk_10 = 32;
                            texture = D_800DEC70;
                            part->unk_0C = 0x00404040;
                        }
                        part->unk_00 = texture;
                        particle_data->unk_4A = 16;
                    } else {

                        {
                            s32 size;

                            size = 96;
                            part->unk_10 = size;
                        }
                        {
                            void *texture;

                            texture = D_800DEC50;
                            part->unk_00 = texture;
                        }
                        part->unk_0C = 0x00282828;
                        particle_data->unk_4A = 8;
                    }
                    {
                        S_func_81856800_8 *texture_data;

                        texture_data = part->unk_00;
                        texture_data = texture_data->unk_04;
                        part->unk_04.u8_04 = 0;
                        part->unk_04.u8_05.unk_05 = 0;
                        part->unk_08.ptr_08 = texture_data;
                    }
                    particle_data->unk_00 = action;
                    frame_index = func_80069EF8() & 3;
                    particle_data->unk_48 = frame_index;
                    particle_data->unk_4C = 0;
                }
                index--;
            } while (index >= 0);
        }
        state = action->unk_0A.s16_0A;
    }
    switch (state) {
    case 0:
    {
        u16 *control;

        control = action->unk_04;
        if ((control[0] & 0x80) == 0) {
            return;
        }
    }
        if (object->unk_60 == 0) {
            object->unk_72.u8_72 = owner->unk_24;
            object->unk_73.u8_73 = owner->unk_25;
        } else {


            part = ((S_func_81856800_4 *)((u8 *)object->unk_60 - 32))->unk_0C;
            object->unk_72.u8_72 = ((MovingTile *)part)->unk_24;
            object->unk_73.u8_73 = ((MovingTile *)part)->unk_25;
        }
        model = object_base->unk_0C;
        if (resolve_record_orientation_or_fallback(model->unk_08, model, coord_offset, 0) == 0) {
            coord_offset[2] = 0;
            coord_offset[1] = 0;
            coord_offset[0] = 0;
        }
        motion_arg->unk_00.u16_02.unk_02 = ((S_func_81856800_2 *)object_base->unk_08)->unk_00.u16_02.unk_02
            + coord_offset[0];
        motion_arg->unk_04.u16_06.unk_06 = ((S_func_81856800_2 *)object_base->unk_08)->unk_04.u16_06.unk_06
            + coord_offset[1];
        motion_arg->unk_08.u16_0A.unk_0A = ((S_func_81856800_2 *)object_base->unk_08)->unk_08.u16_0A.unk_0A
            + coord_offset[2];
        action->unk_50.u16_50 = 8;
        {
            s32 velocity;
            s32 position;

            velocity = object->unk_72.s8_72;
            velocity <<= 6;
            position = motion_arg->unk_00.u16_02.unk_02;
            position -= 32;
            velocity -= position;
            motion_arg->unk_0C.s16_0E.unk_0E = velocity;
        }
        {
            s32 quotient;

            quotient = motion_arg->unk_0C.s32_0C / action->unk_50.s16_50;
            motion_arg->unk_0C.s32_0C = quotient;
        }
        {
            s32 velocity;
            s16 position;

            velocity = object->unk_73.s8_73;
            velocity <<= 6;
            position = motion_arg->unk_04.u16_06.unk_06;
            position -= 32;
            motion_arg->unk_10.s16_12.unk_12 = (s16)velocity - position;
        }
        {
            s32 quotient;

            quotient = motion_arg->unk_10.s32_10 / action->unk_50.s16_50;
            motion_arg->unk_10.s32_10 = quotient;
        }
        height_limit = (s16)(((S_func_81856800_2 *)object_base->unk_08)->unk_08.u16_0A.unk_0A - 48);
        target_height = sample_terrain_surface_height(motion_arg->unk_00.u16_02.unk_02, motion_arg->unk_04.u16_06.unk_06, height_limit);
        motion_arg->unk_14.s16_16.unk_16 = target_height - motion_arg->unk_08.u16_0A.unk_0A;
        motion_arg->unk_14.s32_14 /= action->unk_50.s16_50;
        play_sound_if_enabled(0x300);
        next_state = action->unk_0A.u16_0A;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;

    case 1:
    {
        motion_arg->unk_00.s32_00 += motion_arg->unk_0C.s32_0C;
        motion_arg->unk_04.s32_04 += motion_arg->unk_10.s32_10;
        motion_arg->unk_08.s32_08 += motion_arg->unk_14.s32_14;
        timer = action->unk_50.u16_50 - 1;
        action->unk_50.u16_50 = timer;
        next_timer = 10;
        if ((s16)timer > 0) {
            return;
        }
        next_state = action->unk_0A.u16_0A;
        action->unk_50.u16_50 = next_timer;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;
    }

    case 2:
    {
        void *spawn_type;
        u8 *spawn_page;
        timer = action->unk_50.u16_50 - 1;
        action->unk_50.u16_50 = timer;
        if ((s16)timer > 0) {
            return;
        }
        if (object->unk_60 == 0) {
            action->unk_0A.u16_0A = 5;
            return;
        }
        index = 8;
        page_or_magic = (s32)0x80080000;
        spawn_type = animate_jittering_five_point_effect;

case2_spawn_loop:
        effect = allocate_list_node(0x201, (void *)(page_or_magic + 0x3498));
        if (effect != 0) {
            part = (S_func_81856800_6 *)((u8 *)effect + 32);
            effect->unk_10 = spawn_type;
            part->unk_48 = index;
            part->unk_04.u16_04 = motion_arg->unk_00.u16_02.unk_02;
            part->unk_06 = motion_arg->unk_04.u16_06.unk_06;
            part->unk_08.u16_08 = motion_arg->unk_08.u16_0A.unk_0A;
            part->unk_46 = 3;
            effect->unk_20 = action;
            part->unk_4A = 0;
        }
        index -= 4;
        if (index >= 0) {
            goto case2_spawn_loop;
        }
        next_state = action->unk_0A.u16_0A;
        next_timer = 8;
        action->unk_50.u16_50 = next_timer;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;
    }

    case 3:
    {
        s32 point_offset;
#ifdef __mips__
        S_func_81856800_11 *dst_point;
#else
        S_func_81856800_11 *dst_point;
#endif

        if (action->unk_50.s16_50 < 6) {
            effect = allocate_list_node(0x201, ((u8 *)(&scene_object_list_anchor)));
            if (effect != 0) {
                part = (S_func_81856800_6 *)((u8 *)effect + 32);
                effect->unk_10 = fade_packed_object_color_to_zero;
                register_node(effect, project_linked_shape_quads);
                part->unk_04.u16_04 =
                    motion_arg->unk_00.u16_02.unk_02 + (func_80069EF8() & 0x3F) - 32;
                part->unk_06 =
                    motion_arg->unk_04.u16_06.unk_06 + (func_80069EF8() & 0x3F) - 32;
                part->unk_08.u16_08 = motion_arg->unk_08.u16_0A.unk_0A;
                part->unk_40 = func_80066460(0, 3, 0x2C0, 0x100);
                part->unk_34 = 0x00707070;
                if (action->unk_50.u16_50 & 1) {
                    part->unk_38 = 0xA0;
                    part->unk_3A = 0;
                } else {
                    part->unk_38 = 0x80;
                    part->unk_3A = 32;
                }
                part->unk_3C = 0xBF;
                part->unk_3E = 0x1F;
                part->unk_42 = func_8006649C(0xA0, 0x1F7);
                part->unk_46 = 6;
                index = 1;
#ifdef __mips__
                page_or_magic = 0x19C2D14F;
#endif
                point_offset = 0;
                do {
                    dst_point = (S_func_81856800_11 *)((u8 *)part + index * 8);
                    src_point = (S_func_81856800_11 *)((u8 *)part + (index - 1) * 8);
#ifdef __mips__
                    {
                        MipsProduct product;
                        s32 mod_value;
                        s32 mod_sign;
                        s32 mod_quotient;

                        mod_value = func_80069EF8();
                        product.value = (long long)mod_value * page_or_magic;
                        mod_quotient = (product.words.hi >> 4) - ((s32)(mod_value >> 31));
                        mod_sign = (mod_quotient << 2) + mod_quotient;
                        mod_sign = (mod_sign << 5) - mod_quotient;
                        mod_quotient = src_point->unk_04;
                        mod_value -= mod_sign;
                        mod_quotient += mod_value;
                        mod_quotient -= 80;
                        dst_point->unk_04 = mod_quotient;
                    }
                    {
                        MipsProduct product;
                        s32 mod_value;
                        s32 mod_sign;
                        s32 mod_quotient;

                        mod_value = func_80069EF8();
                        product.value = (long long)mod_value * page_or_magic;

                        mod_quotient = (product.words.hi >> 4) - ((s32)(mod_value >> 31));
                        mod_sign = (mod_quotient << 2) + mod_quotient;
                        mod_sign = (mod_sign << 5) - mod_quotient;
                        mod_quotient = src_point->unk_06;
                        mod_value -= mod_sign;
                        mod_quotient += mod_value;
                        mod_quotient -= 80;
                        dst_point->unk_06 = mod_quotient;
                    }
#else
                    dst_point->unk_04 =
                        src_point->unk_04 + (func_80069EF8() % 159) - 80;
                    dst_point->unk_06 =
                        src_point->unk_06 + (func_80069EF8() % 159) - 80;

#endif
                    dst_point->unk_08 =
                        src_point->unk_08 - ((func_80069EF8() & 0x1F) + 20);
                    index++;
                } while (index < 5);
                part->unk_00 = action;
                part->unk_4A = 0;
            }
        }
    }
        timer = action->unk_50.u16_50 - 1;
        action->unk_50.u16_50 = timer;
        if ((s16)timer > 0) {
            return;
        }
        if (object->unk_60 != 0) {
            apply_attack_power_and_element_effects(object->unk_60, 10,
                          action->unk_09, 4,
                          object->unk_2A, object, 2);
        }
        next_state = action->unk_0A.u16_0A;
        next_timer = 10;
        action->unk_50.u16_50 = next_timer;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;

    case 4:
    {
#ifndef __mips__
        S_func_81856800_7 *particle_data;
#endif


        effect = allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
        if (effect != 0) {
            particle_data = (S_func_81856800_7 *)((u8 *)effect + 32);
            part = effect->unk_0C;
            effect->unk_10 = advance_motion_and_fade_sprite;
            ((S_func_81856800_2 *)effect->unk_08)->unk_00.s32_00 =
                motion_arg->unk_00.s32_00 +
                (((func_80069EF8() & 0x1FF) - 255) << 13);
            ((S_func_81856800_2 *)effect->unk_08)->unk_04.s32_04 =
                motion_arg->unk_04.s32_04 +
                (((func_80069EF8() & 0x1FF) - 255) << 13);
            ((S_func_81856800_2 *)effect->unk_08)->unk_08.s32_08 =
                motion_arg->unk_08.s32_08 -
                ((func_80069EF8() & 0x1FF) << 12) + (s32)0xFFE00000;
            part->unk_1E = 3072;
            part->unk_1C = 3072;
            part->unk_10 = 32;
            part->unk_00 = D_800DEE38;
            part->unk_0C = 0x00808080;
            part->unk_14 |= 0xC;
            particle_data->unk_4A = 8;
            {
                S_func_81856800_8 *texture_data;

                texture_data = part->unk_00;
                texture_data = texture_data->unk_04;
                part->unk_04.u8_04 = 0;
                part->unk_04.u8_05.unk_05 = 0;
                part->unk_08.ptr_08 = texture_data;
            }
            effect->unk_20 = action;
            particle_data->unk_48 = func_80069EF8() & 3;
            particle_data->unk_4C = 0;
        }
        timer = action->unk_50.u16_50 - 1;
        action->unk_50.u16_50 = timer;
        if ((s16)timer > 0) {
            return;
        }
        next_state = action->unk_0A.u16_0A;
        next_state++;
        action->unk_0A.u16_0A = next_state;
        return;
    }


    case 5:
    {
        s32 finish_flags;

        finish_flags = action->unk_52.s16_52;
        if (finish_flags & 0x8000) {
            action->unk_52.u16_52 &= 0x7FFF;
            return;
        }
        g_dungeon_status.active_actor = 0;
        ((u16 *)((u8 *)action - 2))[0] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    }
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/advance_motion_and_fade_sprite.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

/* Retail 81857050 (advance_motion_and_fade_sprite): updates the effect's motion, waits for its timer, then fades its sprite to
 * black and marks the effect (header and global flags) finished. */
void advance_motion_and_fade_sprite(EffectRecord *effect, EffectMotion *motion, SpriteEntry *sprite) {
    EffectOwner *owner = effect->owner;
    s32 z_velocity;
    s16 state;
    u16 timer;
    u8 brightness;

    owner->flags |= 0x8000;

    z_velocity = motion->vz;
    if (z_velocity != 0) {
        z_velocity -= 0x20000;
    }
    motion->vz = z_velocity;
    motion->x += motion->vx;
    motion->y += motion->vy;
    motion->z += motion->vz;

    state = effect->state;
    switch (state) {
    case 0:
        timer = effect->timer - 1;
        effect->timer = timer;
        if ((s16)timer <= 0) {
            register_node((ObjectNodeHeader *)effect - 1, (s32)project_sprite_chain);
            effect->state += 1;
        }
        break;

    case 1:
        advance_sprite_animation_and_textures(sprite);
        if (sprite->status & 0x6000) {
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
        }
        if (sprite->red <= effect->fade_step) {
            *(u32 *)&sprite->red = 0;
            ((ObjectNodeHeader *)effect - 1)->flags |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
        brightness = sprite->blue - effect->fade_step;
        sprite->blue = brightness;
        sprite->green = brightness;
        sprite->red = brightness;
        break;
    }
}
#include "modules/dungeon_native_abi.h"
#include "dungeon/effect/particle/advance_motion_and_fade_sprite.h"
#include "common.h"

typedef struct DungeonDrawState {
    u8 pad[0x8D0];
    u8 *next_primitive;
} DungeonDrawState;

typedef struct DungeonShape {
    u8 pad00[0x34];
    s32 unk34;
    u8 unk38;
    u8 pad39;
    u8 unk3A;
    u8 pad3B;
    u8 unk3C;
    u8 pad3D;
    u8 unk3E;
    u8 pad3F;
    u16 unk40;
    u16 unk42;
    u8 pad44[2];
    s16 unk46;
} DungeonShape;


extern DungeonDrawState *D_80083160[];
extern s32 func_80065420(void *world_vertex, void *screen_point, void *ptr2, void *ptr3);
extern void func_80066640(void *primitive, s32 value);
extern void func_800666F4(void *primitive);

typedef struct DungeonTag {
    unsigned addr : 24;
    unsigned len : 8;
} DungeonTag;

#define PRIM_U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define PRIM_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define PRIM_U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))

#ifdef __mips__
typedef union DungeonSignedProduct {
    signed long long value;
    struct {
        s32 hi;
        u32 lo;
    } word;
} DungeonSignedProduct;
#endif

/* Project linked shapes and queue four textured quads for each visible shape. */
s32 project_linked_shape_quads(void *shape_data)
{
    u16 points[5][2];
    s32 half_width;
    DungeonShape *shape;
    DungeonDrawState **draw_state_p = D_80083160;
    s32 depth_or_tag_mask;
    s32 y_span;
    s32 width_divisor;
    s32 point_index;
    s32 scaled_depth;
#ifdef __mips__
    DungeonSignedProduct depth_product;
    s32 depth_sign;
#endif

    do {
        shape = (DungeonShape *)shape_data;
        depth_or_tag_mask = 0;
        point_index = 4;
        for (; point_index >= 0; point_index--) {
            s32 point_depth;
            s32 biased_depth_sum;

            point_depth = func_80065420((u8 *)shape + 4 + point_index * 8, points[point_index],
                                   &half_width, &half_width);
            biased_depth_sum = depth_or_tag_mask - 8;
            depth_or_tag_mask = biased_depth_sum + point_depth;
        }

        y_span = (s16)points[0][1];
        y_span = y_span - (s16)points[4][1];
        width_divisor = shape->unk46;
        y_span = abs(y_span);
        y_span = y_span / (width_divisor + 2);
#ifdef __mips__
        depth_product.value = (signed long long)depth_or_tag_mask * 0x66666667;
        depth_sign = depth_or_tag_mask >> 31;
        scaled_depth = depth_product.word.hi >> 1;
        depth_or_tag_mask = scaled_depth - depth_sign;
#else
        depth_or_tag_mask = depth_or_tag_mask / 5;
#endif
        half_width = y_span;

        if ((u32)depth_or_tag_mask < 0x1E0) {
            point_index = 0;
            {
                s32 ordering_offset = depth_or_tag_mask * 4;

                do {
                    DungeonDrawState *draw_state = *draw_state_p;
                    u8 *primitive = draw_state->next_primitive;
                    s32 next_index;
                    u16 *current_point;
                    register u16 *next_point;
                    u16 texture_attr;
                    u16 start_x;
                    u16 width_u16;
                    u16 start_y;
                    u16 end_y;
                    u8 tex_coord;
                    u8 tex_coord2;
                    u8 tex_coord3;
                    u8 tex_span;

                    draw_state->next_primitive = primitive + 0x28;
                    PRIM_U32(primitive, 4) = shape->unk34;
                    func_800666F4(primitive);
                    func_80066640(primitive, 1);

                    current_point = points[point_index];
                    texture_attr = shape->unk40;
                    next_index = point_index + 1;
                    PRIM_U16(primitive, 0x16) = texture_attr;
                    texture_attr = shape->unk42;
                    PRIM_U16(primitive, 0x0E) = texture_attr;

                    start_x = current_point[0];
                    width_u16 = *(u16 *)(void *)&half_width;
                    next_point = points[next_index];
                    PRIM_U16(primitive, 0x08) = start_x - width_u16;
                    PRIM_U16(primitive, 0x10) = next_point[0] - width_u16;
                    PRIM_U16(primitive, 0x18) = current_point[0] + width_u16;
                    PRIM_U16(primitive, 0x20) = next_point[0] + width_u16;

                    start_y = current_point[1];
                    PRIM_U16(primitive, 0x1A) = start_y;
                    PRIM_U16(primitive, 0x0A) = start_y;
                    end_y = next_point[1];
                    PRIM_U16(primitive, 0x22) = end_y;
                    PRIM_U16(primitive, 0x12) = end_y;

                    tex_coord = shape->unk38;
                    PRIM_U8(primitive, 0x1C) = tex_coord;
                    PRIM_U8(primitive, 0x0C) = tex_coord;
                    tex_span = shape->unk3C;
                    tex_coord2 = tex_coord + tex_span;
                    PRIM_U8(primitive, 0x24) = tex_coord2;
                    PRIM_U8(primitive, 0x14) = tex_coord2;

                    tex_coord2 = shape->unk3A;
                    PRIM_U8(primitive, 0x25) = tex_coord2;
                    PRIM_U8(primitive, 0x1D) = tex_coord2;
                    tex_span = shape->unk3E;
                    tex_coord3 = tex_coord2 + tex_span;
                    PRIM_U8(primitive, 0x15) = tex_coord3;
                    PRIM_U8(primitive, 0x0D) = tex_coord3;

                    ((DungeonTag *)primitive)->addr =
                        ((DungeonTag *)((u8 *)ordering_offset + (u32)*draw_state_p + 0xB0))->addr;
                    ((DungeonTag *)((u8 *)ordering_offset + (u32)*draw_state_p + 0xB0))->addr = (u32)primitive;

                    point_index = next_index;
                } while (point_index < 4);
            }
        }
        scaled_depth = *(s32 *)((u8 *)shape_data - 8);
        if (scaled_depth == 0) {
            break;
        }
        shape_data = (u8 *)scaled_depth + 0x20;
    } while (1);
    return 0;
}
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} Point;

typedef struct {
    void *object;
    Point points[5];
    u8 pad2C[8];
    s32 value34;
    s16 field38;
    s16 field3A;
    s16 field3C;
    s16 field3E;
    s16 field40;
    s16 field42;
    s16 delta44;
    s16 pad46;
    u16 timer48;
    s16 state4A;
} Entity;

extern s16 func_80066460(s32, s32, s32, s32);
extern s16 func_8006649C(s32, s32);
extern s32 rand();


/* Initializes, animates, and retires a jittering five-point effect. */
void animate_jittering_five_point_effect(Entity *entity)
{
    s32 point_index;
    s16 state;
    s32 jitter_coord;
    s16 random_value;

    *(u16 *)((u8 *)entity->object + 0x52) |= 0x8000;
    state = entity->state4A;
    switch (state) {
    case 0:
        entity->timer48--;
        if ((s16)entity->timer48 > 0) {
            return;
        }
        {
            void *entity_base;
            entity_base = (u8 *)entity - 0x20;
            register_node(entity_base, (s32)project_linked_shape_quads);
        }
        entity->value34 = 0x00C0C0C0;
        entity->field40 = func_80066460(0, 1, 0x2C0, 0x100);
        random_value = func_8006649C(0xA0, 0x1F7);
        point_index = 1;
        {
            entity->field42 = random_value;
            entity->field3E = 0x1F;
            entity->field3C = 0x1F;
            entity->field38 = 0x80;
            entity->timer48 = 0;
            entity->field3A = 0;
            entity->delta44 = -0x1C;
            do {
                entity->points[point_index].x = entity->points[0].x;
                entity->points[point_index].y = entity->points[0].y;
                entity->points[point_index].z = entity->points[0].z + entity->delta44 * point_index;
                point_index++;
            } while (point_index < 5);
        }
        state = (u16)entity->state4A + 1;
        entity->state4A = state;
        return;
    case 1:
        point_index = 1;
        if ((s16)entity->timer48 < 6) {
            do {
                jitter_coord = entity->points[0].x + rand() % 95 - 0x30;
                entity->points[point_index].x = jitter_coord;
                jitter_coord = entity->points[0].y + rand() % 95 - 0x30;
                entity->points[point_index].y = jitter_coord;
                point_index++;
            } while (point_index < 5);
            point_index = 1;
        } else {
            while (point_index < 5) {
                point_index++;
            }
        }
        point_index = 1;
        do {
            entity->points[point_index].z = entity->points[0].z + entity->delta44 * point_index;
            point_index++;
        } while (point_index < 5);
        {
            s32 update_value;
            s32 timer_bits;
            jitter_coord = entity->timer48;
            update_value = (u16)entity->delta44;
            jitter_coord++;
            entity->timer48 = jitter_coord;
            jitter_coord <<= 1;
            timer_bits = entity->timer48;
            update_value -= jitter_coord;
            entity->delta44 = update_value;
            entity->field38 = ((timer_bits & 3) << 5) + 0x80;
            entity->field3A = ((s16)entity->timer48 >> 2) << 5;
            if ((s16)entity->timer48 >= 8) {
                entity->value34 = 0;
                state = (u16)entity->state4A + 1;
                entity->state4A = state;
                return;
            }
            update_value = 0xFFEFEFF0;
            entity->value34 += update_value;
            return;
        }
    case 2:
    {
        u32 *flags_page;
        flags_page = (u32 *)0x80080000;
        *(u16 *)((u8 *)entity - 2) |= 0x8000;
        flags_page[0x528] |= 0x8000;
    }
        return;
    }
}
#include "modules/dungeon_native_abi.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"



typedef struct S_80024F40_0 {
    void * unk_00;
    u8 pad_04[0x30];
    union { u8 u8; s32 s32; } unk_34;   /* accessed as both */
    u8 pad_38[0xA];
    s16 unk_42;
    u8 pad_44[0x6];
    union { s16 s; u16 u; } unk_4A;   /* accessed as both */
} S_80024F40_0;   /* arg0 in fade_packed_object_color_to_zero */

typedef struct S_80024F40_1 {
    u8 pad_00[0x52];
    u16 unk_52;
} S_80024F40_1;

s16 func_8006649C();
s32 func_80069EF8();

/* Fades the object's packed color to zero, then sets completion flags. */
void fade_packed_object_color_to_zero(void *object) {
    s16 fade_state;
    void *linked_object;

    linked_object = ((S_80024F40_0 *)object)->unk_00;
    ((S_80024F40_1 *)linked_object)->unk_52 =
        (u16)(((S_80024F40_1 *)linked_object)->unk_52 | 0x8000);
    ((S_80024F40_0 *)object)->unk_42 =
        func_8006649C((func_80069EF8() & 0xF) * 0x10, 0x1F8);
    fade_state = ((S_80024F40_0 *)object)->unk_4A.s;
    switch (fade_state) {
    case 0:
        if ((u8)((S_80024F40_0 *)object)->unk_34.u8 < 0x31U) {
            ((S_80024F40_0 *)object)->unk_34.s32 = 0;
            ((S_80024F40_0 *)object)->unk_4A.u++;
            return;
        }
        ((S_80024F40_0 *)object)->unk_34.s32 = ((S_80024F40_0 *)object)->unk_34.s32 - 0x303030;
        break;
    case 1:
        (*(u16 *)((u8 *)object + -2)) =
            (u16)(((u16 *)object)[-1] | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    }
}
