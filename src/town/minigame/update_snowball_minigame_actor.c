#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
extern int abs(int);

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80020DF0_0 {
    u8 pad_00[0x15];
    s8 unk_15;
    u8 pad_16[0x52];
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x2];
    union { u16 s; s16 u; } unk_6C;   /* accessed as both */
    u8 pad_6E[0x3A];
    s32 unk_A8;
    void * unk_AC;
} S_80020DF0_0;   /* arg0 in update_snowball_minigame_actor */

typedef struct S_80020DF0_1 {
    s32 unk_00;
    u8 pad_04[0x26];
    u16 unk_2A;
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u16 unk_2E;
    u8 pad_30[0x4];
    s16 unk_34;
    s16 unk_36;
} S_80020DF0_1;   /* actor in update_snowball_minigame_actor */

typedef struct S_80020DF0_2 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80020DF0_2;   /* arg1 in update_snowball_minigame_actor */

typedef struct S_80020DF0_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    void * unk_04;
} S_80020DF0_8;   /* link in update_snowball_minigame_actor */

extern volatile u16 D_800135C0;
extern u8 D_80022B80[];
extern s16 D_800272A0[];
extern void *scene_object_payload_alias;
extern s32 town_target_height_offset;
extern u8 D_80092698[];
extern u8 tracked_actor_callback_address[];
extern u8 town_actor_interaction_address[];
extern u8 D_800F2DC0[];
extern u8 D_800F2E08[];
extern u8 D_800F2E50[];
extern u8 D_800F2E98[];
extern u8 D_800F2EE0[];
extern u8 D_800F2F28[];
extern u8 D_800F2F80[];
extern u8 D_800F2FE0[];
extern u8 snowball_actor_sprites[];

extern void clear_resident_bit(s32);
extern void set_resident_bit(s32);
extern void select_record_entry_and_value(void *, void *, s32);
extern void sound_set_cd_cue_parameters(s32, s32, s32, s32);
extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void advance_sprite_animation_and_textures(void *);
extern void SD_Call(s32);
extern s32 rsin(s32);
extern s32 rcos(s32);
extern void unlink_scene_list_node(void *);
extern void add_motion_deltas_to_position(void *);
extern s32 query_lowered_transform_position(void *);

/* Updates actor movement, animation, scoring, and departure through its state sequence. */
void update_snowball_minigame_actor(void *object, void *motion, SpriteFrameState *sprite)
{
    u8 *effect;
    void *actor;
    s32 ground_height;
    s16 state;
    u16 state_bits;
    GameWork *world;
    void **music;
    s32 index;

    effect = NULL;
    actor = NULL;
    world = &g_game_work;
    music = &scene_object_payload_alias;

    ground_height = (s16)query_lowered_transform_position(motion);
    if (((S_80020DF0_0 *)object)->unk_68.s < 0xFF) {
        s32 actor_state;

        actor = ((S_80020DF0_0 *)object)->unk_AC;
        actor_state = ((S_80020DF0_1 *)actor)->unk_36;
        if (actor_state == 0xFF) {
            ((S_80020DF0_0 *)object)->unk_68.s = actor_state;
        }
    }
    add_motion_deltas_to_position(motion);
    if (((S_80020DF0_2 *)motion)->unk_08.at02.v >= ground_height) {
        ((S_80020DF0_2 *)motion)->unk_08.at02.v = ground_height;
    }
    advance_sprite_animation_and_textures(sprite);

    state = ((S_80020DF0_0 *)object)->unk_68.s;
    state_bits = ((S_80020DF0_0 *)object)->unk_68.u;
    switch (state) {
    case 0:
        ((S_80020DF0_2 *)motion)->unk_00 = 0x03A00000;
        ((S_80020DF0_2 *)motion)->unk_04 = 0x01E00000;
        ((S_80020DF0_2 *)motion)->unk_08.at02.v = query_lowered_transform_position(motion);
        ((S_80020DF0_0 *)object)->unk_15 = 0;
        ((S_80020DF0_0 *)object)->unk_6C.s = 0x40;
        ((S_80020DF0_0 *)object)->unk_68.s = 1;
                        /* fall through */

    case 1:
        if (sprite->flags & 0x6000) {
            ((S_80020DF0_2 *)motion)->unk_10 = 0x80000;
            effect = D_800F2DC0;
        }
        if (((S_80020DF0_0 *)object)->unk_A8 & 1) {
            u16 timer;

            timer = ((S_80020DF0_0 *)object)->unk_6C.s - 1;
            ((S_80020DF0_0 *)object)->unk_6C.s = timer;
            if ((s16)timer >= 0) {
                ((S_80020DF0_2 *)motion)->unk_00 =
                    (rsin((s16)timer << 7) << 7) + 0x03A00000;
            }
        }
        if (((S_80020DF0_2 *)motion)->unk_04 > 0x0477FFFF) {
            effect = D_800F2E08;
            sprite->flags |= 1;
            ((S_80020DF0_2 *)motion)->unk_0C = 0x80000;
            ((S_80020DF0_0 *)object)->unk_68.s = 2;
        }
        break;

    case 2:
        if (sprite->flags & 0x6000) {
            effect = D_800F2E98;
        }
        if (((S_80020DF0_2 *)motion)->unk_04 > 0x048FFFFF) {
            effect = D_800F2E50;
            ((S_80020DF0_2 *)motion)->unk_10 = 0;
            ((S_80020DF0_0 *)object)->unk_68.s = 3;
        }
        break;

    case 3:
        if (sprite->flags & 0x6000) {
            effect = D_800F2E98;
        }
        if (((S_80020DF0_2 *)motion)->unk_00 > 0x03DFFFFF) {
            effect = D_800F2F28;
            ((S_80020DF0_2 *)motion)->unk_14 = -0x100000;
            ((S_80020DF0_0 *)object)->unk_68.s = 4;
        }
        break;

    case 4:
    {
        s32 x;

        x = ((S_80020DF0_2 *)motion)->unk_00;
        ((S_80020DF0_2 *)motion)->unk_14 += 0x48000;
        if (x > 0x041FFFFF) {
            ((S_80020DF0_2 *)motion)->unk_14 = 0;
            ((S_80020DF0_2 *)motion)->unk_0C = 0;
            ((S_80020DF0_0 *)object)->unk_15 = 1;
            ((S_80020DF0_0 *)object)->unk_68.s = 5;
        }
    }
        break;

    case 5:
        if (*music == D_80092698) {
            ((S_80020DF0_0 *)object)->unk_6C.s = 7;
            *music = tracked_actor_callback_address;
            ((S_80020DF0_0 *)object)->unk_15 = 0;
            ((S_80020DF0_0 *)object)->unk_68.s = 6;
        }
        break;

    case 6:
    {
        ObjectPosition *target;
        s32 target_height;
        s32 base_height;

        target = &view_reference_entity;
        (*(s32 *)((u8 *)motion + 0xC)) =
            (target->x.v - ((S_80020DF0_2 *)motion)->unk_00) >> 1;
        (*(s32 *)((u8 *)motion + 0x10)) =
            (target->y.v - ((S_80020DF0_2 *)motion)->unk_04) >> 1;
        target_height = target->z.v + town_target_height_offset;
        base_height = ((S_80020DF0_2 *)motion)->unk_08.at00.v + 0x80000;
        ((S_80020DF0_2 *)motion)->unk_14 = (target_height - base_height) >> 1;
        add_motion_deltas_to_position(motion);
        *music = tracked_actor_callback_address;
        (*(u16 *)((u8 *)object + 0x6C))--;
        if ((s16)((S_80020DF0_0 *)object)->unk_6C.s <= 0) {
            *music = tracked_actor_callback_address;
            ((S_80020DF0_2 *)motion)->unk_14 = 0;
            ((S_80020DF0_2 *)motion)->unk_10 = 0;
            ((S_80020DF0_2 *)motion)->unk_0C = 0;
            ((S_80020DF0_0 *)object)->unk_68.s = 7;
        }
    }
        break;

    case 7:
    case 8:
    case 9:
    {
        ObjectPosition *target;

        target = &view_reference_entity;
        (*(s32 *)((u8 *)motion + 0)) = target->x.v;
        (*(s32 *)((u8 *)motion + 4)) = target->y.v;
        (*(s32 *)((u8 *)motion + 8)) =
            target->z.v + town_target_height_offset - 0x80000;
        if (((s32)world->pressed_buttons) & 0x40) {
            if (target->z.w.i == 0) {
                if (((S_80020DF0_0 *)object)->unk_68.s == 9) {
                    ((S_80020DF0_1 *)actor)->unk_00 = 0x100000;
                    effect = D_800F2FE0;
                } else {
                    *music = town_actor_interaction_address;
                    ((S_80020DF0_2 *)motion)->unk_14 = 0x100000;
                }
                ((S_80020DF0_1 *)actor)->unk_2A &= 0xFFFB;
                ((S_80020DF0_0 *)object)->unk_68.u++;
            } else {
                *music = tracked_actor_callback_address;
            }
            if (((S_80020DF0_0 *)object)->unk_68.s == 0xA) {
                SD_Call(0x700);
            }
        }
    }
        break;

    case 10:
    {
        s32 velocity_y;
        s32 x;

        ((S_80020DF0_2 *)motion)->unk_0C =
            (((S_80020DF0_1 *)actor)->unk_00 >> 12) *
            rsin(((S_80020DF0_1 *)actor)->unk_2C.s);
        velocity_y = ((-((S_80020DF0_1 *)actor)->unk_00) >> 12) *
            rcos(((S_80020DF0_1 *)actor)->unk_2C.s);
        ((S_80020DF0_2 *)motion)->unk_10 = velocity_y;
        if (velocity_y > -0x40000) {
            ((S_80020DF0_2 *)motion)->unk_10 = -0x40000;
        }
        ((S_80020DF0_1 *)actor)->unk_2C.s =
            ((S_80020DF0_1 *)actor)->unk_2C.u - ((s16)((S_80020DF0_1 *)actor)->unk_2E >> 4);

        if (((S_80020DF0_2 *)motion)->unk_08.at00.v > 0) {
            u16 flags;

            flags = ((S_80020DF0_1 *)actor)->unk_2A;
            if (!(flags & 4)) {
                ((S_80020DF0_1 *)actor)->unk_2A = flags | 4;
                SD_Call(0x701);
            }
            x = ((S_80020DF0_2 *)motion)->unk_00;
            ((S_80020DF0_2 *)motion)->unk_08.at00.v = 0x200000;
            if (x <= 0x041FFFFF) {
                if (x <= 0x03BFFFFF) {
                    if (x <= 0x03800000) {
                        ((S_80020DF0_2 *)motion)->unk_00 = 0x03880000;
                    }
                } else {
                    ((S_80020DF0_2 *)motion)->unk_00 = 0x03B80000;
                }
            } else {
                if (x > 0x04BFFFFF) {
                    ((S_80020DF0_2 *)motion)->unk_00 = 0x04B80000;
                } else if (x <= 0x04800000) {
                    ((S_80020DF0_2 *)motion)->unk_00 = 0x04880000;
                }
            }
            ((S_80020DF0_1 *)actor)->unk_2C.s = -((S_80020DF0_1 *)actor)->unk_2C.s >> 1;
        }

        if (((S_80020DF0_2 *)motion)->unk_04 <= 0x01E00000) {
            s32 terrain;

            SD_Call(0x1700);
            SD_Call(0x1701);
            terrain = D_800272A0[((S_80020DF0_1 *)actor)->unk_34];
            if (terrain == 8) {
                s32 scale;
                u8 *particle_data;

                SD_Call(0x505);
                index = 1;
                scale = 0x1000;
                particle_data = D_80022B80;
                ((S_80020DF0_0 *)object)->unk_A8 |= 1;
                do {
                    ObjectNodeHeader *particle;

                    particle = allocate_list_node(0x136, ((u8 *)(&scene_object_list_anchor)));
                    if (particle != NULL) {
                        SpriteFrameState *part;
                        void *link;

                        part = particle->sprite;
                        register_node(particle, project_sprite_chain);
                        link = (u8 *)particle + 0x20;
                        part->color.word = 0x00808080;
                        part->scale_y = scale;
                        part->scale_x = scale;
                        ((S_80020DF0_8 *)link)->unk_04 = motion;
                        ((S_80020DF0_8 *)link)->unk_02 = 0x78;
                        particle->update_callback = particle_data;
                        select_record_entry_and_value(part, snowball_actor_sprites, (s16)(index * 4));
                    }
                    index--;
                } while (index >= 0);
            } else {
                ((S_80020DF0_0 *)object)->unk_A8 &= -2;
            }
            effect = D_800F2F80;
            ((S_80020DF0_2 *)motion)->unk_14 = 0;
            ((S_80020DF0_2 *)motion)->unk_10 = 0;
            ((S_80020DF0_2 *)motion)->unk_0C = 0;
            ((S_80020DF0_0 *)object)->unk_6C.s = 0x14;
            ((S_80020DF0_0 *)object)->unk_68.s = 0xB;
        }
    }
        break;

    case 11:
    {
        u16 flags;
        s32 y;
        s32 x;

        flags = sprite->flags;
        if ((flags & 0x6000) && ((S_80020DF0_0 *)object)->unk_6C.u > 0) {
            effect = D_800F2DC0;
            sprite->flags = flags | 0x800;
        }
        if (((S_80020DF0_2 *)motion)->unk_00 > 0x03A00000) {
            sprite->flags &= 0xFFFE;
        } else {
            sprite->flags |= 1;
        }
        y = ((S_80020DF0_2 *)motion)->unk_04;
        ((S_80020DF0_2 *)motion)->unk_04 = y + ((0x01E00000 - y) >> 1);
        {
            s16 timer = ((S_80020DF0_0 *)object)->unk_6C.s - 1;

            ((S_80020DF0_0 *)object)->unk_6C.u = timer;
            if (timer == 0) {
                s32 x;

                sprite->flags &= 0xF7FF;
                x = ((S_80020DF0_2 *)motion)->unk_00;
                if (x > 0x03A80000) {
                    ((S_80020DF0_2 *)motion)->unk_0C = -0x80000;
                } else if (x <= 0x0397FFFF) {
                    ((S_80020DF0_2 *)motion)->unk_0C = 0x80000;
                } else {
                    effect = D_800F2E50;
                    ((S_80020DF0_2 *)motion)->unk_0C = 0;
                    ((S_80020DF0_2 *)motion)->unk_00 = 0x03A00000;
                }
            }
        }
        if ((u32)(((S_80020DF0_2 *)motion)->unk_00 - 0x03BC0000) <= 0xC80000) {
            ((S_80020DF0_2 *)motion)->unk_08.at00.v = 0;
        } else {
            ((S_80020DF0_2 *)motion)->unk_08.at00.v = 0x200000;
        }
        {
            s32 center_dist;

            center_dist = ((S_80020DF0_2 *)motion)->unk_00;
            center_dist = center_dist - 0x03A00000;
            center_dist = abs(center_dist);
            if (center_dist <= 0x80000 && ((S_80020DF0_0 *)object)->unk_6C.u < 0) {
                ((S_80020DF0_1 *)actor)->unk_2A |= 2;
                ((S_80020DF0_2 *)motion)->unk_14 = 0;
                ((S_80020DF0_2 *)motion)->unk_10 = 0;
                ((S_80020DF0_2 *)motion)->unk_0C = 0;
                ((S_80020DF0_0 *)object)->unk_68.s = 0;
            }
        }
    }
        break;

    case 0xFF:
    {
        s32 score_total;
        s16 *score_table;
        s16 *score_entry;

        score_total = 0;
        index = 7;
        score_table = D_800272A0;
        score_entry = score_table + 7;
        do {
            score_total += *score_entry;
            score_entry--;
            index--;
        } while (index >= 0);

        {
            s16 best_score = D_800135C0;
            s32 zero = 0;

            if (best_score < score_total || score_total == 0x40) {
                sound_set_cd_cue_parameters(zero, 0x2C3D, 0x01000001, 0x01000271);
                SD_Call(0x300);
                D_800135C0 = score_total;
                set_resident_bit(0x5DA);
            } else {
                sound_set_cd_cue_parameters(zero, 0x2C3D, zero, 0x01000290);
                SD_Call(0x300);
                clear_resident_bit(0x5DA);
            }
        }
        effect = D_800F2DC0;
        ((S_80020DF0_2 *)motion)->unk_10 = 0x80000;
        ((S_80020DF0_0 *)object)->unk_6C.s = 0x1E;
        ((S_80020DF0_0 *)object)->unk_68.u++;
    }
                        /* fall through */

    case 0x100:
    case 0x102:
        ((S_80020DF0_0 *)object)->unk_6C.s--;
        if ((s16)((S_80020DF0_0 *)object)->unk_6C.s <= 0) {
            ((S_80020DF0_2 *)motion)->unk_10 = 0;
            ((S_80020DF0_2 *)motion)->unk_14 = -0x100000;
            ((S_80020DF0_0 *)object)->unk_68.u++;
        }
        break;

    case 0x101:
    case 0x103:
    {
        s32 height;

        height = ((S_80020DF0_2 *)motion)->unk_08.at00.v;
        ((S_80020DF0_2 *)motion)->unk_14 += 0x20000;
        if (height > 0x1FFFFF) {
            ((S_80020DF0_2 *)motion)->unk_08.at00.v = 0x200000;
            ((S_80020DF0_2 *)motion)->unk_14 = 0;
            ((S_80020DF0_0 *)object)->unk_68.u++;
        }
    }
        break;

    case 0x104:
        effect = D_800F2E08;
        ((S_80020DF0_0 *)object)->unk_68.s = state_bits + 1;
        break;

    case 0x105:
        effect = D_800F2E50;
        ((S_80020DF0_0 *)object)->unk_68.s = state_bits + 1;
        break;

    case 0x106:
        effect = D_800F2E98;
        ((S_80020DF0_0 *)object)->unk_68.s = state_bits + 1;
        break;

    case 0x107:
        ((S_80020DF0_2 *)motion)->unk_10 = -0x80000;
        sprite->tpage_abr = 0x60;
        sprite->color.word = 0x00C0C0C0;
        sprite->flags |= 0xC;
        effect = D_800F2EE0;
        ((S_80020DF0_0 *)object)->unk_68.u++;
        break;

    case 0x108:
        sprite->color.word += -0x80808;
        if ((u8)*(u32 *)&sprite->color.word < 0x11) {
            ((S_80020DF0_0 *)object)->unk_68.u++;
        }
        break;

    case 0x109:
        unlink_scene_list_node(object);
        (*(u16 *)((u8 *)object + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;

    default:
        break;
    }

    if (effect != NULL) {
        select_record_entry_and_value(sprite, effect, 0);
    }

    return;
}
