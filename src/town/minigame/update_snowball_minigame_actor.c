#include "common.h"
#include "town/scene/collection.h"
#include "town/minigame.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity_objects.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "town/person/position.h"
#include "engine/node.h"
#include "engine/runtime.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "slus.h"
#include "town/player/position.h"
#include "town/scene/object.h"

#ifndef NULL
#define NULL 0
#endif





extern volatile u16 snowball_best_score;
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

/* Updates actor movement, animation, scoring, and departure through its state sequence. */
void update_snowball_minigame_actor(TownCollectionActor *object, ObjectPosition *motion, SpriteFrameState *sprite)
{
    u8 *effect;
    TownCollectionSequence *actor;
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
    if (object->state.s < 0xFF) {
        s32 actor_state;

        actor = object->sequence;
        actor_state = actor->state.s;
        if (actor_state == 0xFF) {
            object->state.s = actor_state;
        }
    }
    add_motion_deltas_to_position(motion);
    if (motion->z.w.i >= ground_height) {
        motion->z.w.i = ground_height;
    }
    advance_sprite_animation_and_textures(sprite);

    state = object->state.s;
    state_bits = object->state.u;
    switch (state) {
    case 0:
        motion->x.v = 0x03A00000;
        motion->y.v = 0x01E00000;
        motion->z.w.i = query_lowered_transform_position(motion);
        object->unk_15 = 0;
        object->timer.u = 0x40;
        object->state.s = 1;
                        /* fall through */

    case 1:
        if (sprite->flags & 0x6000) {
            motion->velocity_y = 0x80000;
            effect = D_800F2DC0;
        }
        if (object->flags & 1) {
            u16 timer;

            timer = object->timer.u - 1;
            object->timer.u = timer;
            if ((s16)timer >= 0) {
                motion->x.v =
                    (rsin((s16)timer << 7) << 7) + 0x03A00000;
            }
        }
        if (motion->y.v > 0x0477FFFF) {
            effect = D_800F2E08;
            sprite->flags |= 1;
            motion->velocity_x = 0x80000;
            object->state.s = 2;
        }
        break;

    case 2:
        if (sprite->flags & 0x6000) {
            effect = D_800F2E98;
        }
        if (motion->y.v > 0x048FFFFF) {
            effect = D_800F2E50;
            motion->velocity_y = 0;
            object->state.s = 3;
        }
        break;

    case 3:
        if (sprite->flags & 0x6000) {
            effect = D_800F2E98;
        }
        if (motion->x.v > 0x03DFFFFF) {
            effect = D_800F2F28;
            motion->velocity_z = -0x100000;
            object->state.s = 4;
        }
        break;

    case 4:
    {
        s32 x;

        x = motion->x.v;
        motion->velocity_z += 0x48000;
        if (x > 0x041FFFFF) {
            motion->velocity_z = 0;
            motion->velocity_x = 0;
            object->unk_15 = 1;
            object->state.s = 5;
        }
    }
        break;

    case 5:
        if (*music == D_80092698) {
            object->timer.u = 7;
            *music = tracked_actor_callback_address;
            object->unk_15 = 0;
            object->state.s = 6;
        }
        break;

    case 6:
    {
        ObjectPosition *target;
        s32 target_height;
        s32 base_height;

        target = &view_reference_entity;
        motion->velocity_x =
            (target->x.v - motion->x.v) >> 1;
        motion->velocity_y =
            (target->y.v - motion->y.v) >> 1;
        target_height = target->z.v + town_target_height_offset;
        base_height = motion->z.v + 0x80000;
        motion->velocity_z = (target_height - base_height) >> 1;
        add_motion_deltas_to_position(motion);
        *music = tracked_actor_callback_address;
        (*(u16 *)((u8 *)object + 0x6C))--;
        if ((s16)object->timer.u <= 0) {
            *music = tracked_actor_callback_address;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            object->state.s = 7;
        }
    }
        break;

    case 7:
    case 8:
    case 9:
    {
        ObjectPosition *target;

        target = &view_reference_entity;
        motion->x.v = target->x.v;
        (*(s32 *)((u8 *)motion + 4)) = target->y.v;
        motion->z.v =
            target->z.v + town_target_height_offset - 0x80000;
        if ((world->pressed_buttons) & 0x40) {
            if (target->z.w.i == 0) {
                if (object->state.s == 9) {
                    actor->speed = 0x100000;
                    effect = D_800F2FE0;
                } else {
                    *music = town_actor_interaction_address;
                    motion->velocity_z = 0x100000;
                }
                actor->flags.u &= 0xFFFB;
                object->state.u++;
            } else {
                *music = tracked_actor_callback_address;
            }
            if (object->state.s == 0xA) {
                SD_Call(0x700);
            }
        }
    }
        break;

    case 10:
    {
        s32 velocity_y;
        s32 x;

        motion->velocity_x =
            (actor->speed >> 12) *
            rsin(actor->angle.s);
        velocity_y = ((-actor->speed) >> 12) *
            rcos(actor->angle.s);
        motion->velocity_y = velocity_y;
        if (velocity_y > -0x40000) {
            motion->velocity_y = -0x40000;
        }
        actor->angle.s =
            actor->angle.u - ((s16)actor->angle_step.u >> 4);

        if (motion->z.v > 0) {
            u16 flags;

            flags = actor->flags.u;
            if (!(flags & 4)) {
                actor->flags.u = flags | 4;
                SD_Call(0x701);
            }
            x = motion->x.v;
            motion->z.v = 0x200000;
            if (x <= 0x041FFFFF) {
                if (x <= 0x03BFFFFF) {
                    if (x <= 0x03800000) {
                        motion->x.v = 0x03880000;
                    }
                } else {
                    motion->x.v = 0x03B80000;
                }
            } else {
                if (x > 0x04BFFFFF) {
                    motion->x.v = 0x04B80000;
                } else if (x <= 0x04800000) {
                    motion->x.v = 0x04880000;
                }
            }
            actor->angle.s = -actor->angle.s >> 1;
        }

        if (motion->y.v <= 0x01E00000) {
            s32 terrain;

            SD_Call(0x1700);
            SD_Call(0x1701);
            terrain = D_800272A0[actor->round_index.s];
            if (terrain == 8) {
                s32 scale;
                u8 *particle_data;

                SD_Call(0x505);
                index = 1;
                scale = 0x1000;
                particle_data = D_80022B80;
                object->flags |= 1;
                do {
                    ObjectNodeHeader *particle;

                    particle = allocate_list_node(0x136, &scene_object_list_anchor.next);
                    if (particle != NULL) {
                        SpriteFrameState *part;
                        SceneEffectCopyObject *link;

                        part = particle->sprite;
                        register_node(particle, project_sprite_chain);
                        link = (SceneEffectCopyObject *)((u8 *)particle + 0x20);
                        part->color.word = 0x00808080;
                        part->scale_y = scale;
                        part->scale_x = scale;
                        link->source = motion;
                        link->timer.s = 0x78;
                        particle->update_callback = particle_data;
                        select_record_entry_and_value(part, snowball_actor_sprites, (s16)(index * 4));
                    }
                    index--;
                } while (index >= 0);
            } else {
                object->flags &= -2;
            }
            effect = D_800F2F80;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            object->timer.u = 0x14;
            object->state.s = 0xB;
        }
    }
        break;

    case 11:
    {
        u16 flags;
        s32 y;
        s32 x;

        flags = sprite->flags;
        if ((flags & 0x6000) && object->timer.s > 0) {
            effect = D_800F2DC0;
            sprite->flags = flags | 0x800;
        }
        if (motion->x.v > 0x03A00000) {
            sprite->flags &= 0xFFFE;
        } else {
            sprite->flags |= 1;
        }
        y = motion->y.v;
        motion->y.v = y + ((0x01E00000 - y) >> 1);
        {
            s16 timer = object->timer.u - 1;

            object->timer.s = timer;
            if (timer == 0) {
                s32 actor_x;

                sprite->flags &= 0xF7FF;
                actor_x = motion->x.v;
                if (actor_x > 0x03A80000) {
                    motion->velocity_x = -0x80000;
                } else if (actor_x <= 0x0397FFFF) {
                    motion->velocity_x = 0x80000;
                } else {
                    effect = D_800F2E50;
                    motion->velocity_x = 0;
                    motion->x.v = 0x03A00000;
                }
            }
        }
        if ((u32)(motion->x.v - 0x03BC0000) <= 0xC80000) {
            motion->z.v = 0;
        } else {
            motion->z.v = 0x200000;
        }
        {
            s32 center_dist;

            center_dist = motion->x.v;
            center_dist = center_dist - 0x03A00000;
            center_dist = abs(center_dist);
            if (center_dist <= 0x80000 && object->timer.s < 0) {
                actor->flags.u |= 2;
                motion->velocity_z = 0;
                motion->velocity_y = 0;
                motion->velocity_x = 0;
                object->state.s = 0;
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
            s16 best_score = snowball_best_score;
            s32 zero = 0;

            if (best_score < score_total || score_total == 0x40) {
                sound_set_cd_cue_parameters(zero, 0x2C3D, 0x01000001, 0x01000271);
                SD_Call(0x300);
                snowball_best_score = score_total;
                set_resident_bit(0x5DA);
            } else {
                sound_set_cd_cue_parameters(zero, 0x2C3D, zero, 0x01000290);
                SD_Call(0x300);
                clear_resident_bit(0x5DA);
            }
        }
        effect = D_800F2DC0;
        motion->velocity_y = 0x80000;
        object->timer.u = 0x1E;
        object->state.u++;
    }
                        /* fall through */

    case 0x100:
    case 0x102:
        object->timer.u--;
        if ((s16)object->timer.u <= 0) {
            motion->velocity_y = 0;
            motion->velocity_z = -0x100000;
            object->state.u++;
        }
        break;

    case 0x101:
    case 0x103:
    {
        s32 height;

        height = motion->z.v;
        motion->velocity_z += 0x20000;
        if (height > 0x1FFFFF) {
            motion->z.v = 0x200000;
            motion->velocity_z = 0;
            object->state.u++;
        }
    }
        break;

    case 0x104:
        effect = D_800F2E08;
        object->state.s = state_bits + 1;
        break;

    case 0x105:
        effect = D_800F2E50;
        object->state.s = state_bits + 1;
        break;

    case 0x106:
        effect = D_800F2E98;
        object->state.s = state_bits + 1;
        break;

    case 0x107:
        motion->velocity_y = -0x80000;
        sprite->tpage_abr = 0x60;
        sprite->color.word = 0x00C0C0C0;
        sprite->flags |= 0xC;
        effect = D_800F2EE0;
        object->state.u++;
        break;

    case 0x108:
        sprite->color.word += -0x80808;
        if ((u8)*(u32 *)&sprite->color.word < 0x11) {
            object->state.u++;
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
