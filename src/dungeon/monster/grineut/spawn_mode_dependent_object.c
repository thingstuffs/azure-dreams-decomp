#include "shared/audio_commands.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
/* Grineut actor spawning, movement, attacks, and sprite effects. */
#include "dungeon/monster/grineut.h"
#include "shared/actor_action_flags.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "engine/cd.h"

void * (*const resource07_slot0_entry0)(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a) = spawn_mode_dependent_112_object;
void (*const resource07_slot0_entry1)(void *entity, R07_80170A28_S_80170A28_2 *motion, void *part) = update_entity_facing_motion_and_ground;

/* Creates a Grineut actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_mode_dependent_112_object(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a)
{
    s32 kind;
    void *obj;
    R07_80170854_S_8016A854_2 *part_a;
    SpriteFrameState *part_b;
    R07_80170854_S_8016A854_1 *work;
    R07_80170854_S_8016A854_4 *actor;
    s32 primary_bits;
    s32 secondary_flags;
    s8 saved_byte_24;
    s16 saved_value_0a;
    s8 saved_byte_25;

    work = 0;
    saved_byte_24 = byte_24;
    saved_value_0a = value_0a;
    saved_byte_25 = byte_25;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((R07_80170854_S_8016A854_0 *)obj)->unk_10 = ((u8 *)update_entity_facing_motion_and_ground);
        work->unk_13 = MONSTER_GRINEUT;
        register_node(obj, project_sprite_chain);

        part_a = ((R07_80170854_S_8016A854_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value_0a;
        part_b = ((R07_80170854_S_8016A854_0 *)obj)->unk_0C;
        kind = kind_flags & 3;
        part_b->tile_y = saved_byte_25;
        actor = work;
        part_b->frameTable = ((u8 *)grineut_frame_set_1);
        part_b->tile_x = saved_byte_24;

        if (kind == 1) {
            primary_bits = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            secondary_flags = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->unk_14 = primary_bits;
            work->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            primary_bits = work->unk_14 | ACTOR_CLASS_ENABLED;
            secondary_flags = work->unk_1C | ACTOR_PLAYER_SIDE;
            work->unk_14 = primary_bits;
            work->unk_1C = secondary_flags;
        } else if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                if (generate_random_value() & 1) {
                    work->unk_1C |= ACTOR_ASLEEP;
                    set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = ((u8 *)grineut_alt_direction_frames);
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = ((void *)dispatch_monster_move_attack_spell);
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}

/* Runs actor callbacks and updates facing, animation, movement, and ground contact. */
void update_entity_facing_motion_and_ground(void *entity, R07_80170A28_S_80170A28_2 *motion, void *part)
{
    void *entity_base = entity;
    s16 old_state;
    s32 state_or_direction;
    s16 direction_index;
    s16 direction_copy;
    void *call_entity;
    void *call_motion;
    void *call_part;
    void *call_self;
    u32 unused_tail;
    R07_80170A28_EntityCallback callback;
    s32 rounded_angle;
    s16 ground_height;
    s16 base_height;
    s32 entity_flags;
    u16 part_flags;
    u16 new_part_flags;
    u8 direction_flag;

    if (g_dungeon_status.flags & 0x2000) {
        callback = (*(R07_80170A28_EntityCallback *)((u8 *)entity + 0x8C));
        if (callback == (R07_80170A28_EntityCallback)((void *)dispatch_monster_move_attack_spell)) {
            {
                call_self = entity;
                callback(call_self, motion, part, call_self);
            }
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        return;
    }

    call_entity = entity;
    call_motion = motion;
    call_part = part;
    old_state = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    call_self = entity;
    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_part, call_self) != 0) {
        return;
    }

    {
        R07_80170A28_EntityCallback update_callback;
        update_callback = (*(R07_80170A28_EntityCallback *)((u8 *)entity + 0x8C));
        if (update_callback != 0) {
            update_callback(entity, motion, part, entity);
        }
    }
    ((R07_80170A28_EntityCallback *)D_80174198)[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, part, entity);

    if ((s16)old_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, part, entity);
    }

    part_flags = ((R07_80170A28_S_80170A28_0 *)part)->unk_14;
    if (!(part_flags & 0x8000)) {
        rounded_angle = g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        state_or_direction = (rounded_angle >> 9) & 7;
        direction_index = state_or_direction;
        direction_copy = state_or_direction;
        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_copy) {
            if (((R07_80170A28_S_80170A28_0 *)part)->unk_2C != 0) {
                select_indirect_table_entry(part,
                              ((R07_80170A28_S_80170A28_0 *)part)->unk_2C[direction_copy],
                              ((R07_80170A28_S_80170A28_0 *)part)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = state_or_direction;
        }

        direction_flag = dir_sprite_flag[direction_index];
        if (direction_flag != 0) {
            ((R07_80170A28_S_80170A28_0 *)part)->unk_14 |= 1;
        } else {
            ((R07_80170A28_S_80170A28_0 *)part)->unk_14 &= 0xFFFE;
        }
        if (!(((R07_80170A28_S_80170A28_1 *)entity_base)->unk_1C & 0x20)) {
            if (!(((R07_80170A28_S_80170A28_0 *)part)->unk_14 & 0x40)) {
                advance_sprite_animation_and_textures(part);
            }
        } else {
            ((R07_80170A28_S_80170A28_0 *)part)->unk_14 |= 0x7000;
        }
        apply_monster_koyaw_data(((R07_80170A28_S_80170A28_1 *)entity_base)->unk_1C, (u8 *)part + 0xC);
    } else {
        if (part_flags & 0x800) {
            new_part_flags = part_flags & 0x8FFF;
        } else {
            new_part_flags = part_flags | 0x7000;
        }
        ((R07_80170A28_S_80170A28_0 *)part)->unk_14 = new_part_flags;
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((*(u16 *)((u8 *)entity + 0x98)) & 8) {
        (*(s8 *)((u8 *)entity + 0x9D)) = 0;
    } else {
        motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(s8 *)((u8 *)entity + 0x9D)) = (u8)(*(s8 *)((u8 *)entity + 0x9D)) + 1;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4)) {
        ground_height = ((s16)sample_terrain_surface_height(motion->unk_00.at02.v,
                               motion->unk_04.at02.v,
                               (s16)(((R07_80170A28_S_80170A28_1 *)entity_base)->unk_88 - 0x20)));
        if (ground_height < 0x200) {
            base_height = (s16)((R07_80170A28_S_80170A28_1 *)entity_base)->unk_88;
            if ((*(s16 *)((u8 *)entity + 0x92)) + base_height < ground_height) {
                ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
            } else if (ground_height >= base_height) {
                (*(s32 *)((u8 *)entity + 0x90)) = 0;
                motion->unk_14 = 0;
                ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
            } else {
                motion->unk_14 = 0;
                ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_1C |= 0x08000000;
                (*(s8 *)((u8 *)entity + 0x9D)) = 0;
                (*(s16 *)((u8 *)entity + 0x92)) = ground_height - ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_88;
            }

            entity_flags = ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_1C;
            if (entity_flags & 0x40000000) {
                ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_1C = entity_flags & 0xBFFFFFFF;
                ground_height = ((s16)sample_terrain_surface_height(
                    (((R07_80170A28_S_80170A28_0 *)part)->unk_24 << 6) | 0x20,
                    (((R07_80170A28_S_80170A28_0 *)part)->unk_25 << 6) | 0x20,
                    (s16)(((R07_80170A28_S_80170A28_1 *)entity_base)->unk_88 - 0x20)));
                (*(s16 *)((u8 *)entity + 0x92)) +=
                    ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_88 - ground_height;
                ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_88 = ground_height;
            }
        } else {
            ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((R07_80170A28_S_80170A28_1 *)entity_base)->unk_1C &= 0xF7FFFFFF;
    }

    entity_base = (u8 *)entity_base + 0x88;
    motion->unk_0A =
        *(u16 *)entity_base + (*(u16 *)((u8 *)entity + 0x92));
    ((R07_80170A28_S_80170A28_0 *)part)->unk_14 |= 0x40;

    return;
}

/* Selects movement, attacks, and spells from actor status and creates sprite effects during idle
 * animation. */
void dispatch_monster_move_attack_spell(void *record, EntityRec *entity, void *object, ActorRecord *other_entity)
{
    s32 scratch;
    s16 offset[3];
    s8 result;
    u16 state;
    u8 *table;
    u8 *high_table; /* MATCH: both table-selection paths feed the shared tail in a1. */

    if (g_dungeon_status.flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 = 0xE;
        advance_stored_path_motion(record, entity, object, other_entity);
        return;
    }

    if (other_entity->mp == 0) {
        advance_actor_pending_action(record, entity, object, other_entity);
        if (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p == ((u8 *)grineut_alt_direction_frames)) {
            return;
        }
        {
            void *next_state;

            next_state = ((u8 *)grineut_frame_set_2);
            high_table = next_state;
        }
        (*(void * *)((u8 *)object + 0x2C)) = high_table;
        select_sprite_entry(object,
            *((u8 *)(((g_game_work.view.camera_rotation.parts.viewAngle + other_entity->facing + 0x100) >> 9) & 7) + (u32)high_table),
            0);
        return;
    }

    if (((u32)other_entity->flags1C) & ACTOR_ASLEEP) {
        if (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p == ((u8 *)grineut_alt_direction_frames)) {
            ((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)record)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)record)->unk_8C = 0;
            other_entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(record, entity, object, ((u8 *)grineut_frame_set_2)) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)other_entity->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(record, entity, object, other_entity);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 != 0xE) {
            table = ((u8 *)grineut_frame_set_1);
            if (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p != table) {
                (*(void * *)((u8 *)object + 0x2C)) = table;
                select_sprite_entry(object,
                    table[((g_game_work.view.camera_rotation.parts.viewAngle + other_entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)record)->unk_9A.as_u8 = 0xE;
        }

        ((Rec_func_800A9E70_arg0 *)record)->unk_98 &= 0xFFF3;
        if (other_entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(record, entity, object, ((u8 *)grineut_frame_set_4)) != 0) {
                return;
            }
        }

        if (((u32)other_entity->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(record, entity, object, other_entity);
            update_grineut_parent_motion(record, entity, object, other_entity);
            (*(void * *)((u8 *)object + 0x2C)) = ((u8 *)grineut_frame_set_3);
            select_sprite_entry(object,
                *((u8 *)(((g_game_work.view.camera_rotation.parts.viewAngle + other_entity->facing + 0x100) >> 9) & 7) + (u32)((u8 *)grineut_frame_set_3)),
                0);
            return;
        }

        if ((can_entity_gain_level(other_entity) << 16) != 0) {
            process_selected_actor_record(record, entity, object, other_entity);
        }
    }

    result = ((s8)find_active_rect_containing_point(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00.v, ((R07_80170E54_S_80170E54_2 *)object)->unk_24.at01.v));
    ((R07_80170E54_S_80170E54_2 *)object)->unk_26 = result;

    if (other_entity->pending_turn_updates > 0) {
        if (((u32)other_entity->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(other_entity);
            return;
        }
        if (((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00u.v == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            choose_grineut_move(record, entity, object, other_entity);
            return;
        }
        if (!(other_entity->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(other_entity,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((relink_grineut_path(record, entity, object, 0) << 16) == 0) {
                return;
            }
            state = other_entity->action_flags | 0x4000;
            other_entity->action_flags = state;
            if (!(state & 0x8000)) {
                choose_grineut_move(record, entity, object, other_entity);
                return;
            }
        }

        state = other_entity->action_flags & ACTOR_ACTION_CODE_MASK;
        switch (state) {
        case 8:
        case 9:
            if ((try_grineut_attack(record, entity, object, other_entity) << 16) != 0) {
                return;
            }
            begin_grineut_attack(record, entity, object, other_entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            ActorRecord *player;
            s16 coordinate;

            coordinate = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00.v),(s16)(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at01.v),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                &scratch));
            player = primary_actor_record;
            other_entity->facing = coordinate;
            if (player->action_id == 0x11) {
                begin_actor_spell_action(record, entity, object, ((u8 *)grineut_frame_set_3), ((void *)dispatch_monster_move_attack_spell));
                return;
            }
        }

        case 12:
            update_actor_status_and_mp(other_entity);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(record, entity, object, ((u8 *)grineut_frame_set_3), ((void *)dispatch_monster_move_attack_spell));
            return;

        case 11:
        default:
            choose_grineut_move(record, entity, object, other_entity);
            return;
        }
    }

    if (!(((u32)other_entity->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 index = result;

        if ((index < 0) || !(dungeon_rooms[index].flags & 2)) {
            if (!(((u32)other_entity->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        ((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00.v, ((R07_80170E54_S_80170E54_2 *)object)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    other_entity->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at00.v),(s16)(((R07_80170E54_S_80170E54_2 *)object)->unk_24.at01.v),(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                        &scratch));
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((R07_80170E54_S_80170E54_2 *)object)->unk_14 & 0x40) {
        return;
    }

    table = ((u8 *)grineut_frame_set_1);
    if ((((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p != table) &&
        (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p != ((u8 *)grineut_frame_set_3))) {
        (*(void * *)((u8 *)object + 0x2C)) = table;
        select_sprite_entry(object,
            table[((g_game_work.view.camera_rotation.parts.viewAngle + other_entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800A9E70_arg0 *)record)->unk_AA = 1;
    } else if (((R07_80170E54_S_80170E54_2 *)object)->unk_14 & 0x6000) {
        s16 timer = ((Rec_func_800A9E70_arg0 *)record)->unk_AA - 1;

        ((Rec_func_800A9E70_arg0 *)record)->unk_AA = timer;
        if (timer < 0) {
            ((Rec_func_800A9E70_arg0 *)record)->unk_AA = (rand() & 0x1F) + 0x20;
        }
        if (((Rec_func_800A9E70_arg0 *)record)->unk_AA < 2) {
            ((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p = ((u8 *)grineut_frame_set_1);
        } else {
            ((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p = ((u8 *)grineut_frame_set_3);
        }
        select_sprite_entry(object,
            ((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p2[
                ((g_game_work.view.camera_rotation.parts.viewAngle + other_entity->facing + 0x100) >> 9) & 7],
            0);
    }

    if (!resolve_record_orientation_or_fallback(((R07_80170E54_S_80170E54_2 *)object)->unk_08, object, offset, 1)) {
        return;
    }
    if (((R07_80170E54_S_80170E54_2 *)object)->unk_2C.p != ((u8 *)grineut_frame_set_1)) {
        return;
    }

    {
        void *created;
        void *sub;
        void *color;
        u8 *base;
        s32 base_word;

        created = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
        ((Rec_func_800A9E70_arg0 *)record)->unk_A0.at00_pv.v = created;
        object = created;
        if (object == 0) {
            return;
        }
        register_node(object, project_sprite_chain);
        color = (void *)0x00808080;
        ((R07_80170E54_S_80170E54_2 *)object)->unk_10 = ((u8 *)D_800D79B0);
        ((R07_80170E54_S_80170E54_9 *)(((R07_80170E54_S_80170E54_2 *)object)->unk_08))->unk_02 =
            ((u16)entity->x.w.i) + offset[0];
        ((R07_80170E54_S_80170E54_9 *)(((R07_80170E54_S_80170E54_2 *)object)->unk_08))->unk_06 =
            ((u16)entity->y.w.i) + offset[1];
        ((R07_80170E54_S_80170E54_9 *)(((R07_80170E54_S_80170E54_2 *)object)->unk_08))->unk_0A =
            ((u16)entity->z.w.i) + offset[2];
        sub = ((R07_80170E54_S_80170E54_2 *)object)->unk_0C;
        base = ((u8 *)secondary_sprite);
        ((R07_80170E54_S_80170E54_2 *)object)->unk_BB = 0;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_1E = 0xC00;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_1C = 0xC00;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_0C = color;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_00 = base;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_14 |= 0xC;
        base_word = ((R07_80170E54_S_80170E54_8 *)base)->unk_04;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_04 = 0;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_05 = 0;
        ((R07_80170E54_S_80170E54_7 *)sub)->unk_08 = base_word;
    }
}


/* Advances one stored path step, updates occupied tiles and facing, and selects the movement animation and
 * delay. */
void advance_stored_path_motion(void *action, s32 action_id, SpriteFrameState *entity, void *move_state) {
    void *state = move_state;
    s32 tile_mask;
    s16 move_result;
    s16 direction;
    s16 x;
    s32 y;
    s32 step_count;
    u8 new_x;
    u8 new_y;

    if (((R07_80171570_S_80171570_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (((R07_80171570_S_80171570_0 *)state)->unk_71.u <= ((R07_80171570_S_80171570_0 *)state)->unk_8A) {
        return;
    }

    if (*(u8 * *)&entity->frameTable != ((u8 *)grineut_move_direction_frames)) {
        entity->frameTable = ((u8 *)grineut_move_direction_frames);
        select_sprite_entry(
            entity,(s16)(((u8 *)grineut_move_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R07_80171570_S_80171570_0 *)state)->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }

    x = entity->tile_x;
    y = entity->tile_y;
    tile_mask = 0x3000;
    if (((R07_80171570_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, tile_mask);

    direction = ((s16)get_rounded_facing_and_rounding_flag((s16)(x),(s16)(y),(s16)(((R07_80171570_S_80171570_3 *)((u8 *)state + ((R07_80171570_S_80171570_0 *)state)->unk_8A))->unk_74),(s16)(((R07_80171570_S_80171570_3 *)((u8 *)state + ((R07_80171570_S_80171570_0 *)state)->unk_8A))->unk_7C),
        (u8 *)action + 0x98));
    move_result = ((s16)check_movement_clearance_and_height((s16)(direction), entity, state, 0x20));

    entity->tile_x =
        ((R07_80171570_S_80171570_3 *)((u8 *)state + ((R07_80171570_S_80171570_0 *)state)->unk_8A))->unk_74;
    tile_mask = 0x3000;
    entity->tile_y =
        ((R07_80171570_S_80171570_3 *)((u8 *)state + ((R07_80171570_S_80171570_0 *)state)->unk_8A))->unk_7C;
    ((R07_80171570_S_80171570_0 *)state)->unk_8A = (u16)((R07_80171570_S_80171570_0 *)state)->unk_8A + 1;

    new_x = entity->tile_x;
    new_y = entity->tile_y;
    if (((R07_80171570_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags((s16)(new_x),(s16)(new_y),(u16)(tile_mask));
    ((R07_80171570_S_80171570_0 *)state)->unk_2A = direction;

    if (move_result == 3 && !(g_dungeon_status.flags & 0x80)
        && !(entity->flags & 0x8000)) {
        initialize_opposite_facing_effect(action, action_id, entity, state);
        ((R07_80171570_S_80171570_2 *)action)->unk_8C = 0;
    } else {
        ((R07_80171570_S_80171570_2 *)action)->unk_9A = 0x0F;
        ((R07_80171570_S_80171570_2 *)action)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((R07_80171570_S_80171570_2 *)action)->unk_96 = 0;
        return;
    }

    ((R07_80171570_S_80171570_2 *)action)->unk_96 = 8;
    step_count = ((R07_80171570_S_80171570_0 *)state)->unk_71.u;
    if (step_count > 0) {
        ((R07_80171570_S_80171570_2 *)action)->unk_96 = 8 / step_count;
    }
}

/* Chooses a clear step or attack, records the actor's path, and updates occupied tiles and movement
 * counts. */
void choose_grineut_move(void *move_data, void *context, void *position_data, void *actor_data)
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

    if ((dungeon_flags & 0x4000) || ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.s >= 0) {
        if (((R07_801717B4_S_80171C34_1 *)actor_data)->unk_12 >= 2 ||
            (s16)try_grineut_attack(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_46 = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, (u8 *)move_data + 0x9C);
    actor_flags = ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_data,(u8)((SpriteFrameState *)position_data)->tile_x,(u8)((SpriteFrameState *)position_data)->tile_y);
            if (((void *)current_angle) != 0) {
                s16 target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->tile_x,(s16)((SpriteFrameState *)position_data)->tile_y,(s16)(((R07_801717B4_S_80171C34_7 *)(((R07_801717B4_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_24),(s16)(((R07_801717B4_S_80171C34_7 *)(((R07_801717B4_S_80171C34_3_pre *)((void *)current_angle))[-1].unk_00))->unk_25),
                    (u8 *)move_data + 0x98));
                ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
            if (!(((R07_801717B4_S_80171C34_1 *)actor_data)->unk_14 & 0x80000000)) {
                ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_14 |= 0x80000000;
                ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.u +=
                    (generate_random_value() & 7) << 9;
            }
        } else {
            if (probe_directional_neighbor(actor_data,(u8)((SpriteFrameState *)position_data)->tile_x,(u8)((SpriteFrameState *)position_data)->tile_y,(s16)(((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.s)) != 0) {
                ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(((R07_801717B4_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((R07_801717B4_S_80171C34_1 *)actor_data)->unk_45 + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (((SpriteFrameState *)position_data)->tile_x == (u16)target_x &&
                    ((SpriteFrameState *)position_data)->tile_y == (u16)target_y) {
                    ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }

                turn_data = (u8 *)move_data + 0x98;
                target_angle = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->tile_x,(s16)((SpriteFrameState *)position_data)->tile_y,(s16)((s16)target_x),(s16)((s16)target_y), turn_data));
                ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.s = target_angle;
                if (((s16)check_movement_clearance_and_height((s16)(target_angle), position_data, actor_data, 0x20)) <= 0) {
                    ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->tile_x,(s16)((SpriteFrameState *)position_data)->tile_y,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y), turn_data));
                }
                if (((s16)test_neighbor_position_relation(
                        ((SpriteFrameState *)position_data)->tile_x, ((SpriteFrameState *)position_data)->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y)) != 0) {
                    limit_detour = 1;
                }
            } else {
                select_actor_route_target(position_data, ((R07_801717B4_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                              (u8 *)move_data + 0x98);
            }
        }
    } else if (*(s8 *)&((SpriteFrameState *)position_data)->room_index >= 0 &&
               ((R07_801717B4_DungeonRecord *)dungeon_rooms)[*(s8 *)&((SpriteFrameState *)position_data)->room_index].flags & 2) {
        select_actor_route_target(position_data, ((R07_801717B4_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                      (u8 *)move_data + 0x98);
    } else if (!(((R07_801717B4_S_80171C34_1 *)actor_data)->unk_46 & 0x8000)) {
        current_angle = (s32)probe_directional_neighbor(actor_data,(u8)((SpriteFrameState *)position_data)->tile_x,(u8)((SpriteFrameState *)position_data)->tile_y,(s16)(((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.s));
        if (((void *)current_angle) != 0 &&
            (((R07_801717B4_S_80171C34_3 *)((void *)current_angle))->unk_1C & 0x2000) &&
            (s16)((s16)get_actor_height_difference((void *)current_angle, actor_data)) < 0x81) {
            if (((s16)check_diagonal_side_height(
                    ((s16)((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)((SpriteFrameState *)position_data)->tile_x,(s16)((SpriteFrameState *)position_data)->tile_y,(s16)((s16)(((R07_801717B4_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                return;
            }
        }

        if (((R07_801717B4_S_80171C34_1 *)actor_data)->unk_1C & 0x20000) {
            TileObject *target_position = &reference_tile_object;
            ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.s = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)position_data)->tile_x,(s16)((SpriteFrameState *)position_data)->tile_y,(s16)(target_position->tile_position.parts.tile_x),(s16)(target_position->tile_position.parts.tile_y), (u8 *)move_data + 0x98));
            if (((s16)test_neighbor_position_relation(
                    ((SpriteFrameState *)position_data)->tile_x, ((SpriteFrameState *)position_data)->tile_y,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y)) != 0) {
                if (((s16)get_actor_height_difference(primary_actor_record, actor_data)) < 0x81) {
                    if (((s16)check_diagonal_side_height(
                            ((s16)((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.u >> 9) & 0xFFFF,(s16)((SpriteFrameState *)position_data)->tile_x,(s16)((SpriteFrameState *)position_data)->tile_y,(s16)((s16)(((R07_801717B4_S_80171C34_1 *)actor_data)->unk_88.u - 0x20)))) != 0) {
                        ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            select_actor_route_target(position_data, ((R07_801717B4_S_80171C34_5 *)move_data)->unk_9C.s, actor_data,
                          (u8 *)move_data + 0x98);
        }
    }

    turn_index = 0;
    turn_table = ((s16 *)actor_turn_angle_offsets);

    do {
        turn_flags = ((R07_801717B4_S_80171C34_5 *)move_data)->unk_98;
        current_angle = ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.s;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (((s16)check_movement_clearance_and_height((s16)(trial_angle), position_data, actor_data, 0x20)) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
                    return;
                }
            }

            ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.s = trial_angle;
            ((R07_801717B4_S_80171C34_8 *)((u8 *)actor_data + (((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_74 =
                ((SpriteFrameState *)position_data)->tile_x;
            ((R07_801717B4_S_80171C34_8 *)((u8 *)actor_data + (((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u & 0x7F)))->unk_7C =
                ((SpriteFrameState *)position_data)->tile_y;
            ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u++;

            update_map_cell_flags_with_item_limit(
                ((SpriteFrameState *)position_data)->tile_x, ((SpriteFrameState *)position_data)->tile_y,
                (((R07_801717B4_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (((R07_801717B4_S_80171C34_1 *)actor_data)->unk_2A.u >> 8) & 0xE;
                x_step += step_offset;
                ((SpriteFrameState *)position_data)->tile_x += *x_step;
                ((SpriteFrameState *)position_data)->tile_y += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags((s16)((SpriteFrameState *)position_data)->tile_x,(s16)((SpriteFrameState *)position_data)->tile_y,(u16)((((R07_801717B4_S_80171C34_1 *)actor_data)->unk_1C & 0x2000) ? 0x300 : 0x3000));
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&reference_tile_object.tile_position.parts.tile_x) != *(u16 *)&((SpriteFrameState *)position_data)->tile_x) {
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
        ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        update_actor_status_and_mp(actor_data);
        return;
    }

    {
        ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_46 &= 0x7FFF;
        ((R07_801717B4_S_80171C34_5 *)move_data)->unk_9C.u = ((SpriteFrameState *)position_data)->room_index;
        ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_6D.u--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (((R07_801717B4_S_80171C34_1 *)actor_data)->unk_6D.s == 0) {
        ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_71.u &= 0x7F;
        return;
    }

    turn_index = ((s16)sample_terrain_surface_height(
        (((SpriteFrameState *)position_data)->tile_x << 6) | 0x20,
        (((SpriteFrameState *)position_data)->tile_y << 6) | 0x20,(s16)((s16)(((R07_801717B4_S_80171C34_1 *)actor_data)->unk_88.u - 0x20))));
    if (turn_index < 0x200) {
        ((R07_801717B4_S_80171C34_1 *)actor_data)->unk_88.s = turn_index;
    }
}

/* Starts the directional movement animation and shifts the position opposite the actor's facing. */
void initialize_opposite_facing_effect(void *effect, s32 *position, SpriteFrameState *sprite, void *source)
{
    s32 direction;
    s16 *direction_x;

    direction = (*(u16 *)((s8 *)source + 0x2A) >> 9) & 7;
    *((s8 *)effect + 0x9A) = 0x10;
    *((s8 *)effect + 0x9B) = 0;
    sprite->frameTable = ((u8 *)grineut_frame_set_5);
    select_sprite_entry(sprite,(s16)(((u8 *)grineut_frame_set_5)[((g_game_work.view.camera_rotation.parts.viewAngle +
                               *(s16 *)((s8 *)source + 0x2A) + 0x100) >> 9) & 7]),(s16)(0));
    direction_x = dir_step_x;
    direction *= 2;
    position[0] -= *(s16 *)((u8 *)direction_x + direction) << 19;
    position[1] -= *(s16 *)((u8 *)dir_step_y + direction) << 19;
}

/* Checks target compatibility, height, and action availability; starts an adjacent attack when allowed. */
s32 try_grineut_attack(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, SpriteFrameState *sprite, ActorRecord *actor)
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
        sprite->frameTable = grineut_frame_set_1;
        select_sprite_entry(sprite, (grineut_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}


/* Claims an action slot, starts the directional attack animation, and prepares its target and damage
 * state. */
void begin_grineut_attack(void *action_state, void *action_context, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
            sprite->frameTable = ((u8 *)grineut_frame_set_1);
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + ((u8 *)grineut_frame_set_1)), 0);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}

/* Relinks actor state, updates status or movement as needed, and reports whether a new action may start. */
s32 relink_grineut_path(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        choose_grineut_move(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((R07_8017229C_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        choose_grineut_move(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((R07_8017229C_S_80172628_0 *)entity)->unk_71 = (u8) (((R07_8017229C_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((R07_8017229C_S_80172628_0 *)entity)->unk_71 = (u8) (((R07_8017229C_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((R07_8017229C_S_80172628_0 *)entity)->unk_46 = (u16) (((R07_8017229C_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}

/*
 * On completed tile movement, spends MP and advances status timers, resuming behavior and clearing
 * its counter only after a positive signed floor-trap result. Clears the secondary action halfword
 * under dungeon status flag 0x80. /
 */
void move_grineut_to_tile(R07_801723E0_S_801724A8_0 *state, s32 context, s32 source, s32 target) {
    if (update_actor_movement_to_tile(state, context, source, target) != 0) {
        spend_actor_mp(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = ((void *)dispatch_monster_move_attack_spell);
        state->unk_90.at00.v = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}

/* Hops to the destination tile, updates landing animation, spends MP, and checks for a floor trap. */
void advance_target_hop(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 arc_offset;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 direction_aux;
    DungeonGlobalStatus *global_base;

    state = ((R07_80172478_S_80172478_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)grineut_frame_set_6);
        select_sprite_entry(
            sprite,
            ((u8 *)grineut_frame_set_6)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R07_80172478_S_80172478_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((R07_80172478_S_80172478_0 *)action)->unk_98 |= 8;
        ((R07_80172478_S_80172478_2 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((R07_80172478_S_80172478_0 *)action)->unk_A8.s = 5;
        ((R07_80172478_S_80172478_0 *)action)->unk_A4 = 0;
        ((R07_80172478_S_80172478_0 *)action)->unk_9B++;

    case 1:
        move_ticks = ((R07_80172478_S_80172478_0 *)action)->unk_A8.s;
        ((R07_80172478_S_80172478_0 *)action)->unk_90 -= ((R07_80172478_S_80172478_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            target_x = ((SpriteFrameState *)sprite)->tile_x;
            pos_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = ((EntityRec *)motion)->y.w.i;
            pos_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((((SpriteFrameState *)sprite)->tile_y << 6) - pos_y) << 16) /
                ((R07_80172478_S_80172478_0 *)action)->unk_A8.s;

            ((R07_80172478_S_80172478_0 *)action)->unk_A4 =
                (-rsin(((R07_80172478_S_80172478_0 *)action)->unk_A8.s * 0x199)) << 10;
        }

        height_offset = ((R07_80172478_S_80172478_0 *)action)->unk_90;
        arc_offset = ((R07_80172478_S_80172478_0 *)action)->unk_A4;
        next_move_ticks = ((R07_80172478_S_80172478_0 *)action)->unk_A8.u;
        height_offset += arc_offset;
        next_move_ticks -= 1;
        ((R07_80172478_S_80172478_0 *)action)->unk_A8.u = next_move_ticks;
        ((R07_80172478_S_80172478_0 *)action)->unk_90 = height_offset;
        if ((next_move_ticks << 16) >= 0) {
            break;
        }

        ((R07_80172478_S_80172478_0 *)action)->unk_90 = 0;
        ((R07_80172478_S_80172478_0 *)action)->unk_98 &= 0xFFF7;
        ((R07_80172478_S_80172478_2 *)actor)->unk_1C.s |= 0x08000000;
        ((R07_80172478_S_80172478_0 *)action)->unk_9B++;
        break;
    case 2:
        if (((R07_80172478_S_80172478_2 *)actor)->unk_1C.s & 0x08000000) {
            ((R07_80172478_S_80172478_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
            ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174168);
            select_sprite_entry(
                sprite,
                ((u8 *)D_80174168)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R07_80172478_S_80172478_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);

            ((R07_80172478_S_80172478_0 *)action)->unk_9B++;
        }
        break;
    }
    action_ticks = ((R07_80172478_S_80172478_0 *)action)->unk_96 - 1;
    ((R07_80172478_S_80172478_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
    spend_actor_mp(actor, 4);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = ((R07_80172478_S_80172478_2 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((R07_80172478_S_80172478_2 *)actor)->unk_46 & 0x8000) {
            ((R07_80172478_S_80172478_2 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((R07_80172478_S_80172478_2 *)actor)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)sprite)->tile_x,(s16)((SpriteFrameState *)sprite)->tile_y,(s16)(reference_tile_object.tile_position.parts.tile_x),(s16)(reference_tile_object.tile_position.parts.tile_y),
                &direction_aux));
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((R07_80172478_S_80172478_0 *)action)->unk_8C = ((void *)dispatch_monster_move_attack_spell);
        on_actor_status_updated(actor);
    }
}

/*
 * Runs update_linked_actor_motion and installs dispatch_monster_move_attack_spell only when it
 * succeeds and the signed floor-trap check returns positive.
 */
void update_grineut_linked_motion(Resource07CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_linked_actor_motion(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = dispatch_monster_move_attack_spell;
        }
    }
}

/* Animates a backward step and forward attack, applies damage, then recenters the actor and spends MP. */
void complete_staged_destination_movement(R07_8017284C_S_8017284C_0 *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor)
{
    s16 timer;
    s32 direction_y;
    s32 direction;
    s32 wrap_base;
    s32 x_velocity;
    s32 y_velocity;
    s32 z_velocity;
    s32 speed_component;
    s32 facing;
    s32 state;

    state = action->phase;
    switch (state) {
    case 0:
        if (sprite->flags & 0x8000) {
            action->phase = 3;
            action->timer.s = 0;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        facing = ((u16)actor->facing >> 9) & 7;
        direction = facing + 4;
        wrap_base = direction;
        if (direction < 0) {
            wrap_base = facing + 11;
        }
        direction -= wrap_base & 0x18;
        motion->velocity_x =
            (*(s16 *)((u8 *)(((s8 *)dir_step_x)) + (direction * 2))) * 0x60000;
        direction_y = (*(s16 *)((u8 *)(((s8 *)dir_step_y)) + (direction * 2)));
        motion->velocity_z = 0;
        motion->velocity_y = direction_y * 0x60000;
        sprite->frameTable = ((u8 *)grineut_frame_set_3);
        select_sprite_entry(sprite,
            (*(u8 *)((u8 *)(((u8 *)grineut_frame_set_3)) + (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7))),
            0);
        action->timer.s = 0;
        action->phase += 1;
        return;

    case 1:
        x_velocity = motion->velocity_x;
        y_velocity = motion->velocity_y;
        motion->velocity_x = x_velocity - (x_velocity >> 2);
        motion->velocity_y = y_velocity - (y_velocity >> 2);
        if (sprite->flags & 0xE000) {
            sprite->frameTable = ((u8 *)D_80174170);
            select_sprite_entry(sprite,
                (*(u8 *)((u8 *)(((u8 *)D_80174170)) + (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7))),
                0);
            action->timer.s = 0x14;
            action->phase += 1;
            return;
        }
        return;

    case 2:
        timer = action->timer.u - 1;
        z_velocity = motion->velocity_z;
        action->timer.s = timer;
        if (timer < 12) {
            z_velocity += 0x1400;
        } else {
            z_velocity += 0x20000;
        }
        motion->velocity_z = z_velocity;
        action->unk_90 += z_velocity;

        if (action->timer.s == 0x11) {
            play_sound_if_enabled(0x808);
            direction = ((u16)actor->facing >> 9) & 7;
            speed_component = (*(s16 *)((u8 *)(((s8 *)dir_step_x)) + (direction * 2))) * 0x30000;
            motion->velocity_x = speed_component + (speed_component >> 2);
            speed_component = (*(s16 *)((u8 *)(((s8 *)dir_step_y)) + (direction * 2))) * 0x30000;
            motion->velocity_y = speed_component + (speed_component >> 2);
        }

        if (((sprite->unk_04 == 3) &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        }

        if (((sprite->unk_04 == 5) &&
             (sprite->flags & 0x1000)) ||
            (sprite->flags & 0x8000)) {
            motion->velocity_x =
                ((((sprite->tile_x << 6) + 0x20) << 16) -
                 motion->x.v) / action->timer.s;
            motion->velocity_y =
                ((((sprite->tile_y << 6) + 0x20) << 16) -
                 motion->y.v) / action->timer.s;
        }

        if ((action->timer.s <= 0) ||
            (sprite->flags & 0x8000)) {
            action->phase += 1;
            return;
        }
        return;

    case 3:
        if ((action->timer.s <= 0) ||
            (sprite->flags & 0x8000)) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
            spend_actor_mp(actor, 0x100);
            action->unk_8C = ((void *)dispatch_monster_move_attack_spell);
            g_dungeon_status.active_actor = 0;
            action->unk_98 &= 0xFFF7;
            advance_status_timers(actor);
            if (actor->pending_turn_updates == 0) {
                actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
                return;
            }
            ((void * *)actor_update_node_cursor)[0] = (u8 *)actor - 0x20;
        }
    }
}

/* Starts a targeted spell with a two-row effect, waits for its animation, and restores actor movement. */
void advance_actor_stored_path_2(void *action, ObjectPosition *motion, void *sprite, void *actor) {
    u16 pos[3];
    s16 is_special;
    u8 *item;
    void *node;
    u8 *state;

    is_special = 0;
    state = (u8 *)(((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8);
    switch ((u8)state) {
    case 0:
        if ((*(u32 *)((u8 *)actor + 0x1C)) & ACTOR_PLAYER_SIDE) {
            u32 kind = ((*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF) - 1;
            switch (kind) {
            case 6:
                is_special = 1;
                /* fall through */
            case 2:
                item = (u8 *)actor + 0xE;
                break;
            case 5:
                is_special = 1;
                /* fall through */
            case 1:
                item = (u8 *)actor + 0xB;
                break;
            case 4:
                is_special = 1;
                /* fall through */
            case 0:
                item = (u8 *)actor + 8;
                break;
            default:
                item = 0;
                break;
            }
        } else {
            s32 kind = (*(u16 *)((u8 *)actor + 0x46)) & 0x3FFF;
            switch (kind) {
            case 3:
                item = (u8 *)actor + 0xE;
                break;
            case 2:
                item = (u8 *)actor + 0xB;
                break;
            case 1:
                item = (u8 *)actor + 8;
                break;
            default:
                item = 0;
                break;
            }
        }
        if (*item != 0) {

            ((Rec_func_80172CC0_arg0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 use_existing;

                use_existing = is_special;
                if (use_existing) {
                    node = primary_actor_record;
                    (*(void * *)((u8 *)actor + 0x60)) = node;
                    goto copy_existing;
                }
            }

            {
                u8 *item_table = item_action_definitions;
                u8 item_id = *item;
                u8 *item_entry = item_table + item_id * 20;
                if (item_entry[0x12] == 2) {
                    node = (*(void * *)((u8 *)actor + 0x60));
                    if (node != 0) {
copy_existing:
                        {

                            state = ((R07_80172CC0_S_80172CC0_1_pre *)node)[-1].unk_00;
                            (*(u8 *)((u8 *)actor + 0x72)) = ((R07_80172CC0_S_80172CC0_2 *)state)->unk_24;
                            (*(u8 *)((u8 *)actor + 0x73)) = ((R07_80172CC0_S_80172CC0_2 *)state)->unk_25;
                        }

                    }
                } else {
                    s8 x;
                    s8 y;

                    ((ActorRecord *)actor)->target = (void *)scan_actor_along_heading(
                        actor,
                        ((SpriteFrameState *)sprite)->tile_x,
                        ((SpriteFrameState *)sprite)->tile_y,
                        ((ActorRecord *)actor)->facing,
                        0x10);
                    x = ((ActorRecord *)actor)->target_tile_x;
                    y = ((ActorRecord *)actor)->target_tile_y;
                    x = abs(x);
                    y = abs(y);
                    ((ActorRecord *)actor)->target_tile_x = x;
                    ((ActorRecord *)actor)->target_tile_y = y;
                }
            }

            pos[0] = ((u16)motion->x.w.i);
            pos[1] = ((u16)motion->y.w.i);
            pos[2] = ((u16)motion->z.w.i);
            if (create_actor_spell_effect(actor, item, is_special, (u8 *)action + 0x98)) {
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
                play_sound_if_enabled(0x703);
                create_two_row_object_group(pos, (s16)((*item - 1) % 3));
                ((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8++;
                return;
            }
            return;

        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);
        g_dungeon_status.active_actor = 0;
        {
            u8 *active_entity = (u8 *)primary_actor_record;
            (*(u16 *)((u8 *)active_entity + 0xA6))--;
        }
        advance_status_timers(actor);
        (*(u8 *)((u8 *)actor + 0x6D))--;
        ((Rec_func_80172CC0_arg0 *)action)->unk_8C.as_pv = ((void *)dispatch_monster_move_attack_spell);
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        return;
    case 1:
        item = (u8 *)(s32)get_cd_command_queue_depth();
        if (item) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            return;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8++;
                        /* fall through */

    case 2:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174180);
        select_sprite_entry(
            sprite,
            ((u8 *)D_80174180)[((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
            0);
        ((Rec_func_80172CC0_arg0 *)action)->unk_A8 = 0x10;
        ((Rec_func_80172CC0_arg0 *)action)->unk_9B.as_u8++;
        return;

    case 3:
        {
            s16 sound_timer = ((Rec_func_80172CC0_arg0 *)action)->unk_A8 - 1;
            ((Rec_func_80172CC0_arg0 *)action)->unk_A8 = sound_timer;
            if (sound_timer == 0) {
                play_sound_if_enabled(0x610);
            }
        }

        if ((((SpriteFrameState *)sprite)->unk_04 == 12 &&
            (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0xE000)) {
            ((SpriteFrameState *)sprite)->flags |= 0x800;
            ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 = 0x10;
            ((Rec_func_80172CC0_arg0 *)action)->unk_98 |= 0x80;
        }

        {
            u16 anim_timer = ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 - 1;
            ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 = anim_timer;
            if ((s16)anim_timer <= 0) {
                ((Rec_func_80172CC0_arg0 *)action)->unk_96.as_u16 = 0;
                ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
            }
        }

        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);

        if (((SpriteFrameState *)sprite)->frameTable != ((u8 *)grineut_frame_set_1)) {
            ((SpriteFrameState *)sprite)->frameTable = ((u8 *)grineut_frame_set_1);
            select_sprite_entry(
                sprite,
                ((u8 *)grineut_frame_set_1)[((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)actor + 0x2A)) + 0x100) >> 9) & 7],
                0);
        }

        {
            if (((s32)g_dungeon_status.active_actor) != 0) {
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        ((SpriteFrameState *)sprite)->flags &= 0xF7FF;
        ((Rec_func_80172CC0_arg0 *)action)->unk_8C.as_pv = ((void *)dispatch_monster_move_attack_spell);
        advance_status_timers(actor);
        if ((*(s8 *)((u8 *)actor + 0x6D)) > 0) {
            (*(u8 *)((u8 *)actor + 0x6D))--;
        }
        (*(u8 *)((u8 *)actor + 0x73)) = 0;
        (*(u8 *)((u8 *)actor + 0x72)) = 0;
        (*(u16 *)((u8 *)actor + 0x46)) &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        break;

    default:
        break;
    }

    return;
}

/* Applies a value change and knockback, decelerates the actor, then recenters it and restores movement. */
void settle_directional_motion_at_tile(void *motion_state, void *motion, void *sprite, void *entity)
{
    s32 direction;
    s16 timer;
    s32 tracked_entity;

    direction = (((EntityRec *)entity)->unk_6A >> 9) & 7;
    switch (((R07_80173238_S_80173238_1 *)motion_state)->phase) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        ((R07_80173238_S_80173238_2 *)motion)->unk_0C = ((s16 *)((s8 *)dir_step_x))[direction] << 18;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 = ((s16 *)((s8 *)dir_step_y))[direction] << 18;
        ((R07_80173238_S_80173238_1 *)motion_state)->phase++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            ((R07_80173238_S_80173238_2 *)motion)->unk_14 = 0;
            ((R07_80173238_S_80173238_2 *)motion)->unk_10 = 0;
            ((R07_80173238_S_80173238_2 *)motion)->unk_0C = 0;
            begin_actor_display_action(motion_state, motion, sprite, ((u8 *)D_80174178));
            return;
        }
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((R07_80173238_S_80173238_1 *)motion_state)->timer.s = 0;
            ((R07_80173238_S_80173238_1 *)motion_state)->phase = 3;
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        ((R07_80173238_S_80173238_1 *)motion_state)->timer.s = timer;

        ((R07_80173238_S_80173238_2 *)motion)->unk_0C -= ((R07_80173238_S_80173238_2 *)motion)->unk_0C / 4;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 -= ((R07_80173238_S_80173238_2 *)motion)->unk_10 / 4;

    case 1:
        ((R07_80173238_S_80173238_2 *)motion)->unk_0C -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;

        if (((R07_80173238_S_80173238_1 *)motion_state)->timer.s > 0) {
            ((R07_80173238_S_80173238_1 *)motion_state)->timer.s = ((R07_80173238_S_80173238_1 *)motion_state)->timer.u - 1;
        } else if (((SpriteFrameState *)sprite)->flags & 0x6000) {
            ((R07_80173238_S_80173238_1 *)motion_state)->timer.s = 0;
        }

        if (((R07_80173238_S_80173238_1 *)motion_state)->timer.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((R07_80173238_S_80173238_2 *)motion)->unk_14 = 0;
            ((R07_80173238_S_80173238_2 *)motion)->unk_10 = 0;
            ((R07_80173238_S_80173238_2 *)motion)->unk_0C = 0;
            begin_actor_display_action(motion_state, motion, sprite, ((u8 *)D_80174178));
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)grineut_frame_set_4);
        select_sprite_entry(
            sprite,
            ((u8 *)grineut_frame_set_4)[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((R07_80173238_S_80173238_1 *)motion_state)->phase++;
        return;

    case 2:
        ((R07_80173238_S_80173238_2 *)motion)->unk_0C -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            return;
        }

        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)grineut_frame_set_4);
        select_sprite_entry(
            sprite,
            ((u8 *)grineut_frame_set_4)[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((R07_80173238_S_80173238_1 *)motion_state)->timer.s = 8;
        ((R07_80173238_S_80173238_1 *)motion_state)->phase++;
        return;

    case 3:
        timer = ((R07_80173238_S_80173238_1 *)motion_state)->timer.s;
        if (timer != 0) {
            {
                s32 target_x = ((SpriteFrameState *)sprite)->tile_x << 6;
                s32 current_x = ((R07_80173238_S_80173238_2 *)motion)->unk_00.at02.v - 0x20;
                ((R07_80173238_S_80173238_2 *)motion)->unk_0C = ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = ((SpriteFrameState *)sprite)->tile_y << 6;
                s32 current_y = ((R07_80173238_S_80173238_2 *)motion)->unk_04.at02.v - 0x20;
                ((R07_80173238_S_80173238_2 *)motion)->unk_10 =
                    ((target_y - current_y) << 15) / ((R07_80173238_S_80173238_1 *)motion_state)->timer.s;
            }
        }

        timer = ((R07_80173238_S_80173238_1 *)motion_state)->timer.u - 1;
        ((R07_80173238_S_80173238_1 *)motion_state)->timer.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        ((R07_80173238_S_80173238_2 *)motion)->unk_14 = 0;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 = 0;
        ((R07_80173238_S_80173238_2 *)motion)->unk_0C = 0;
        ((R07_80173238_S_80173238_2 *)motion)->unk_00.at00.v = ((((SpriteFrameState *)sprite)->tile_x << 6) + 0x20) << 16;
        ((R07_80173238_S_80173238_2 *)motion)->unk_04.at00.v = ((((SpriteFrameState *)sprite)->tile_y << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->tile_x, ((SpriteFrameState *)sprite)->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        ((R07_80173238_S_80173238_1 *)motion_state)->unk_8C = ((void *)dispatch_monster_move_attack_spell);

        return;

    default:
        return;
    }
}

/* Runs the shared actor defeat and removal sequence with the supplied callback arguments. */
void remove_defeated_grineut(void *state, void *motion, void *position, void *actor)
{
    update_actor_defeat_removal(state, motion, position, actor);
}

/* Runs the shared hop and shrink sequence for the actor with the supplied callback arguments. */
void shrink_hopping_grineut(void *state, void *motion, void *position, void *actor)
{
    update_actor_hop_and_shrink(state, motion, position, actor);
}

/* Runs the shared actor removal sequence with the supplied callback arguments. */
void advance_grineut_removal(void *state, void *motion, void *position, void *actor)
{
    advance_actor_removal(state, motion, position, actor);
}

/*
 * Runs update_actor_hop_and_grow and installs dispatch_monster_move_attack_spell when it returns
 * nonzero.
 */
void grow_hopping_grineut(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_hop_and_grow(state, motion, position, actor)) {
        state->callback = dispatch_monster_move_attack_spell;
    }
}

/* Waits for a status effect to clear, updates actor status and activity counts, then restores movement. */
void update_sleeping_grineut(void *controller, s32 actor_index, void *sprite, ActorRecord *actor)
{
    DungeonGlobalStatus *dungeon_status;
    s32 actor_flags;
    s32 state;

    state = ((Rec_func_801736F4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)grineut_alt_direction_frames);
            select_sprite_entry(
                sprite,(u8)(((u8 *)grineut_alt_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle
                             + actor->facing + 0x100)
                            >> 9) & 7]),
                0);
        }
        {
            DungeonGlobalStatus *dungeon_counters;
            dungeon_counters = &g_dungeon_status;
            (*(u16 *)&dungeon_counters->activity_counts.parts.pending_action_count)--;
        }
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
        return;

    case 1:
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {
            void *anim_table;
            anim_table = ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv;
            if (anim_table == ((u8 *)grineut_frame_set_3)) {
                ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv = ((u8 *)grineut_frame_set_2);
            } else if (anim_table == ((u8 *)grineut_frame_set_2)) {
                ((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv = ((u8 *)grineut_alt_direction_frames);
            }
            select_sprite_entry(
                sprite,(u8)(((u8 *)((Rec_func_800AA258_arg2 *)sprite)->unk_2C.as_pv)
                    [((g_game_work.view.camera_rotation.parts.viewAngle
                       + actor->facing + 0x100)
                      >> 9) & 7]),
                0);
        }

        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) == 0) {
            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)grineut_frame_set_2);
            select_sprite_entry(
                sprite,(u8)(((u8 *)grineut_frame_set_2)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                            >> 9) & 7]),
                0);
            if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x8000) {
                actor->flags1C &= ~ACTOR_ASLEEP;
                ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)dispatch_monster_move_attack_spell);
                return;
            }
            {
                DungeonGlobalStatus *dungeon_counters = &g_dungeon_status;
                (*(u16 *)&dungeon_counters->activity_counts.parts.pending_action_count)++;
            }
            ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
            return;
        } else {
            dungeon_status = &g_dungeon_status;
            if (!(dungeon_status->flags & 0x1000)
                && ((actor->hp_delta == 0)
                    || (begin_ready_actor_directional_action(controller, actor_index, sprite, 0) == 0))) {

                if (actor->mp == 0) {
                    if (dungeon_status->flags & 0x2008) {
                        return;
                    }
                    advance_actor_pending_action(controller, actor_index, sprite, actor);
                    return;
                }

                if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                    return;
                }
                actor_flags = actor->flags1C;
                if (actor_flags & 0x100) {
                    begin_pushed_actor_move(controller, actor_index, sprite, actor);
                    return;
                }
                if (actor_flags & 0x80000) {
                    begin_actor_move_to_target_facing(controller, actor_index, sprite, actor);
                    update_grineut_parent_motion(controller, actor_index, sprite, actor);
                    return;
                }
                if (actor->pending_turn_updates == 0) {
                    return;
                }
                if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                    if ((check_entity_relation(
                             actor,
                             ((s32)primary_actor_record->previous_actor_header)
                                 + 0x20)
                         << 16)
                        != 0) {
                        return;
                    }
                }

                update_actor_status_and_mp(actor);
                on_actor_status_updated(actor);
                if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                    TileObject *room_base;
                    s32 room_id;
                    room_base = &reference_tile_object;
                    room_id = ((Rec_func_800AA258_arg2 *)sprite)->unk_26.as_s8;
                    if (((room_id == room_base->room_index)
                         && (room_id >= 0))
                        || (((s16)get_tile_chebyshev_distance(room_base, sprite)) < 2)) {
                        if (!(generate_random_value() & 7)) {
                            clear_slots_of_type(actor, STATUS_SLEEP);
                        }
                    }
                }
                if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                    return;
                }

                (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)grineut_frame_set_2);
                select_sprite_entry(
                    sprite,(u8)(((u8 *)grineut_frame_set_2)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                                >> 9) & 7]),
                    0);
                if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0x8000) {
                    actor->flags1C &= ~ACTOR_ASLEEP;
                    ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)dispatch_monster_move_attack_spell);
                    return;
                }
                {
                    DungeonGlobalStatus *dungeon_counters = &g_dungeon_status;
                    (*(u16 *)&dungeon_counters->activity_counts.parts.pending_action_count)++;
                }
                ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
                return;
            }
        }
        return;

    case 2:
        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *dungeon_counters;
            dungeon_counters = &g_dungeon_status;
            (*(u16 *)&dungeon_counters->activity_counts.parts.pending_action_count)--;
        }
        actor->flags1C &= ~ACTOR_ASLEEP;
        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)grineut_frame_set_2);
        select_sprite_entry(
            sprite,(u8)(((u8 *)grineut_frame_set_2)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
                        >> 9) & 7]),
            0);
        ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)dispatch_monster_move_attack_spell);
        return;

        return;
    }
}

/* Waits for MP recovery while processing actor status, then restores the normal animation and movement. */
void dim_and_clear_flagged_effect(void *controller, void *context, void *sprite, ActorRecord *entity)
{
    s32 state;

    state = ((Rec_func_801736F4_arg0 *)controller)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = ((u8 *)grineut_alt_direction_frames);
        (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
        select_sprite_entry(sprite,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
        return;
    }
    case 1:
    {
        u32 entity_flags;

        if (entity->mp != 0) {

            (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)grineut_frame_set_2);
            select_sprite_entry(sprite,
                ((u8 *)grineut_frame_set_2)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            (((u32)entity->flags1C)) |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, entity);
            update_grineut_parent_motion(controller, context, sprite, entity);
            return;
        }

        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
        }

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (entity->mp == 0) {
            return;
        }

        (*(void * *)((u8 *)sprite + 0x2C)) = ((u8 *)grineut_frame_set_2);
        select_sprite_entry(sprite,
            ((u8 *)grineut_frame_set_2)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        ((Rec_func_801736F4_arg0 *)controller)->unk_9B++;
    }
        break;
    case 2:
        if (((Rec_func_800AA258_arg2 *)sprite)->unk_14 & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~(ACTOR_MP_EMPTY | ACTOR_ASLEEP);
            ((Rec_func_801736F4_arg0 *)controller)->unk_8C = ((void *)dispatch_monster_move_attack_spell);
        }

        return;
    }
}

/*
 * Resumes the main actor handler after parent motion completes and the signed floor-trap check is
 * positive; during motion, restores movement frames when the alternate table is active and flags
 * 0x208 are clear.
 */
void update_grineut_parent_motion(R07_80173EF4_Actor *actor, s32 action, R07_80173EF4_Entity *entity, R07_80173EF4_MapObject *map_object)
{
    if (update_actor_transform_from_parent(actor, action, entity, map_object) != 0) {
        if ((check_actor_floor_trap(entity, map_object) << 16) > 0) {
            actor->unk_8C = ((u8 *)dispatch_monster_move_attack_spell);
            return;
        }
    } else if (entity->unk_2C == ((u8 *)grineut_alt_direction_frames) &&
               !(map_object->unk_1C & 0x208)) {
        entity->unk_2C = ((u8 *)grineut_move_direction_frames);
        select_sprite_entry(entity,(s16)(((u8 *)grineut_move_direction_frames)[((g_game_work.view.camera_rotation.parts.viewAngle + map_object->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }
}

/*
 * Runs update_thrown_actor_travel and installs dispatch_monster_move_attack_spell only when it
 * succeeds and the signed floor-trap check returns positive.
 */
void update_thrown_grineut(Resource07CallbackState *state, void *entity, void *position, void *graphic)
{
    if (update_thrown_actor_travel(state, entity, position, graphic)) {
        if ((s16)check_actor_floor_trap(position, graphic) > 0) {
            state->callback = dispatch_monster_move_attack_spell;
        }
    }
}

/*
 * Runs interpolate_actor_to_terrain_tile and installs dispatch_monster_move_attack_spell when it
 * returns nonzero.
 */
void settle_grineut_on_tile(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (interpolate_actor_to_terrain_tile(state, motion, position, actor)) {
        state->callback = dispatch_monster_move_attack_spell;
    }
}

/*
 * Runs update_spinning_actor_fall and installs dispatch_monster_move_attack_spell when it returns
 * nonzero.
 */
void update_spinning_grineut_fall(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_spinning_actor_fall(state, motion, position, actor)) {
        state->callback = dispatch_monster_move_attack_spell;
    }
}

/* Runs update_actor_fade_in and installs dispatch_monster_move_attack_spell when it returns nonzero. */
void fade_in_grineut(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (update_actor_fade_in(state, motion, position, actor)) {
        state->callback = dispatch_monster_move_attack_spell;
    }
}

/*
 * Runs resolve_actor_floor_trap_once and installs dispatch_monster_move_attack_spell when it
 * returns positive.
 */
void resolve_grineut_floor_trap(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (resolve_actor_floor_trap_once(state, motion, position, actor) > 0) {
        state->callback = dispatch_monster_move_attack_spell;
    }
}

/*
 * Runs propagate_actor_action_flag and installs dispatch_monster_move_attack_spell when it returns
 * positive.
 */
void propagate_grineut_action_flag(Resource07CallbackState *state, void *motion, void *position, void *actor)
{
    if (propagate_actor_action_flag(state, motion, position, actor) > 0) {
        state->callback = dispatch_monster_move_attack_spell;
    }
}
