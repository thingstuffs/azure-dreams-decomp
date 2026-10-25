#include "sdk/libc.h"
#include "shared/audio_commands.h"
#include "dungeon/actor/motion.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
/* Snowman actor spawning, movement, spell and attack sequences, and particle effects. */
#include "dungeon/monster/snowman.h"
#include "shared/actor_action_flags.h"
#include "shared/monster_ids.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"
#include "shared/tile_object.h"

void * (*const resource10_slot0_entry0)(s16 flags, s16 kind_id, s16 variant, s32 spawn_value) = create_actor_with_optional_status;
void (*const resource10_slot0_entry1)(u8 *actor, u8 *motion, u8 *object) = update_actor_callbacks_animation_and_ground;

/* Projects linked effect positions and queues their colored pixel and drawing-mode packets by depth. */
s32 draw_snowman_point_chain(u8 *node_data, u16 *position)
{
    R10_8017092C_Scratch *scratch = (R10_8017092C_Scratch *)0x1F800000;
    void **global_state = ((void **)(&g_game_work));
    GpuContext *render_state = (GpuContext *)global_state[0];
    R10_8017092C_Packet *first_packet = (R10_8017092C_Packet *)render_state->packetCursor;
    R10_8017092C_Packet *packet;
    R10_8017092C_Packet *mode_packet;
    s32 depth_index;
    u32 addr_mask = 0x00FFFFFF;
    u32 length_mask = 0xFF000000;

    scratch->table = (u8 *)render_state + 0xB0;
    scratch->current = (u8 *)first_packet;
    for (;;) {
        scratch->in0 = position[1];
        packet = (R10_8017092C_Packet *)scratch->current;
        scratch->in1 = position[3];
        scratch->in2 = position[5];

        scratch->current = (u8 *)packet + 0xC;
        depth_index = RotTransPers(&scratch->in0, (u8 *)packet + 8,
                              &scratch->out0, &scratch->out1);
        scratch->index = depth_index;

        if ((u32)depth_index < 480U) {
            u16 tpage;
            u8 r;
            u8 g;
            u8 b;

            packet->data.link = *(u32 *)(node_data + 8);
            packet->code = 2;
            r = packet->data.color.r;
            g = packet->data.color.g;
            b = packet->data.color.b;
            packet->data.color.r = r;
            packet->data.color.g = g;
            packet->data.color.b = b;
            packet->data.color.command = 106;

            *(u32 *)packet = (*(u32 *)packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    ((u32)packet & addr_mask);

            mode_packet = (R10_8017092C_Packet *)scratch->current;
            scratch->current = (u8 *)mode_packet + 0xC;
            tpage = (u16)GetTPage(0, 1, 0, 0);
            SetDrawMode(mode_packet, 0, 0,(u16)(tpage), 0);

            *(u32 *)mode_packet = (*(u32 *)mode_packet & length_mask) |
                          (((u32 *)scratch->table)[scratch->index] & addr_mask);
            mode_packet = (R10_8017092C_Packet *)((u32)mode_packet & addr_mask);
            ((u32 *)scratch->table)[scratch->index] =
                                    (((u32 *)scratch->table)[scratch->index] & length_mask) |
                                    (u32)mode_packet;
        }

        {
            u8 *next_node = *(u8 **)(node_data - 8);

            if (next_node == 0)
                break;
            node_data = next_node + 0x20;
            position = (u16 *)*(u8 **)(next_node + 8);
        }
    }

    ((GpuContext *)global_state[0])->packetCursor = scratch->current;
    return 0;
}


/* Moves and accelerates the sprite, shrinks and fades it, and expires it near the target or on timeout. */void move_and_shrink_fading_effect(R10_80170B0C_Actor *actor, R10_80170B0C_Vec3 *vec, SpriteFrameState *sprite)
{
    s32 distance_x;
    s32 distance_y;
    u16 reduced_size;
    u16 sprite_size;

    vec->xyz[0] += actor->pos[0];
    vec->xyz[1] += actor->pos[1];
    vec->xyz[2] += actor->pos[2];
    actor->pos[0] += actor->vel[0];
    actor->pos[1] += actor->vel[1];
    actor->pos[2] += actor->vel[2];

    distance_x = __builtin_abs(actor->x - *(s16 *)((u8 *)vec + 2));
    if (distance_x < 0x10) {
        distance_y = __builtin_abs(actor->y - *(s16 *)((u8 *)vec + 6));
        if (distance_y < 0x10) {
            *(u16 *)((u8 *)actor - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }

    sprite->color.c.r = actor->color[0] * actor->scale / actor->divisor;
    sprite->color.c.g = actor->color[1] * actor->scale / actor->divisor;
    sprite_size = sprite->scale_x;
    reduced_size = sprite_size - 0xC8;
    sprite_size = reduced_size;
    sprite->color.c.b = actor->color[2] * actor->scale / actor->divisor;
    if ((s16)reduced_size < 0) {
        sprite_size = 0;
    }
    sprite->scale_x = sprite_size;
    sprite->scale_y = sprite_size;
    actor->scale = (u16)actor->scale - 8;
    advance_sprite_animation_and_textures(sprite);
    if (actor->scale <= 0) {
        *(u16 *)((u8 *)actor - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a timed sprite offset from its owner with motion that converges toward the source position. */
void create_converging_fading_sprite(
    R10_80170CF8_S_80AC55DC_1 *origin, s16 effect_id, s32 effect_value, s16 duration,
    s32 offset_x, s32 offset_y, s32 offset_z)
{
    ObjectNodeHeader *node;
    R10_80170CF8_S_80AC55DC_2 *work;
    SpriteFrameState *sprite;
    u16 sprite_flags;
    s32 step_x;
    s32 step_y;
    s32 step_z;
    s32 t;

    node = allocate_flagged_object_node(0x212);
    if (node != 0) {
        node->update_callback = ((u8 *)move_and_shrink_fading_effect);

        (node->position)->x.w.i =
            ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_02 + offset_x;
        (node->position)->y.w.i =
            ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_06 + offset_y;
        (node->position)->z.w.i =
            ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_0A + offset_z - 0x14;

        work = (R10_80170CF8_S_80AC55DC_2 *)((u8 *)node + 0x20);
        work->unk_36 = ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_02;
        work->unk_38 = ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_06;
        work->unk_3A = ((R10_80170CF8_S_80AC55DC_6 *)(origin->unk_08))->unk_0A;
        step_x = -(offset_x << 16) / (duration / 8);
        work->unk_40 = step_x / 2;
        step_y = -(offset_y << 16) / (duration / 8);
        work->unk_44 = step_y / 2;
        step_z = -(offset_z << 16) / (duration / 8);
        t = step_z / 2;
        work->unk_48 = t;
        t = step_x;
        if (t < 0) {
            t += 3;
        }
        work->unk_4C = t >> 2;
        work->unk_50 = step_y / 4;
        work->unk_54 = step_z / 4;

        work->unk_14 = effect_id;
        work->unk_32 = duration;
        work->unk_34 = duration;
        register_node(node, project_sprite_chain);

        sprite = node->sprite;
        sprite_flags = sprite->flags;
        sprite->tpage_abr = 0x20;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0;
        sprite->color.c.g = 0;
        sprite->color.c.r = 0;
        sprite->flags = sprite_flags | 0xC;
        ((R10_80170CF8_S_80AC55DC_0 *)node)->unk_20 = effect_value;
        work->unk_08 = effect_value;
        select_record_entry_and_value(sprite, ((u8 *)shared_sprite_entries), 0);
    }
}


/* Creates a Snowman actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_actor_with_optional_status(s16 flags, s16 kind_id, s16 variant, s32 spawn_value)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    void *result;
    ObjectNodeHeader *object;
    ObjectPosition *part0;
    SpriteFrameState *part1;
    R10_80170F3C_S_80170F3C_4 *result_copy;

    result = 0;
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != 0) {
        result = (u8 *)object;
        result += 0x20;
        object->update_callback = ((u8 *)update_actor_callbacks_animation_and_ground);
        ((R10_80170F3C_S_80170F3C_1 *)result)->unk_13 = MONSTER_SNOWMAN;
        register_node(object, project_sprite_chain);

        {
            void *handler;

            part0 = object->position;
            handler = ((u8 *)snowman_direction_frames);
            part0->z.w.i = spawn_value;
            part1 = object->sprite;
            kind = flags & 3;
            part1->tile_y = variant;
            result_copy = result;
            part1->frameTable = handler;
        }
        part1->tile_x = kind_id;

        if (kind == 1) {
            flags0 = ((ObjectNodeHeader *)result)->unk_14;
            flags1 = *(s32 *)&((ObjectNodeHeader *)result)->pad_1C;
            flags0 |= 0x6000;
            flags1 |= 0x6000;
            ((ObjectNodeHeader *)result)->unk_14 = flags0;
            *(s32 *)&((ObjectNodeHeader *)result)->pad_1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((ObjectNodeHeader *)result)->unk_14;
            flags1 = *(s32 *)&((ObjectNodeHeader *)result)->pad_1C;
            flags0 |= 0x2000;
            flags1 |= 0x2000;
            ((ObjectNodeHeader *)result)->unk_14 = flags0;
            *(s32 *)&((ObjectNodeHeader *)result)->pad_1C = flags1;
        } else if (((flags & -4) << 16) == 0 &&
                   (((ObjectNodeHeader *)result)->unk_14 & ACTOR_RESIST_SLEEP) == 0 &&
                   (generate_random_value() & 1) != 0) {
            set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
            part1->frameTable = ((u8 *)snowman_alt_direction_frames);
        }

        initialize_actor_sprite_and_animation(object, part0, part1,(s16)(flags));
        result_copy->unk_9A = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C = ((void *)update_snowman_behavior);
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }

    return result;
}

/* MECHANISM: 2.7.2-cdk-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   kind_id and variant arrive as s16: their narrowing copies survive cse, combine folds the a1/a2 temps
   into them, so sched1 schedules the parameter copies and the entry order is retail's. */

/* Runs actor callbacks, cycles its idle hop animation, and updates facing, motion, and ground contact. */
void update_actor_callbacks_animation_and_ground(u8 *actor, u8 *motion, u8 *object)
{
    u8 *actor_copy;
    R10_80171104_ActorCallback callback;
    s16 old_direction;
    s16 timer;
    u16 flags;
    s16 height_delta;
    s16 floor_height;
    s16 actor_height;
    s16 view_index_copy;
    u8 *animation;
    s32 shifted_direction;

    actor_copy = actor;

    if (g_dungeon_status.flags & 0x2000) {
        R10_80171104_ActorCallback early_callback;
        void *early_actor;

        early_callback = (*(R10_80171104_ActorCallback *)((u8 *)actor + 0x8C));
        if (early_callback == (R10_80171104_ActorCallback)((void *)update_snowman_behavior)) {
            early_actor = actor;
            early_callback(early_actor, motion, object, early_actor);
            return;
        }
        (*(u8 *)((u8 *)actor + 0x71)) &= 0x7F;
        return;
    }

    old_direction = (*(s8 *)((u8 *)actor + 0x6D));
    if (refresh_actor_facing_and_lifecycle(actor, motion, object, actor) != 0) {
        return;
    }

    callback = (*(R10_80171104_ActorCallback *)((u8 *)actor + 0x8C));
    if (callback != 0) {
        callback(actor, motion, object, actor);
    }
    ((R10_80171104_ActorCallback *)D_80175A1C)[(*(u8 *)((u8 *)actor + 0x9A))](actor, motion, object, actor);

    if ((*(u8 *)((u8 *)actor + 0x9A)) != 0xE ||
        (((SpriteAnimationTableView *)object)->flags & 0x40) ||
        ((*(u32 *)((u8 *)actor + 0x1C)) & 0x20)) {
        shifted_direction = (s32)old_direction << 16;
    } else {
        if (((SpriteAnimationTableView *)object)->frame_table != ((u8 *)snowman_direction_frames) &&
            ((SpriteAnimationTableView *)object)->frame_table != ((u8 *)snowman_frame_set_2) &&
            ((SpriteAnimationTableView *)object)->frame_table != ((u8 *)snowman_frame_set) &&
            ((SpriteAnimationTableView *)object)->frame_table != ((u8 *)snowman_frame_set_3)) {
            (*(u8 **)((u8 *)object + 0x2C)) = ((u8 *)snowman_direction_frames);
            select_sprite_entry(object,
                ((u8 *)snowman_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7], 0);
            (*(u16 *)((u8 *)actor + 0x9E)) = 0;
            (*(s16 *)((u8 *)actor + 0xA0)) = 10;
        }

        if (((SpriteAnimationTableView *)object)->frame_table == ((u8 *)snowman_direction_frames)) {
            timer = (*(u16 *)((u8 *)actor + 0x9E));
            (*(u16 *)((u8 *)actor + 0x9E)) = timer + 1;
            if (timer >= (*(s16 *)((u8 *)actor + 0xA0))) {
                (*(u8 **)((u8 *)object + 0x2C)) = ((u8 *)snowman_frame_set_2);
                select_sprite_entry(object,
                    ((u8 *)snowman_frame_set_2)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
                advance_sprite_animation_and_textures(object);
                (*(s16 *)((u8 *)actor + 0xA0)) = 3;
            }
        }

        if (((SpriteAnimationTableView *)object)->frame_table == ((u8 *)snowman_frame_set_2)) {
            timer = (*(u16 *)((u8 *)actor + 0xA0)) - 1;
            (*(s16 *)((u8 *)actor + 0xA0)) = timer;
            if ((timer << 16) <= 0 &&
                (((SpriteAnimationTableView *)object)->flags & 0xE000)) {
                (*(u8 **)((u8 *)object + 0x2C)) = ((u8 *)snowman_frame_set);
                select_sprite_entry(object,
                    ((u8 *)snowman_frame_set)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
                advance_sprite_animation_and_textures(object);
                (*(s16 *)((u8 *)actor + 0xA0)) = 6;
                (*(s32 *)((u8 *)actor + 0x90)) += 0xFFE00000;
                ((R10_80171104_S_80171104_2 *)motion)->unk_14 = 0;
                (*(s8 *)((u8 *)actor + 0x9D)) = 0;
            }
        }

        if (((SpriteAnimationTableView *)object)->frame_table == ((u8 *)snowman_frame_set)) {
            timer = (*(u16 *)((u8 *)actor + 0xA0)) - 1;
            (*(s16 *)((u8 *)actor + 0xA0)) = timer;
            if ((timer << 16) <= 0 &&
                (((SpriteAnimationTableView *)object)->flags & 0xE000)) {
                (*(u8 **)((u8 *)object + 0x2C)) = ((u8 *)snowman_frame_set_3);
                select_sprite_entry(object,
                    ((u8 *)snowman_frame_set_3)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7], 0);
                advance_sprite_animation_and_textures(object);
                (*(s16 *)((u8 *)actor + 0xA0)) = 3;
            }
        }

        if (((SpriteAnimationTableView *)object)->frame_table != ((u8 *)snowman_frame_set_3)) {
            shifted_direction = (s32)old_direction << 16;
        } else {
            timer = (*(u16 *)((u8 *)actor + 0xA0)) - 1;
            (*(s16 *)((u8 *)actor + 0xA0)) = timer;
            if ((timer << 16) > 0) {
                shifted_direction = (s32)old_direction << 16;
            } else {
                if (((SpriteAnimationTableView *)object)->flags & 0xE000) {
                    (*(u8 **)((u8 *)object + 0x2C)) = ((u8 *)snowman_direction_frames);
                    select_sprite_entry(object,
                        ((u8 *)snowman_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100)
                            >> 9) & 7], 0);
                    (*(u16 *)((u8 *)actor + 0x9E)) = 0;
                    (*(s16 *)((u8 *)actor + 0xA0)) = 20;
                }
                shifted_direction = (s32)old_direction << 16;
            }
        }
    }

    if ((shifted_direction >> 16) != ((R10_80171104_S_80171104_1 *)actor_copy)->unk_6D) {
        try_move_actor_to_valid_position(actor, motion, object, actor_copy);
    }

    flags = ((SpriteAnimationTableView *)object)->flags;
    if (!(flags & 0x8000)) {
        s16 view_index;
        s32 old_direction;

        old_direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80171104_S_80171104_1 *)actor_copy)->unk_2A + 0x100) >> 9) & 7;
        view_index = old_direction;
        view_index_copy = old_direction;
        if ((*(s16 *)((u8 *)actor + 0x94)) != view_index) {
            animation = ((SpriteAnimationTableView *)object)->frame_table;
            if (animation != 0) {
                select_indirect_table_entry(object, animation[view_index], ((SpriteAnimationTableView *)object)->frame_index);
            }
            (*(s16 *)((u8 *)actor + 0x94)) = old_direction;
        }

        if (dir_sprite_flag[view_index_copy] != 0) {
            ((SpriteAnimationTableView *)object)->flags |= 1;
        } else {
            ((SpriteAnimationTableView *)object)->flags &= 0xFFFE;
        }
        if (!(((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u & 0x20)) {
            if (!(((SpriteAnimationTableView *)object)->flags & 0x40)) {
                advance_sprite_animation_and_textures(object);
            }
        } else {
            ((SpriteAnimationTableView *)object)->flags |= 0x7000;
        }
        apply_monster_koyaw_data(((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.s, object + 0xC);
    } else if (flags & 0x800) {
        ((SpriteAnimationTableView *)object)->flags = flags & 0x8FFF;
    } else {
        ((SpriteAnimationTableView *)object)->flags = flags | 0x7000;
    }

    ((R10_80171104_S_80171104_2 *)motion)->unk_00.at00.v += ((R10_80171104_S_80171104_2 *)motion)->unk_0C;
    ((R10_80171104_S_80171104_2 *)motion)->unk_04.at00.v += ((R10_80171104_S_80171104_2 *)motion)->unk_10;

    if ((*(u16 *)((u8 *)actor + 0x98)) & 8) {
        (*(s8 *)((u8 *)actor + 0x9D)) = 0;
    } else {
        ((R10_80171104_S_80171104_2 *)motion)->unk_14 += (*(s8 *)((u8 *)actor + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)actor + 0x9D))++;
    }
    (*(s32 *)((u8 *)actor + 0x90)) += ((R10_80171104_S_80171104_2 *)motion)->unk_14;

    if (!((*(u16 *)((u8 *)actor + 0x98)) & 4)) {
        floor_height = ((s16)sample_terrain_surface_height(((R10_80171104_S_80171104_2 *)motion)->unk_00.at02.v, ((R10_80171104_S_80171104_2 *)motion)->unk_04.at02.v,(s16)((s16)(((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u - 0x20))));
        if (floor_height < 0x200) {
            actor_height = ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.s;
            if ((*(s16 *)((u8 *)actor + 0x92)) + actor_height < floor_height) {
                ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)actor + 0x90)) = 0;
                } else {
                    height_delta = floor_height - ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u;
                    (*(s16 *)((u8 *)actor + 0x92)) = height_delta;
                }
                ((R10_80171104_S_80171104_2 *)motion)->unk_14 = 0;
                ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u |= 0x08000000;
                (*(s8 *)((u8 *)actor + 0x9D)) = 0;
            }

            if (((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u & 0x40000000) {
                ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u &= 0xBFFFFFFF;
                floor_height = ((s16)sample_terrain_surface_height((((SpriteAnimationTableView *)object)->tile_x << 6) | 0x20,
                                       (((SpriteAnimationTableView *)object)->tile_y << 6) | 0x20,(s16)((s16)(((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u - 0x20))));
                (*(s16 *)((u8 *)actor + 0x92)) += ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u - floor_height;
                ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.s = floor_height;
            }
        } else {
            ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u &= 0xF7FFFFFF;
        }
    } else {
        ((R10_80171104_S_80171104_1 *)actor_copy)->unk_1C.u &= 0xF7FFFFFF;
    }

    ((R10_80171104_S_80171104_2 *)motion)->unk_0A = ((R10_80171104_S_80171104_1 *)actor_copy)->unk_88.u + (*(s16 *)((u8 *)actor + 0x92));
    ((SpriteAnimationTableView *)object)->flags |= 0x40;

    return;
}

/* Selects movement, attacks, and spells from actor status, MP, and its position relative to the player. */
void update_snowman_behavior(void *actor_arg, void *context_arg, SpriteFrameState *sprite_arg, ActorRecord *entity_arg)
{
    s32 direction_aux;
    s32 tile_record;
    u16 action_state;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xE;
        advance_snowman_stored_path(actor_arg, context_arg, sprite_arg, entity_arg);
        return;
    }

    if (entity_arg->mp == 0) {
        u8 *animations;

        advance_actor_pending_action(actor_arg, context_arg, sprite_arg, entity_arg);
        if (sprite_arg->frameTable == ((u8 *)snowman_alt_direction_frames)) {
            return;
        }
        animations = ((u8 *)D_801759E0);
        sprite_arg->frameTable = animations;
        select_sprite_entry(sprite_arg,
            animations[((g_game_work.view.camera_rotation.parts.viewAngle + entity_arg->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity_arg->flags1C) & ACTOR_ASLEEP) {
        if (sprite_arg->frameTable == ((u8 *)snowman_alt_direction_frames)) {
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_8C = 0;
            entity_arg->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor_arg, context_arg, sprite_arg, ((u8 *)D_801759E0)) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity_arg->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                u8 *animations = ((u8 *)snowman_direction_frames);

                if (sprite_arg->frameTable != animations) {
                    sprite_arg->frameTable = animations;
                    select_sprite_entry(sprite_arg,
                        animations[((g_game_work.view.camera_rotation.parts.viewAngle + entity_arg->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = next_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_98 &= 0xFFF3;

        if (entity_arg->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor_arg, context_arg, sprite_arg, ((u8 *)D_80175998)) != 0) {
                return;
            }
        }

        if (((u32)entity_arg->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor_arg, context_arg, sprite_arg, entity_arg);
            update_snowman_parent_motion(actor_arg, context_arg, sprite_arg, entity_arg);
            sprite_arg->frameTable = ((u8 *)snowman_direction_frames);
            select_sprite_entry(sprite_arg,
                ((u8 *)snowman_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + entity_arg->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((s16)can_entity_gain_level(entity_arg) != 0) {
            if ((s16)process_selected_actor_record(actor_arg, context_arg, sprite_arg, entity_arg) != 0) {
                wait_for_snowman_action_slot(actor_arg, context_arg, sprite_arg, entity_arg);
            }
        }
    }

    tile_record = find_active_rect_containing_point(sprite_arg->tile_x,
        sprite_arg->tile_y);
    sprite_arg->room_index = tile_record;

    if (entity_arg->pending_turn_updates > 0) {
        if (((u32)entity_arg->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(entity_arg);
            return;
        }
        if (*(u16 *)&sprite_arg->tile_x == reference_tile_object . tile_position . word ) {
            choose_snowman_move(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        }
        if (!(entity_arg->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(entity_arg,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)relink_snowman_path(actor_arg, context_arg, sprite_arg, 0) == 0) {
                return;
            }
            action_state = entity_arg->action_flags | 0x4000;
            entity_arg->action_flags = action_state;
            if (!(action_state & 0x8000)) {
                choose_snowman_move(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
            }
        }

        switch (entity_arg->action_flags & ACTOR_ACTION_CODE_MASK) {
        case 8:
            if ((s16)try_snowman_attack(actor_arg, context_arg, sprite_arg, entity_arg) != 0) {
                return;
            }
            begin_snowman_attack(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        case 9:
            select_actor_target_and_advance_status(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        case 5:
        case 6:
        case 7:
            {
                ActorRecord *player;
                s16 direction;

                direction = get_rounded_facing_and_rounding_flag((s16)sprite_arg->tile_x,(s16)sprite_arg->tile_y,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                    &direction_aux);
                player = primary_actor_record;
                entity_arg->facing = direction;
                if (player->action_id == 0x11) {
                    begin_actor_spell_action(actor_arg, context_arg, sprite_arg, ((u8 *)D_801759D0), ((void *)update_snowman_behavior));
                    return;
                }
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_mp(entity_arg);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_arg, context_arg, sprite_arg, ((u8 *)D_801759D0), ((void *)update_snowman_behavior));
            return;
        default:
            choose_snowman_move(actor_arg, context_arg, sprite_arg, entity_arg);
            return;
        }
    }

    if (!(((u32)entity_arg->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) ||
            !(dungeon_rooms[record_index].flags & 2)) {
            if (!(((u32)entity_arg->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((s16)test_neighbor_position_relation(
                        sprite_arg->tile_x, sprite_arg->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    entity_arg->facing = get_rounded_facing_and_rounding_flag((s16)sprite_arg->tile_x,(s16)sprite_arg->tile_y,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                        &direction_aux);
                }
            }
        }
    }
}

/* Advances one stored path step, updates occupied tiles and facing, and selects the movement animation and
 * delay. */
void advance_snowman_stored_path(void *movement, void *motion, SpriteFrameState *entity, void *path_state) {
    void *state = path_state;
    s32 move_flags;
    s16 heading;
    s16 move_result;
    s16 x;
    s32 y;

    if (((R10_80171D7C_S_80171CD4_0 *)state)->unk_71.s <= 0) {
        return;
    }

    if (((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 != 0xF) {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_90 = 0;
        ((Rec_func_80171CD4_arg1 *)motion)->unk_14 = 0;
        ((Rec_func_80171CD4_arg0 *)movement)->unk_9D = 0;
    }

    if (((R10_80171D7C_S_80171CD4_0 *)state)->unk_71.u <= ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s) {
        return;
    }

    if (*(u8 **)&entity->frameTable != ((u8 *)snowman_move_direction_frames)) {
        entity->frameTable = ((u8 *)snowman_move_direction_frames);
        select_sprite_entry(
            entity,
            ((u8 *)snowman_move_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = entity->tile_x;
    y = entity->tile_y;
    move_flags = 0x3000;
    if (((R10_80171D7C_S_80171CD4_0 *)state)->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, move_flags);

    heading = ((s16)get_rounded_facing_and_rounding_flag(
        x,
        y,
        ((R10_80171D7C_S_80171CD4_4 *)((u8 *)state + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s))->unk_74,
        ((R10_80171D7C_S_80171CD4_4 *)((u8 *)state + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)movement + 0x98));
    move_result = ((s16)check_movement_clearance_and_height(heading, entity, state, 0x20));

    entity->tile_x =
        ((R10_80171D7C_S_80171CD4_4 *)((u8 *)state + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s))->unk_74;
    move_flags = 0x3000;
    entity->tile_y =
        ((R10_80171D7C_S_80171CD4_4 *)((u8 *)state + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s))->unk_7C;
    ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.u++;

    {
        s32 next_x = entity->tile_x;
        s32 next_y = entity->tile_y;

        if (((R10_80171D7C_S_80171CD4_0 *)state)->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        cycle_map_cell_flags(next_x, next_y, move_flags);
    }

    ((R10_80171D7C_S_80171CD4_0 *)state)->unk_2A = heading;
    if (move_result == 3) {
        if (!(g_dungeon_status.flags & 0x80) && !(entity->flags & 0x8000)) {
            begin_snowman_step_animation(movement, motion, entity, state);
            ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
        } else {
            ((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 = 0xF;
            ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
        }
    } else {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 = 0xF;
        ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 0;
        return;
    }

    ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 8;
    {
        s32 step_count = ((R10_80171D7C_S_80171CD4_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 8 / step_count;
        }
    }
}

/* Chooses a clear step or attack, records the actor's path, and updates occupied tiles and movement
 * counts. */
void choose_snowman_move(void *move_data, void *context, SpriteFrameState *position_data, void *actor_data)
{
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;

    if ((dungeon_flags & 0x4000) || ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.s >= 0) {
        if (((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_12 >= 2 ||
            (s16)try_snowman_attack(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, (u8 *)move_data + 0x9C);
    actor_flags = ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_data,(u8)position_data->tile_x,(u8)position_data->tile_y);
            if (((void *)current_angle) != 0) {
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)position_data->tile_x,(s16)position_data->tile_y,(s16)(((R10_80171FE8_S_80171C34_7 *)(((R10_80171FE8_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_24),(s16)(((R10_80171FE8_S_80171C34_7 *)(((R10_80171FE8_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_25),
                    (u8 *)move_data + 0x98));
                ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_14 & 0x80000000)) {
                ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_14 |= 0x80000000;
                ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.u +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (probe_directional_neighbor(actor_data,(u8)position_data->tile_x,(u8)position_data->tile_y,(s16)(((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.s)) != 0) {
                ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_45 + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (position_data->tile_x == (u16)target_x &&
                    position_data->tile_y == (u16)target_y) {
                    ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }

                turn_data = (u8 *)move_data + 0x98;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)position_data->tile_x,(s16)position_data->tile_y,(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                if (((s16)check_movement_clearance_and_height((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)position_data->tile_x,(s16)position_data->tile_y,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)test_neighbor_position_relation(
                        position_data->tile_x, position_data->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                select_actor_route_target(position_data, ((R10_80171FE8_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (*(s8 *)&position_data->room_index >= 0 &&
               ((R10_80171FE8_DungeonRecord *)dungeon_rooms)[*(s8 *)&position_data->room_index].flags & 2) {
        select_actor_route_target(position_data, ((R10_80171FE8_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)probe_directional_neighbor(actor_data,(u8)position_data->tile_x,(u8)position_data->tile_y,(s16)(((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.s));
        if (((void *)current_angle) != 0 &&
            (((R10_80171FE8_S_80171C34_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
            (s16)((s16)get_actor_height_difference((void *)current_angle, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    ((s16)((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)position_data->tile_x,(s16)position_data->tile_y,(s16)((s16)(((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }

        if (((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_1C & 0x20000) {
            TileObject *target_position = &reference_tile_object;
            ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)position_data->tile_x,(s16)position_data->tile_y,(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), (u8 *)move_data + 0x98));
            if (((s16)test_neighbor_position_relation(
                    position_data->tile_x, position_data->tile_y,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(primary_actor_record, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            ((s16)((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)position_data->tile_x,(s16)position_data->tile_y,(s16)((s16)(((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                        ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            select_actor_route_target(position_data, ((R10_80171FE8_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)actor_turn_angle_offsets);

    do {
        turn_flags = ((R10_80171FE8_S_80171C34_5 *)move_data)->unk_98;
        current_angle = ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_movement_clearance_and_height((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.s = trial_angle;
            ((R10_80171FE8_S_80171C34_8 *)((u8 *)actor_data + (((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_74 =
                position_data->tile_x;
            ((R10_80171FE8_S_80171C34_8 *)((u8 *)actor_data + (((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_7C =
                position_data->tile_y;
            ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u++;

            update_map_cell_flags_with_item_limit(
                position_data->tile_x, position_data->tile_y,
                (((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_2A.u >> 8) & 0xE;
                x_step += step_offset;
                position_data->tile_x += *x_step;
                position_data->tile_y += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)position_data->tile_x,(s16)position_data->tile_y,(u16)((((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            reference_tile_object . tile_position . word != *(u16 *)&position_data->tile_x) {
            if (((s16)check_entity_relation(actor_data,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20)) != 0) {
                do {
                    return;
                } while (0);
            }
        }

        turn_index++;
        if (turn_index >= 8) {
            break;
        }
    } while (1);

    if (turn_index >= 8) {
        ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        update_actor_status_and_mp(actor_data);
        return;
    }

    {
        ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        ((R10_80171FE8_S_80171C34_5 *)move_data)->unk_9C.u = position_data->room_index;
        ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_6D.u--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_6D.s == 0) {
        ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (position_data->tile_x << 6) | 0x20,
        (position_data->tile_y << 6) | 0x20,(s16)((s16)(((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_88.u - 0x20))));
    if (turn_index < 0x200) {
        ((R10_80171FE8_S_80171C34_1 *)actor_data)->unk_88.s = turn_index;
    }
}

/*
 * Sets action state 0x10, selects camera-relative snowman step frames, and clears the action tick,
 * counter, substate, and linked action field.
 */
void begin_snowman_step_animation(void *actor_state, void *action_state, SpriteFrameState *sprite, void *orientation) {
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9A.as_s8 = 0x10;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9B = 0;
    sprite->frameTable = ((u8 *)snowman_frame_set_2);
    select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80172730_S_80172688_1 *)orientation)->unk_2A + 0x100)
        >> 9) & 7) + ((u8 *)snowman_frame_set_2)), 0);
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_90 = 0;
    ((Rec_func_80171CD4_arg1 *)action_state)->unk_14 = 0;
    ((Rec_func_80171CD4_arg0 *)actor_state)->unk_9D = 0;
}

/* Checks target compatibility, height, and action availability; starts an adjacent attack when allowed. */
s32 try_snowman_attack(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */

    actor_flags = actor->movement_queue_state;
    actor_flags &= 0x7F;
    actor->movement_queue_state = actor_flags;
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }

    target_angle = probe_directional_neighbor(actor, sprite->tile_x, sprite->tile_y, actor->facing);
    if ((check_entity_interaction_compatibility(actor, target_angle) << 16) == 0) {
        return 0;
    }

    status_flags = g_dungeon_status.flags;
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-get_actor_height_difference(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        return -1;
    }

    apply_camera_offset_and_select_target((ObjectNodeHeader *)actor - 1, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->unk_9A.as_u8 = 0x11;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        sprite->frameTable = snowman_direction_frames;
        select_sprite_entry(sprite, (snowman_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}


/* Claims an action slot, starts the directional attack animation, and prepares its target and damage
 * state. */
void begin_snowman_attack(void *action_state, void *action_context, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            sprite->frameTable = ((u8 *)snowman_direction_frames);
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + ((u8 *)snowman_direction_frames)), 0);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

/* Relinks actor state, updates status or movement as needed, and reports whether a new action may start. */
s32 relink_snowman_path(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        choose_snowman_move(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R10_80172A94_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        choose_snowman_move(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((R10_80172A94_S_80172628_0 *)entity)->unk_71 = (u8) (((R10_80172A94_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((R10_80172A94_S_80172628_0 *)entity)->unk_71 = (u8) (((R10_80172A94_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((R10_80172A94_S_80172628_0 *)entity)->unk_46 = (u16) (((R10_80172A94_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}

/*
 * On completed movement, spends MP and advances status timers, then resumes Snowman behavior and
 * clears its timer only after a positive signed floor-trap check. /
 */
void move_snowman_to_tile(void *entity_arg, void *motion, void *check_arg, void *actor_arg) {
    void *entity = entity_arg;
    void *check_value = check_arg;
    void *actor = actor_arg;

    if (update_actor_movement_to_tile(entity, motion, check_value, actor) != 0) {
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(check_value, actor) << 16) > 0) {
            do {
                *(s32 **)((u8 *)entity + 0x8C) = ((void *)update_snowman_behavior);
            } while (0);
            *(s32 *)((u8 *)entity + 0x90) = 0;
        }
    }
}

/* Hops to the destination tile, updates landing animation, spends MP, and checks for a floor trap. */
void hop_snowman_to_tile(void *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 height_step;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 facing_aux;
    DungeonGlobalStatus *global_base;

    state = ((R10_80172C54_S_80172C54_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(sprite->flags & 0x6000)) {
            break;
        }
        sprite->frameTable = ((u8 *)D_801759A8);
        select_sprite_entry(
            sprite,
            ((u8 *)D_801759A8)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R10_80172C54_S_80172C54_0 *)action)->unk_98 |= 8;
        actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.s = 5;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_A4 = 0;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_9B++;

    case 1:
        move_ticks = ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.s;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_90 -= ((R10_80172C54_S_80172C54_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            target_x = sprite->tile_x;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            motion->velocity_x = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->velocity_y =
                (((sprite->tile_y << 6) - pos_y) << 16) /
                ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.s;

            ((R10_80172C54_S_80172C54_0 *)action)->unk_A4 =
                (-rsin(((R10_80172C54_S_80172C54_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height_offset = ((R10_80172C54_S_80172C54_0 *)action)->unk_90;
        height_step = ((R10_80172C54_S_80172C54_0 *)action)->unk_A4;
        next_move_ticks = ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.u;
        height_offset += height_step;
        next_move_ticks -= 1;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.u = next_move_ticks;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_90 = height_offset;
        if ((next_move_ticks << 16) < 0) {
            ((R10_80172C54_S_80172C54_0 *)action)->unk_90 = 0;
            ((R10_80172C54_S_80172C54_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            ((R10_80172C54_S_80172C54_0 *)action)->unk_9B++;
        }
    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            ((R10_80172C54_S_80172C54_0 *)action)->unk_98 &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            sprite->frameTable = ((u8 *)snowman_frame_set_3);
            select_sprite_entry(
                sprite,
                ((u8 *)snowman_frame_set_3)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((R10_80172C54_S_80172C54_0 *)action)->unk_9B++;
        }
        break;

    case 3:
        if (*(u8 * *)&sprite->frameTable == ((u8 *)snowman_direction_frames)) {
            break;
        }
        sprite->frameTable = ((u8 *)snowman_direction_frames);
        select_sprite_entry(
            sprite,
            ((u8 *)snowman_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }

    action_ticks = ((R10_80172C54_S_80172C54_0 *)action)->unk_96 - 1;
    ((R10_80172C54_S_80172C54_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->action_flags & ACTOR_ACTION_PENDING) {
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)sprite->tile_x,(s16)sprite->tile_y,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                &facing_aux));
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((R10_80172C54_S_80172C54_0 *)action)->unk_8C = ((void *)update_snowman_behavior);
        on_actor_status_updated(actor);
    }
}

/*
 * Runs update_linked_actor_motion and installs update_snowman_behavior only when it succeeds and
 * the signed floor-trap check returns positive.
 */
void update_snowman_linked_motion(Resource10CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_snowman_behavior;
        }
    }
}

/* Times an attack animation and sound, applies damage, spends MP, and restores actor movement. */
void advance_timed_attack_animation_and_damage(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 timer;
    s32 state;

    state = ((R10_80173080_S_80173080_0 *)action)->phase;
    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            ((R10_80173080_S_80173080_0 *)action)->phase = 3;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
            return;
        }
        ((R10_80173080_S_80173080_3 *)motion)->unk_14 = 0;
        ((R10_80173080_S_80173080_3 *)motion)->unk_10 = 0;
        ((R10_80173080_S_80173080_3 *)motion)->unk_0C = 0;
        ((R10_80173080_S_80173080_0 *)action)->timer.u = 0;
        ((R10_80173080_S_80173080_0 *)action)->phase++;
        return;
    case 1:
        timer = ((R10_80173080_S_80173080_0 *)action)->timer.u + 1;
        ((R10_80173080_S_80173080_0 *)action)->timer.u = timer;
        if (((s16)timer == 4) || (sprite->flags & 0x8000)) {
            u8 *direction_table = ((u8 *)snowman_attack_frames);

            sprite->frameTable = direction_table;
            select_sprite_entry(sprite,
                          direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                          0);
            ((R10_80173080_S_80173080_0 *)action)->timer.u = 0;
            ((R10_80173080_S_80173080_0 *)action)->phase++;
            return;
        }
        return;
    case 2:
        timer = ((R10_80173080_S_80173080_0 *)action)->timer.u + 1;
        ((R10_80173080_S_80173080_0 *)action)->timer.u = timer;
        if (((s16)timer == 7) || (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
            ((R10_80173080_S_80173080_0 *)action)->timer.u = 0;
            ((R10_80173080_S_80173080_0 *)action)->phase++;
        }
        if (((R10_80173080_S_80173080_0 *)action)->timer.s == 5) {
            play_sound_if_enabled(0x808);
            return;
        }
        return;
    case 3:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            ((R10_80173080_S_80173080_0 *)action)->unk_8C = ((u8 *)update_snowman_behavior);
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
        return;
    }
}

/* Starts a targeted spell effect, emits converging particles, and restores actor status after the
 * animation. */
void advance_actor_spell_effect_sequence(void *actor, ObjectPosition *motion, SpriteFrameState *tile_arg, ActorRecord *action)
{
    s16 particle_index;
    s32 offset_y;
    s32 offset_x;
    void *target_obj;
    u8 *kind_data;
    s32 state;
    s16 effect_flags;
    s16 action_dep;

    state = ((R10_80173280_S_80173280_0 *)actor)->phase;
    effect_flags = 0;
    switch (state) {
    case 0:
    if (action->flags1C & ACTOR_PLAYER_SIDE) {
        u32 kind = (action->action_flags & ACTOR_ACTION_CODE_MASK) - 1;

        switch (kind) {
        case 6:
            effect_flags = 1;
        case 2:
            goto kind_3;
        case 5:
            effect_flags = 1;
        case 1:
            goto kind_2;
        case 4:
            effect_flags = 1;
        case 0:
            goto kind_1;
        case 3:
        default:
            goto kind_default;
        }
    } else {
        switch (action->action_flags & ACTOR_ACTION_CODE_MASK) {
        case 2:
            goto kind_2;
        case 1:
            goto kind_1;
        case 3:
            goto kind_3;
        default:
            goto kind_default;
        }
    }

kind_3:
    kind_data = (u8 *)action + 0xE;
    goto use_kind;
kind_2:
    kind_data = (u8 *)action + 0xB;
    goto use_kind;
kind_1:
    kind_data = (u8 *)action + 8;
    goto use_kind;
kind_default:
    kind_data = 0;

use_kind:
    if (*kind_data != 0) {
        ((R10_80173280_S_80173280_0 *)actor)->unk_98 =
            ((R10_80173280_S_80173280_0 *)actor)->unk_98 & 0xFF7F;
        if (effect_flags) {
            target_obj = primary_actor_record;
            action->target = target_obj;
            state = (s32)*(u8 * *)&((ObjectNodeHeader *)((u8 *)target_obj - 0x20))->sprite;
            action->target_tile_x = ((u8 *)state)[0x24];
            action->target_tile_y = ((u8 *)state)[0x25];
        } else {
            u8 *kind_table;
            u8 kind;
            u8 *kind_entry;

            kind = *kind_data;
            kind_table = (u8 *)item_action_definitions;
            kind_entry = (u8 *)((u32)(kind * 20) + (u8 *)kind_table);

            if (kind_entry[0x12] == 2) {
                target_obj = action->target;
                if (target_obj != 0) {
                    state = (s32)*(u8 * *)&((ObjectNodeHeader *)((u8 *)target_obj - 0x20))->sprite;
                    action->target_tile_x = ((u8 *)state)[0x24];
                    action->target_tile_y = ((u8 *)state)[0x25];
                }
            } else {
                s8 x;
                s8 y;

                action->target = (void *)scan_actor_along_heading(action, tile_arg->tile_x, tile_arg->tile_y,
                              action->facing, 0x10);
                x = action->target_tile_x;
                y = action->target_tile_y;
                x = abs(x);
                y = abs(y);
                action->target_tile_x = x;
                action->target_tile_y = y;
            }
        }
        if (create_actor_spell_effect(action, kind_data,(s16)(effect_flags), (u8 *)actor + 0x98)) {
            ((R10_80173280_S_80173280_0 *)actor)->timer.s = 0x18;
            ((R10_80173280_S_80173280_0 *)actor)->unk_9E = 4;
            ((R10_80173280_S_80173280_0 *)actor)->phase++;
            return;
        }
        return;
    }

    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, tile_arg->tile_x, tile_arg->tile_y);
    {
        u8 *active_actor = primary_actor_record;
        g_dungeon_status.active_actor = 0;
        ((R10_80173280_S_80173280_6 *)active_actor)->unk_A6--;
    }
    advance_status_timers(action);
    (*(u8 *)&action->pending_turn_updates)--;
    ((R10_80173280_S_80173280_0 *)actor)->unk_8C = ((u8 *)update_snowman_behavior);
    action->target_tile_y = 0;
    action->target_tile_x = 0;
    action->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    return;

case 1:
    if (get_cd_command_queue_depth()) {
        tile_arg->flags |= 0x800;
        return;
    }
    tile_arg->flags &= 0xF7FF;
    ((R10_80173280_S_80173280_0 *)actor)->phase++;
    play_sound_if_enabled(0x703);

case 2:
    particle_index = 0;
    do {
        effect_flags = rand() & 0xFF;
        effect_flags |= 0x80;
        offset_x = (s16)((rand() & 0x7F) - 0x40);
        offset_y = (s16)((rand() & 0x7F) - 0x40);
        create_converging_fading_sprite((u8 *)actor - 0x20, 0, 0x00808080, effect_flags, offset_x, offset_y,
                   (s16)((rand() & 0x7F) - 0x40));
        particle_index++;
    } while (particle_index < 5);

    ((R10_80173280_S_80173280_0 *)actor)->unk_9E--;
    if ((s16)((R10_80173280_S_80173280_0 *)actor)->unk_9E == 1) {
        tile_arg->flags |= 0x800;
    }
    if (((R10_80173280_S_80173280_0 *)actor)->timer.u == 5) {
        tile_arg->flags &= 0xF7FF;
    }
    ((R10_80173280_S_80173280_0 *)actor)->timer.s--;
    if ((s16)((R10_80173280_S_80173280_0 *)actor)->timer.s > 0 &&
        !(tile_arg->flags & 0xE000)) {
        return;
    }
    ((R10_80173280_S_80173280_0 *)actor)->unk_98 |= 0x80;
    ((R10_80173280_S_80173280_0 *)actor)->phase++;
    tile_arg->flags |= 0x800;
    ((R10_80173280_S_80173280_0 *)actor)->timer.s = 0x14;
    return;

case 3:
    kind_data = ((u8 *)(&g_dungeon_status));
    if (((R10_80173280_S_80173280_7 *)kind_data)->unk_0C == 0) {
        ((R10_80173280_S_80173280_0 *)actor)->timer.s = 0;
    }
    ((R10_80173280_S_80173280_0 *)actor)->timer.s--;
    if ((s16)((R10_80173280_S_80173280_0 *)actor)->timer.s <= 0) {
        *(u16 *)((u8 *)actor + 0x96) = 0;
        tile_arg->flags &= 0xF7FF;
    }
    if (!(tile_arg->flags & 0xE000)) {
        return;
    }
    motion->velocity_z = 0;
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    set_record_integer_tile_center(motion, tile_arg->tile_x, tile_arg->tile_y);
    if (*(u8 **)&tile_arg->frameTable != ((u8 *)snowman_direction_frames)) {
        u8 *frame_table = ((u8 *)snowman_direction_frames);
        (tile_arg->frameTable) = frame_table;
        select_sprite_entry(tile_arg,
            frame_table[((g_game_work.view.camera_rotation.parts.viewAngle + action->facing + 0x100) >> 9) & 7],
            0);
        tile_arg->flags &= 0xF7FF;
    }
    if (((R10_80173280_S_80173280_7 *)kind_data)->unk_0C != 0) {
        return;
    }
    ((R10_80173280_S_80173280_7 *)kind_data)->unk_0A--;
    ((R10_80173280_S_80173280_0 *)actor)->unk_8C = ((u8 *)update_snowman_behavior);
    advance_status_timers(action);
    action->target_tile_y = 0;
    action->target_tile_x = 0;
    (*(u8 *)&action->pending_turn_updates)--;
    action->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
    play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;
    default:
        return;
    }
}
const Resource10DirectionOffset D_80170854[8] = {
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
    { -1, 1 },
    { -1, 0 },
    { -1, 65535 },
    { 0, 65535 },
    { 1, 65535 }
};
const Resource10DirectionOffset D_80170874[8] = {
    { 16, 0 },
    { 13, 13 },
    { 0, 16 },
    { -13, 13 },
    { -16, 0 },
    { -13, 65523 },
    { 0, 65520 },
    { 13, 65523 }
};

/* Applies a value change and directional displacement, then returns the actor to its tile and restores
 * movement. */
void displace_actor_then_recenter(void *action, ObjectPosition *motion, SpriteFrameState *entity, EntityRec *actor)
{
    s32 state;

    state = ((R10_8017380C_S_8017380C_0 *)action)->phase;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        ((R10_8017380C_S_8017380C_0 *)action)->timer.s = 4;
        ((R10_8017380C_S_8017380C_0 *)action)->phase++;
        if (actor->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, entity, ((u8 *)D_801759C8));
            return;
        }
        if (!(entity->flags & 0x8000)) {
            return;
        }
        ((R10_8017380C_S_8017380C_0 *)action)->timer.s = 0;
        ((R10_8017380C_S_8017380C_0 *)action)->phase = 3;
        return;

    case 1:
    {
        s16 frames_left;

        frames_left = ((R10_8017380C_S_8017380C_0 *)action)->timer.u - 1;
        ((R10_8017380C_S_8017380C_0 *)action)->timer.s = frames_left;
        if (frames_left > 0) {
            motion->velocity_x =
                *(s16 *)((u8 *)((s8 *)dir_step_x) +
                    ((actor->unk_6A >> 8) & 0xE)) << 19;
            motion->velocity_y =
                *(s16 *)((u8 *)((s8 *)dir_step_y) +
                    ((actor->unk_6A >> 8) & 0xE)) << 19;
            return;
        }
        if (frames_left != 0) {
            return;
        }
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                ((actor->unk_6A >> 8) & 0xE)) << 18;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                ((actor->unk_6A >> 8) & 0xE)) << 18;
        ((R10_8017380C_S_8017380C_0 *)action)->timer.s = 6;
        ((R10_8017380C_S_8017380C_0 *)action)->phase++;
        return;
    }

    case 2:
        if (actor->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, entity, ((u8 *)D_801759C8));
            return;
        }
        {
            s16 return_frames;
            s32 origin_y;
            u16 previous_frames;

            return_frames = ((R10_8017380C_S_8017380C_0 *)action)->timer.s;
            if (return_frames != 0) {
                motion->velocity_x =
                    (((entity->tile_x << 6) - ({ motion->x.w.i - 0x20; })) << 16) / return_frames;
                origin_y = motion->y.w.i - 0x20;
                motion->velocity_y =
                    (((entity->tile_y << 6) - origin_y) << 16) /
                    ((R10_8017380C_S_8017380C_0 *)action)->timer.s;
            }
            previous_frames = ((R10_8017380C_S_8017380C_0 *)action)->timer.u;
            ((R10_8017380C_S_8017380C_0 *)action)->timer.s = previous_frames - 1;
            if ((s32)(previous_frames << 16) > 0) {
                return;
            }
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            ((R10_8017380C_S_8017380C_0 *)action)->phase++;
            return;
        }

    case 3:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, entity->tile_x, entity->tile_y);
        if (entity->frameTable == ((u8 *)D_80175998)) {
            u8 *direction_table;

            direction_table = ((u8 *)snowman_direction_frames);
            entity->frameTable = direction_table;
            select_sprite_entry(entity,
                direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
        }
        {
            s32 entity_ref;

            entity_ref = ((s32)g_dungeon_status.pending_display_owner);
            if (entity_ref == (s32)((u8 *)actor - 0x20)) {
                g_dungeon_status.pending_display_owner = entity_ref & 0x7FFFFFFF;
            }
        }
        ((R10_8017380C_S_8017380C_0 *)action)->unk_8C = ((void *)update_snowman_behavior);
        return;
    }
}

/* Runs the shared actor defeat and removal sequence with the supplied callback arguments. */
void remove_defeated_snowman(void *state, void *motion, void *position, void *actor)
{
    update_actor_defeat_removal(state, motion, position, actor);
}

/* Runs the shared hop and shrink sequence for the actor with the supplied callback arguments. */
void shrink_hopping_snowman(void *state, void *motion, void *position, void *actor)
{
    update_actor_hop_and_shrink(state, motion, position, actor);
}

void advance_snowman_removal(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}

/* Runs update_actor_hop_and_grow and installs update_snowman_behavior when it returns nonzero. */
void grow_hopping_snowman(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = update_snowman_behavior;
    }
}

/* Waits for a status effect to clear, updates actor status and activity counts, then restores movement. */
void advance_snowman_status_action(void *action, void *context, SpriteFrameState *sprite_in, void *actor_in)
{
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;

    state = ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(sprite_in->flags & 0xE000)) {
            return;
        }
        (sprite_in->frameTable) = ((u8 *)snowman_alt_direction_frames);
        select_sprite_entry(sprite_in,
            ((u8 *)snowman_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base;

            counter_base = &g_dungeon_status;
            counter_base->activity_counts.parts.pending_action_count =
                ((u16)counter_base->activity_counts.parts.pending_action_count) - 1;
        }
        ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 1:
        if ((get_entity_effect_value(actor_in, STATUS_SLEEP) << 16) != 0) {
            status = &g_dungeon_status;
            if (status->flags & 0x1000) {
                return;
            }
            if (((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(action, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_25 == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(action, context, sprite_in, actor_in);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                return;
            }
            actor_flags = ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(action, context, sprite_in, actor_in);
                update_snowman_parent_motion(action, context, sprite_in, actor_in);
                return;
            }
            if (((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                if ((check_entity_relation(actor_in,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(actor_in);
            on_actor_status_updated(actor_in);
            if ((get_entity_effect_value(actor_in, STATUS_SLEEP) << 16) != 0) {
                s8 coordinate = *(s8 *)&sprite_in->room_index;
                TileObject *origin = &reference_tile_object;
                s32 probe_result;

                if ((coordinate != origin->room_index) || (coordinate < 0)) {
                    probe_result = ((s16)get_tile_chebyshev_distance(origin, sprite_in));
                    actor_to_check = actor_in;
                    if (probe_result < 2) {
                        if (!(generate_random_value(actor_in) & 7)) {
                            clear_slots_of_type(actor_in, STATUS_SLEEP);
                        }
                        actor_to_check = actor_in;
                    }
                } else {
                    if (!(generate_random_value(origin) & 7)) {
                        clear_slots_of_type(actor_in, STATUS_SLEEP);
                    }
                    actor_to_check = actor_in;
                }
            } else {
                actor_to_check = actor_in;
            }
            if ((get_entity_effect_value(actor_to_check, STATUS_SLEEP) << 16) != 0) {
                return;
            }

            (sprite_in->frameTable) = ((u8 *)snowman_frame_set_1);
            select_sprite_entry(sprite_in,
                ((u8 *)snowman_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            if (sprite_in->flags & 0x8000) {
                ((R10_80173BBC_S_80173D4C_0 *)action)->unk_8C = ((void *)update_snowman_behavior);
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count++;

            ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B++;
            return;
        }
        (sprite_in->frameTable) = ((u8 *)snowman_frame_set_1);
        select_sprite_entry(sprite_in,
            ((u8 *)snowman_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80173BBC_S_80173D4C_2 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        if (sprite_in->flags & 0x8000) {
            ((R10_80173BBC_S_80173D4C_0 *)action)->unk_8C = ((void *)update_snowman_behavior);
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count++;

        ((R10_80173BBC_S_80173D4C_0 *)action)->unk_9B++;
        return;

    case 2:
        if (!(sprite_in->flags & 0xE000)) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;

        ((R10_80173BBC_S_80173D4C_0 *)action)->unk_8C = ((void *)update_snowman_behavior);

        return;
    }
}

/* Waits for MP recovery while processing actor status, then restores the normal animation and movement. */
void advance_snowman_mp_action(void *actor_in, s32 actor_index, SpriteFrameState *target, void *entity_in)
{
    EntityRec *entity = entity_in;
    s32 state;
    s32 entity_flags;
    s32 direction;
    DungeonGlobalStatus *shared_state;
    state = ((R10_80173F4C_S_801740DC_0 *)actor_in)->unk_9B;
    switch (state) {
    case 0:
    if (!(target->flags & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count--;
    }
    (target->frameTable) = ((u8 *)snowman_alt_direction_frames);
    direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
    select_sprite_entry(target,(u8)(((u8 *)snowman_alt_direction_frames)[direction & 7]), 0);
    ((R10_80173F4C_S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 1:
    if (entity->tileY != 0) {
        DungeonGlobalStatus *shared_counter;

        (target->frameTable) = ((u8 *)snowman_frame_set_1);
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target,(u8)(((u8 *)snowman_frame_set_1)[direction & 7]), 0);
        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count++;
        ((R10_80173F4C_S_801740DC_0 *)actor_in)->unk_9B++;
        return;
    } else {
        shared_state = &g_dungeon_status;
        if (shared_state->flags & 0x1000) {
            return;
        }
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_in, actor_index, target, 0) != 0) {
                return;
            }
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }
        entity_flags = entity->flags1C;
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor_in, actor_index, target, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, actor_index, target, entity);
            update_snowman_parent_motion(actor_in, actor_index, target, entity);
            return;
        }
        if (entity->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
            update_actor_status_and_mp(entity);
        } else {
            update_actor_status_and_mp(entity);
        }
        on_actor_status_updated(entity);
        if (entity->tileY == 0) {
            return;
        }
        (target->frameTable) = ((u8 *)snowman_frame_set_1);
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target,(u8)(((u8 *)snowman_frame_set_1)[direction & 7]), 0);
        shared_state->activity_counts.parts.pending_action_count++;
    }
    ((R10_80173F4C_S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 2:
    if (!(target->flags & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count--;
    }
    ((R10_80173F4C_S_801740DC_0 *)actor_in)->unk_8C = ((void *)update_snowman_behavior);

    return;
    default:
        return;
    }
}

/*
 * Resumes the main actor handler after parent motion completes and the signed floor-trap check is
 * positive; during motion, restores movement frames when the alternate table is active and flags
 * 0x208 are clear.
 */
void update_snowman_parent_motion(R10_80174258_Actor *actor, s32 action, SpriteFrameState *entity, R10_80174258_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)update_snowman_behavior);
            return;
        }
    } else if (*(u8 **)&entity->frameTable == ((u8 *)snowman_alt_direction_frames) &&
               !(map_object->unk_1C & 0x208)) {
        entity->frameTable = ((u8 *)snowman_move_direction_frames);
        select_sprite_entry(entity,(s16)(((u8 *)snowman_move_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}

/*
 * Runs update_thrown_actor_travel and installs update_snowman_behavior only when it succeeds and
 * the signed floor-trap check returns positive.
 */
void advance_boss_command_stream(Resource10CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = update_snowman_behavior;
        }
    }
}

/*
 * Runs interpolate_actor_to_terrain_tile and installs update_snowman_behavior when it returns
 * nonzero.
 */
void settle_snowman_on_tile(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = update_snowman_behavior;
    }
}

/* Runs update_spinning_actor_fall and installs update_snowman_behavior when it returns nonzero. */
void create_positioned_sprite_effect(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = update_snowman_behavior;
    }
}

/* Runs update_actor_fade_in and installs update_snowman_behavior when it returns nonzero. */
void fade_in_snowman(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = update_snowman_behavior;
    }
}

/* Finds actors at the target tile and height, resolves attack damage, and bursts particles for kinds
 * 0x33-0x36. */
void resolve_linked_attack_hits_and_particle_bursts(void *node, s32 target_x, s32 target_y, s32 target_height)
{
    R10_8017442C_OffsetTable offsets = (*(R10_8017442C_OffsetTable *)&D_80170854);
    void *head = node;
    register void *owner = head;
    s32 match_x = target_x;
    s32 match_y;
    register void *owner_data = ((R10_8017442C_S_801745BC_0_pre *)head)[-1].unk_04;
    void *next_link = ((R10_8017442C_S_801745BC_0 *)head)->unk_5C;
    void *position = ((R10_8017442C_S_801745BC_0_pre *)head)[-1].unk_00;
    u16 height_arg = target_height;
    s32 center_height;
    s32 low_height;

    node = (u8 *)next_link + 0x20;
    match_y = target_y;

    if (node != head) {
        center_height = (s32)(height_arg << 16) >> 16;
        low_height = center_height - 0x40;
        do {
            R10_8017442C_S_801745BC_2 *node_data = ((R10_8017442C_S_801745BC_1_pre *)node)[-1].unk_04;
            R10_8017442C_S_801745BC_3 *node_position = ((R10_8017442C_S_801745BC_1_pre *)node)[-1].unk_00;
            s32 height;

            if ((node_data->unk_24 == (match_x & 0xFFFF)) &&
                (node_data->unk_25 == (match_y & 0xFFFF))) {
                height = node_position->unk_0A;
                if (((center_height + 0x40) >= height) && (low_height < height)) {
                    if ((u32)(((R10_8017442C_S_801745BC_1 *)node)->unk_13 - 0x33) < 4U) {
                        u16 angle;
                        R10_8017442C_OffsetPair *offset;

                        ((R10_8017442C_S_801745BC_1 *)node)->unk_28 = 0;
                        ((R10_8017442C_S_801745BC_1 *)node)->unk_64 = -1;
                        initialize_timed_motion_step((u16)(6), 0xC);
                        target_y = 0x601;
                        if (((R10_8017442C_S_801745BC_1 *)node)->unk_13 == 0x34) {
                            target_y = 0x80B;
                        }
                        play_sound_if_enabled(target_y);

                        angle = ((R10_8017442C_S_801745BC_4 *)owner)->unk_2A;
                        offset = (R10_8017442C_OffsetPair *)((u8 *)&offsets +
                            (((s16)angle >> 7) & 0x1C));
                        spawn_radial_particle_burst((s16)((s16)(((R10_8017442C_S_801745BC_5 *)position)->unk_02 + (offset->x * 32))),(s16)((s16)(((R10_8017442C_S_801745BC_5 *)position)->unk_06 +
                                  ((s32)(offset->y << 16) >> 11))),(s16)((s16)(((R10_8017442C_S_801745BC_5 *)position)->unk_0A - 0x20)),(s16)(((R10_8017442C_S_801745BC_4 *)owner)->unk_14),
                            (s32)(s16)angle);
                    } else {
                        resolve_attack_damage_and_effects(owner, owner_data,(s16)((s16)((R10_8017442C_S_801745BC_4 *)owner)->unk_2A),(s16)(1));
                    }
                }
            }
            node = (u8 *)((R10_8017442C_S_801745BC_1 *)node)->unk_5C + 0x20;
        } while (node != head);
    }

}

/* Prepares the owner's attack for actors at the target tile and height, excluding kinds 0x33-0x36. */
void prepare_directional_attacks_for_neighbor_entities(void *node, s32 tile_x, s32 tile_y, s16 target_height)
{
    s32 match_x = tile_x;
    s32 match_y = tile_y;
    void *head = node;
    R10_80174670_S_80174800_4 *actor = head;
    void *owner;

    owner = ((R10_80174670_S_80174800_0_pre *)head)[-1].unk_00;
    node = (u8 *)((R10_80174670_S_80174800_0 *)head)->unk_5C + 0x20;
    while (node != head) {
        R10_80174670_S_80174800_2 *tile = ((R10_80174670_S_80174800_1_pre *)node)[-1].unk_04;
        R10_80174670_S_80174800_3 *height_data = ((R10_80174670_S_80174800_1_pre *)node)[-1].unk_00;
        s16 height;

        if ((tile->unk_24 == (match_x & 0xFFFF)) &&
            (tile->unk_25 == (match_y & 0xFFFF)) &&
            (height = height_data->unk_0A, height <= target_height + 0x38) &&
            (height > target_height - 0x38) &&
            ((u32)(((Rec_func_80174800_arg0 *)node)->unk_13 - 0x33) >= 4U)) {
            actor->unk_84 = 0x7C;
            actor->unk_85 =
                (s8)((s32)(actor->unk_26 * 3) >> 1);
            prepare_directional_attack(actor, owner,
                          actor->unk_2A, 1, 0);
        }
        node = (u8 *)((Rec_func_80174800_arg0 *)node)->unk_5C + 0x20;
    }
}

/* Claims an action slot, starts the directional action animation, and advances status and turn counters. */
void select_actor_target_and_advance_status(void *action_state, s32 effect_arg, SpriteFrameState *anim_state, ActorRecord *actor) {
    actor->movement_queue_state = actor->movement_queue_state & 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, effect_arg, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            anim_state->frameTable = ((s32 *)D_801759D8);
            select_sprite_entry(anim_state,
                          *((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                            + (u8 *)((s32 *)D_801759D8)),
                          0);
            advance_status_timers(actor);
            actor->pending_turn_updates = ((u8)actor->pending_turn_updates) - 1;
        }
    }
}

/* Prepares attacks near the tile ahead, resolves hits with particle bursts, then spends MP and ends the
 * action. */
void advance_directional_attack_sequence(void *action, void *position, SpriteFrameState *sprite, ActorRecord *entity)
{
    R10_80174898_OffsetTable direction_offsets = (*(R10_80174898_OffsetTable *)&D_80170854);
    s32 offset_coord;

    switch (((R10_80174898_S_80174898_0 *)action)->unk_9B) {
    case 0:
        ((R10_80174898_S_80174898_1 *)position)->unk_14 = 0;
        ((R10_80174898_S_80174898_1 *)position)->unk_10 = 0;
        ((R10_80174898_S_80174898_1 *)position)->unk_0C = 0;
        ((R10_80174898_S_80174898_0 *)action)->unk_96 = 0x14;
        ((R10_80174898_S_80174898_0 *)action)->unk_9B++;
        break;

    case 1:
        if ((--((R10_80174898_S_80174898_0 *)action)->unk_96 == 0x11) ||
            (sprite->flags & 0x8000)) {
            R10_80174898_OffsetPair *direction_offset;
            u16 flags;
            s32 height;
            s32 target_x;
            s32 tile_x;
            s32 y_offset;
            s32 x_offset;

            flags = sprite->flags;
            sprite->flags = flags | 0x0800;
            height = ((R10_80174898_S_80174898_1 *)position)->unk_0A;
            tile_x = sprite->tile_x;
            direction_offset = &direction_offsets.entries[(((u16)entity->facing) >> 9) & 7];
            x_offset = direction_offset->x;
            target_x = tile_x + x_offset;
            y_offset = direction_offset->y;
            offset_coord = sprite->tile_y + y_offset;
            target_x = target_x & 0xFFFF;
            prepare_directional_attacks_for_neighbor_entities(entity, target_x, offset_coord & 0xFFFF, height);
        }
        if ((((R10_80174898_S_80174898_0 *)action)->unk_96 == 0x0A) ||
            (sprite->flags & 0x8000)) {
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x606);
        }
        if ((((R10_80174898_S_80174898_0 *)action)->unk_96 == 9) ||
            (sprite->flags & 0x8000)) {
            R10_80174898_OffsetPair *direction_offset;
            u16 angle;
            s32 height;
            s32 tile_x;
            s32 x;
            s32 target_x;
            s32 y_offset;

            angle = ((u16)entity->facing);
            direction_offset = direction_offsets.entries + ((angle >> 9) & 7);
            height = ((R10_80174898_S_80174898_1 *)position)->unk_0A;
            tile_x = sprite->tile_x;
            offset_coord = direction_offset->x;
            target_x = tile_x + offset_coord;
            y_offset = direction_offset->y;
            offset_coord = sprite->tile_y + y_offset;
            x = target_x & 0xFFFF;
            resolve_linked_attack_hits_and_particle_bursts(entity, x, offset_coord & 0xFFFF, height);
        }
        if ((((R10_80174898_S_80174898_0 *)action)->unk_96 <= 0) ||
            (sprite->flags & 0x8000)) {
            ((R10_80174898_S_80174898_0 *)action)->unk_96 = 0;
            ((R10_80174898_S_80174898_0 *)action)->unk_9B++;
        }
        break;

    case 2:
        if (sprite->flags & 0xE000) {
            ((R10_80174898_S_80174898_1 *)position)->unk_14 = 0;
            ((R10_80174898_S_80174898_1 *)position)->unk_10 = 0;
            ((R10_80174898_S_80174898_1 *)position)->unk_0C = 0;
            set_record_integer_tile_center(position,
                sprite->tile_x, sprite->tile_y);
            if (*(u8 **)&sprite->frameTable != ((u8 *)snowman_direction_frames)) {
                sprite->frameTable = ((u8 *)snowman_direction_frames);
                sprite->flags &= 0xF7FF;
                select_sprite_entry(sprite,
                    (*(u8 **)&sprite->frameTable)[((g_game_work.view.camera_rotation.parts.viewAngle +
                        entity->facing + 0x100) >> 9) & 7],
                    0);
                ((R10_80174898_S_80174898_0 *)action)->unk_9B++;
            }
        }
        break;

    case 3:
        spend_actor_mp(entity, 0x400);
        ((R10_80174898_S_80174898_0 *)action)->unk_8C = ((void *)update_snowman_behavior);
        g_dungeon_status.active_actor = 0;
        (entity->action_flags) &= 0x7FFF;
        break;
    }
}


/* Projects visible sprites in the linked effect chain using the shared depth adjustment. */
s32 project_snowman_sprite_chain(void *initial_payload, s32 entry_data, R10_80174BE4_Entry *entry, s32 unused)
{
    void *payload = initial_payload;
    R10_80174BE4_Scratchpad *scratch = (R10_80174BE4_Scratchpad *)0x1F800000;
    R10_80174BE4_Entry *next_entry;

    for (;;) {
        scratch->value = ((s16 *)D_80175A18)[0];

        if (!(entry->unk14 & 0x80)) {
            project_sprite_commands(payload, entry_data, entry,(s16)(entry->unk06));
        }

        next_entry = *(R10_80174BE4_Entry **)((u8 *)payload - 8);
        if (next_entry == 0) {
            return 0;
        }
        payload = (u8 *)next_entry + 0x20;
        entry_data = (s32)next_entry->unk08;
        entry = next_entry->unk0C;
    }
}

/*
 * Moves the effect along an oscillating directional path, changes its brightness, and expires it
 * at frame 26.
 *
 * MECHANISM: Typed page and scratch fields preserve the signed lh/sw widths and offsets.
 */
void update_effect_motion_and_brightness(void *effect, void *motion, void *render)
{
    R10_80174C70_LocalVector direction;
    R10_80174C70_LocalTable directions;
    long render_or_step = (long)render;
    s32 phase_angle;
    s32 phase_offset;
    u8 brightness;
    u32 frame;

    directions = (*(R10_80174C70_LocalTable *)&D_80170874);

    frame = (u32)((R10_80174C70_S_80174C70_0 *)effect)->unk_1A.s;
    switch (frame) {
    case 0:
    case 1:
    case 2:
    case 3:
        brightness = ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0E + 0x18;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0E = brightness;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0D = brightness;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0C = brightness;

    case 4:
        ((R10_80174C70_S_80174C70_0 *)effect)->unk_62 = 0x20;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.s = 0xA00;
        break;

    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 16:
    case 15:
        ((R10_80174C70_S_80174C70_0 *)effect)->unk_62 = 0x18;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u += 0x180;
        break;

    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
        brightness = ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0E - 0xE;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0E = brightness;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0D = brightness;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0C = brightness;
        ((R10_80174C70_S_80174C70_0 *)effect)->unk_62 = 0x18;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u += 0x30;
        break;

    case 26:
        (*(u16 *)((u8 *)effect + (-2))) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    ((R10_80174C70_S_80174C70_0 *)effect)->unk_1A.u++;

    if (((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u >= 0x1000) {
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u -= 0x1000;
    }

    phase_angle = ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u;
    phase_offset = phase_angle - 0x400;
    phase_angle = phase_offset;
    if ((s16)phase_offset < 0) {
        phase_angle = phase_offset + 0x1000;
    }
    {
        s16 normalized_phase = phase_angle;
        s32 sine = rcos(normalized_phase);
        s32 sine_radius = ((R10_80174C70_S_80174C70_0 *)effect)->unk_62;
        s32 sine_product = sine_radius * sine;
        s32 cosine_angle = normalized_phase;

        render_or_step = sine_product << 4;
        phase_offset = rsin(cosine_angle);
    }

    {
        u8 *direction_ptr = (u8 *)&directions;
        s32 heading_x = ((R10_80174C70_S_80174C70_0 *)effect)->unk_18;
        s32 radius = ((R10_80174C70_S_80174C70_0 *)effect)->unk_62;

        direction.x = (*(u16 *)((u8 *)direction_ptr + (((heading_x - 0x400) >> 7) & 0x1C)));

        {
            s32 cosine_product = radius * phase_offset;
            s32 heading_y = ((R10_80174C70_S_80174C70_0 *)effect)->unk_18;

            direction_ptr += ((heading_y - 0x400) >> 7) & 0x1C;
            direction.y = (*(u16 *)((u8 *)direction_ptr + (2)));

            {
                s32 height_step = cosine_product << 4;

                ((R10_80174C70_S_80174C70_2 *)motion)->unk_08 += height_step;
            }
        }
    }
    {
        s32 axis_step = direction.x;
        s32 axis_product = axis_step * render_or_step;

        axis_step = axis_product >> 4;
        ((R10_80174C70_S_80174C70_2 *)motion)->unk_0C = axis_step;
    }
    {
        s32 axis_step = direction.y;
        s32 axis_product = axis_step * render_or_step;

        ((R10_80174C70_S_80174C70_2 *)motion)->unk_10 = axis_product >> 4;
    }
    ((R10_80174C70_S_80174C70_2 *)motion)->unk_00 += ((R10_80174C70_S_80174C70_2 *)motion)->unk_0C;
    ((R10_80174C70_S_80174C70_2 *)motion)->unk_04 += ((R10_80174C70_S_80174C70_2 *)motion)->unk_10;

    return;
}

/* Spawns a small gray oscillating sprite near the source, oriented relative to the camera. */
void spawn_randomized_oscillating_effect(s32 unused, R10_80174F24_S_func_80AF3724_0 *origin, void *unused_record, void *unused_actor)
{
    R10_80174F24_LocalVector direction;
    R10_80174F24_LocalTable directions;
    s16 angle;
    s32 jitter;
    s32 coordinate;
    s32 x_offset;
    R10_80174F24_S_func_80AF3724_2 *direction_entry;
    ObjectNodeHeader *object;
    R10_80174F24_S_func_80AF3724_4 *state;
    ObjectPosition *transform;
    SpriteFrameState *display;

    directions = (*(R10_80174F24_LocalTable *)&D_80170874);
    object = allocate_flagged_object_node(0x212);
    state = (R10_80174F24_S_func_80AF3724_4 *)((u8 *)object + 0x20);
    if (object != 0) {
        state->unk_1A = 0;
        angle = 0;
        do {
            if (((g_game_work.view.camera_rotation.parts.viewAngle + angle + 0x100) >> 9 & 7) == 2) {
                state->unk_18 = angle;
            }
            angle += 0x200;
        } while (angle < 0x1000);

        object->update_callback = ((u8 *)update_effect_motion_and_brightness);
        register_node(object, project_sprite_chain);

        display = object->sprite;
        display->tpage_abr = 0x20;
        display->flags |= 0xC;

        transform = object->position;
        jitter = rand() & 0x1F;
        coordinate = origin->unk_02 - 0x10;
        coordinate += jitter;
        transform->x.w.i = coordinate;
        jitter = rand() & 0x1F;
        coordinate = origin->unk_06 - 0x10;
        coordinate += jitter;
        transform->y.w.i = coordinate;
        jitter = (rand() & 0x1F) - 0x70;
        coordinate = origin->unk_0A;
        coordinate += jitter;
        transform->z.w.i = coordinate;

        direction_entry = (R10_80174F24_S_func_80AF3724_2 *)&directions;
        direction.x = ((R10_80174F24_S_func_80AF3724_2 *)((u8 *)direction_entry +
            (((state->unk_18 - 0x400) >> 7) & 0x1C)))->unk_00;
        direction_entry = (R10_80174F24_S_func_80AF3724_2 *)((u8 *)direction_entry +
            (((state->unk_18 - 0x400) >> 7) & 0x1C));
        direction.y = direction_entry->unk_02;
        x_offset = direction.x << 19;
        transform->velocity_x = x_offset;
        transform->velocity_y = direction.y << 19;
        transform->x.v += x_offset;
        transform->y.v += transform->velocity_y;

        display = object->sprite;
        display->scale_y = 0x200;
        display->scale_x = 0x200;
        display->color.c.b = 0x20;
        display->color.c.g = 0x20;
        display->color.c.r = 0x20;
        display->clut = 0x7DCF;
        display->flags |= 0x100;
        state->unk_28 = (*(R10_80174F24_LocalPacket *)D_80175A0C);
        display->source = &state->unk_28;
    }
}

/* Stops movement and waits for dungeon activity to finish, then clears the callback and counts the new
 * action. */
void wait_for_snowman_action_slot(void *entity_data, s32 unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other_entity = other_data;
    s32 kind = 0x18;

    other_entity[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = ((void *)wait_for_snowman_action_slot);
    entity[0x9A] = kind;
    entity[0x9B] = 0;
    other_entity[0x6D] = 0;
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(other_entity) << 16) == 0)) {
        *(void **)(entity + 0x8C) = 0;
        entity[0x9A] = kind;
        entity[0x9B] = 0;
        (*(s16 *)actor_action_reset_value) = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
}

/* Advances the transition sprite, then restores the view tint to neutral and removes the effect. */
void restore_snowman_scene_tint(u8 *task, void *context, SpriteFrameState *input)
{
    s16 frames_left;
    GameWork *fade_state = &g_game_work;

    if (task[0x9A] == 0) {
        (*(s32 *)D_80175A84) = *(s32 *)&input->source;
        advance_sprite_animation_and_textures(input);
        if (input->flags & 0xE000) {
            unlink_node(task - 0x20);
            *(s16 *)(task + 0x96) = 0x10;
            task[0x9A]++;
            return;
        }
    } else {
        fade_state->view.tint.parts.tint_r = (u8)(fade_state->view.tint.parts.tint_r +
            ((s32)(0x80 - fade_state->view.tint.parts.tint_r) / *(s16 *)(task + 0x96)));
        fade_state->view.tint.parts.tint_g = (u8)(fade_state->view.tint.parts.tint_g +
            ((s32)(0x80 - fade_state->view.tint.parts.tint_g) / *(s16 *)(task + 0x96)));
        fade_state->view.tint.parts.tint_b = (u8)(fade_state->view.tint.parts.tint_b +
            ((s32)(0x80 - fade_state->view.tint.parts.tint_b) / *(s16 *)(task + 0x96)));

        frames_left = *(u16 *)(task + 0x96) - 1;
        *(s16 *)(task + 0x96) = frames_left;
        if (frames_left <= 0) {
            *(u16 *)(task - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }
}

/* Loads transition effects, fades the view tint, replaces the actor, and restores the new actor's facing. */
void advance_actor_transition_and_restore_facing(void *transition, void *position, SpriteFrameState *record, void *actor) {
    u8 *object_data = ((u8 *)(&g_game_work));
    u8 state;
    u32 next_state;

    state = ((R10_80175398_S_80175398_0 *)transition)->phase;
    switch (state) {

    case 0:
        next_state = ((R10_80175398_S_80175398_0 *)transition)->phase + 1;
        ((R10_80175398_S_80175398_0 *)transition)->phase = next_state;
        return;

    case 1:
        run_cd_image_commands(((u8 *)snowman_image_commands), ((u8 *)snowman_image_load_done), 0);
        ((R10_80175398_S_80175398_0 *)transition)->unk_AC = 0;
        ((R10_80175398_S_80175398_0 *)transition)->phase++;
        ((R10_80175398_S_80175398_1 *)actor)->unk_8A = ((R10_80175398_S_80175398_1 *)actor)->unk_2A.u;

    case 2:
    {
        s32 direction;
        u16 angle;

        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80175398_S_80175398_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
        angle = ((R10_80175398_S_80175398_1 *)actor)->unk_2A.u;
        if (((u8 *)snowman_image_load_done)[0] == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((R10_80175398_S_80175398_1 *)actor)->unk_2A.u = angle + 0x200;
            return;
        }
        run_cd_image_commands(((u8 *)snowman_image_commands), ((u8 *)snowman_image_load_done), 1);
        sound_set_cd_cue_parameters(0, ((s32 *)cd_cue_base)[0], 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, read_stream_cue_start_offset(), 0);
        (*(u8 *)snowman_effect_load_done) = 0;
        Control_CD(0xFF, ((s32 *)resource_completion_callback_address), ((u8 *)snowman_effect_load_done));
        select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, position, 8, 0x300);
        ((R10_80175398_S_80175398_0 *)transition)->timer.u = 0x10;
        ((R10_80175398_S_80175398_0 *)transition)->phase++;
    }

    case 3:
    {
        u16 old_timer = ((R10_80175398_S_80175398_0 *)transition)->timer.u;
        u16 timer = old_timer - 1;
        u8 *target_color;

        ((R10_80175398_S_80175398_0 *)transition)->timer.u = timer;
        if ((s32)(timer << 16) <= 0) {
            u8 cd_finished = (*(u8 *)snowman_effect_load_done);
            ((R10_80175398_S_80175398_0 *)transition)->timer.u = old_timer;
            if (cd_finished == 0) {
                return;
            }
            ((R10_80175398_S_80175398_0 *)transition)->phase++;
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            return;
        }

        target_color = ((u8 **)actor_effect_color_targets)[lookup_masked_byte_table(actor)];
        ((R10_80175398_S_80175398_2 *)object_data)->unk_A8 +=
            (((R10_80175398_S_80175398_3 *)target_color)->unk_00 - ((R10_80175398_S_80175398_2 *)object_data)->unk_A8) /
            ((R10_80175398_S_80175398_0 *)transition)->timer.s;
        ((R10_80175398_S_80175398_2 *)object_data)->unk_A9 +=
            (((R10_80175398_S_80175398_3 *)target_color)->unk_01 - ((R10_80175398_S_80175398_2 *)object_data)->unk_A9) /
            ((R10_80175398_S_80175398_0 *)transition)->timer.s;
        ((R10_80175398_S_80175398_2 *)object_data)->unk_AA +=
            (((R10_80175398_S_80175398_3 *)target_color)->unk_02 - ((R10_80175398_S_80175398_2 *)object_data)->unk_AA) /
            ((R10_80175398_S_80175398_0 *)transition)->timer.s;
        return;
    }

    case 4:
        object_data = allocate_flagged_object_node(0x12);
        if (object_data == NULL) {
            return;
        }
        {
            R10_80175398_DungeonEffect *effect = (R10_80175398_DungeonEffect *)object_data;

            effect->resource = ((u8 *)restore_snowman_scene_tint);
            register_node(effect, ((u8 *)project_snowman_sprite_chain));
            ((R10_80175398_S_80175398_0 *)transition)->unk_A8.p = effect;
            effect->child->x = ((R10_80175398_DungeonCopy3 *)position)->x;
            effect->child->y = ((R10_80175398_DungeonCopy3 *)position)->y;
            (*(s16 *)D_80175A18) = -2;
            effect->child->z = ((R10_80175398_DungeonCopy3 *)position)->z;
            object_data = (u8 *)effect->tail;
            ((R10_80175398_DungeonTail *)object_data)->value1e = 0x1000;
            ((R10_80175398_DungeonTail *)object_data)->value1c = 0x1000;
            ((R10_80175398_DungeonTail *)object_data)->color = 0x00808080;
        }
        {
            s16 resource_index = lookup_masked_byte_table(actor) - 1;

            if (resource_index < 0) {
                s32 random_value = rand();

                resource_index = random_value % 3;
            }
            select_record_entry_and_value(object_data, ((u8 *)dungeon_resource_buffer) + ((s32 *)D_80175A00)[resource_index], 0);
        }
        record->flags |= 0x80;
        ((R10_80175398_S_80175398_0 *)transition)->timer.u = 0;
        next_state = ((R10_80175398_S_80175398_0 *)transition)->phase + 1;
        ((R10_80175398_S_80175398_0 *)transition)->phase = next_state;
        return;

    case 5:
    {
        u16 old_timer = ((R10_80175398_S_80175398_0 *)transition)->timer.u;
        ((R10_80175398_S_80175398_0 *)transition)->timer.u = old_timer + 1;
        if ((s16)old_timer < 30) {
            s16 update_count = 0;
            do {
                spawn_randomized_oscillating_effect(transition, position, record, actor);
                update_count++;
            } while (update_count < 8);
        }
    }
        object_data = ((R10_80175398_S_80175398_0 *)transition)->unk_A8.p2;
        object_data = ((R10_80175398_S_80175398_2 *)object_data)->unk_0C;
        if (((R10_80175398_S_80175398_2 *)object_data)->unk_14 & 0xE000) {
            ((R10_80175398_S_80175398_0 *)transition)->phase++;
        }

    case 6:
        if (((R10_80175398_S_80175398_0 *)transition)->phase != 6) {
            return;
        }
        if (create_status_linked_render_effect(position, (*(void **)D_80175A84), (*(s16 *)D_80175A18), ((u8 *)staged_spawn_count)) == 0) {
            return;
        }
        ((R10_80175398_S_80175398_0 *)transition)->timer.u = 0x10;
        ((R10_80175398_S_80175398_0 *)transition)->phase++;
        decrement_monster_entry_count(((R10_80175398_S_80175398_1 *)actor)->unk_13, 3);
        update_map_cell_flags_with_item_limit(record->tile_x, record->tile_y, 0x300);
        unlink_entity_node(actor);
        object_data = (u8 *)actor - 0x20;
        ((R10_80175398_S_80175398_2 *)object_data)->unk_10 |= 0x80000000;
        return;

    case 7:
    {
        u8 *linked_actor = advance_staged_entity_load(record, actor);
        ((R10_80175398_S_80175398_1 *)actor)->unk_60 = linked_actor;
        if (linked_actor == NULL) {
            return;
        }
        ((R10_80175398_S_80175398_0 *)transition)->timer.u = 0x10;
        ((R10_80175398_S_80175398_0 *)transition)->phase++;
        ((R10_80175398_S_80175398_7 *)(((R10_80175398_S_80175398_1 *)actor)->unk_60))->unk_2A = ((R10_80175398_S_80175398_1 *)actor)->unk_2A.u;
        {
            u8 *linked_state = ((R10_80175398_S_80175398_1 *)actor)->unk_60;
            s32 direction;
            u8 *direction_frames;

            object_data = ((R10_80175398_S_80175398_5_pre *)linked_state)[-1].unk_00;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((R10_80175398_S_80175398_5 *)linked_state)->unk_2A + 0x100) >> 9) & 7;
            direction_frames = ((R10_80175398_S_80175398_2 *)object_data)->unk_2C;
            select_indirect_table_entry(object_data, direction_frames[direction], ((R10_80175398_S_80175398_2 *)object_data)->unk_04);
        }
        ((R10_80175398_S_80175398_2 *)object_data)->unk_14 &= 0xFFFE;
    }

    case 8:
    {
        u16 timer = ((R10_80175398_S_80175398_0 *)transition)->timer.u - 1;
        ((R10_80175398_S_80175398_0 *)transition)->timer.u = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        {

            ((R10_80175398_S_80175398_7 *)(((R10_80175398_S_80175398_1 *)actor)->unk_60))->unk_2A = ((R10_80175398_S_80175398_1 *)actor)->unk_8A;
            ((R10_80175398_S_80175398_0_pre *)transition)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
    }
        ((R10_80175398_S_80175398_1 *)actor)->unk_6D = 0;

        return;
    default:
        return;
    }
}

/* Runs resolve_actor_floor_trap_once and installs update_snowman_behavior when it returns positive. */
void resolve_snowman_floor_trap(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = update_snowman_behavior;
    }
}

/* Runs propagate_actor_action_flag and installs update_snowman_behavior when it returns nonzero. */
void propagate_snowman_action_flag(Resource10CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor)) {
        state->callback = update_snowman_behavior;
    }
}
