#include "modules/dungeon_ovl_e0365c.h"
void *(*const e0365c_spawn_entry)(s16,s16,s16,s16) = spawn_mode_dependent_112_object;
#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void *spawn_mode_dependent_112_object(s16 flags,s16 attr_x,s16 attr_y,s16 attr_height) {
 E_80170854_SpawnActor *actor=0;
 E_80170854_SpawnObject *object;
 E_80170854_SpawnMotion *motion;
 s16 saved_flags;
 s32 kind;
 s8 tile_x; s16 height; s8 tile_y;
 {
 SpriteFrameState *sprite;
 E_80170854_SpawnState *state;
 tile_x=attr_x; height=attr_height; tile_y=attr_y;
 object=allocate_list_node(0x112,&D_80083498);
 saved_flags=flags;
 if(object) {
  actor=(E_80170854_SpawnActor *)((u8 *)object+0x20);
  actor->kind=0x1C;
  register_node(object,project_sprite_chain);
  motion=object->motion;
  kind=flags&3;
  motion->height=height;
  sprite=object->sprite;
  sprite->unk_24=tile_x;
  sprite->unk_25=tile_y;
  state=(E_80170854_SpawnState *)actor;
  if(kind==1) {
   actor->handler=update_actor_behavior_facing_and_animation_2;
   actor->flags14|=0x6000;
   actor->flags1C|=0x6000;
   sprite->frameTable=D_80174510;
  } else if(kind>=2) {
   actor->handler=update_actor_behavior_facing_and_animation_2;
   actor->flags14|=0x2000;
   actor->flags1C|=0x2000;
   sprite->frameTable=D_80174510;
  } else if((s16)(flags&~3)==0) {
   if(!(actor->flags14&0x200) && (generate_random_value()&1)) {
    set_or_clear_actor_status_slot(actor,1,(generate_random_value()&0x3F)|0x20);
    sprite->frameTable=D_80174538;
   }
   state->handler=update_actor_behavior_facing_and_animation_2;
   sprite->frameTable=D_80174510;
  } else { actor->handler=update_actor_behavior_facing_and_animation_2;
   sprite->frameTable=D_80174510;
  }
  object->update=update_entity_facing_and_ground;
  initialize_actor_sprite_and_animation(object,motion,sprite,saved_flags);
  state->action_id=0xFF;
  state->direction=-1;
  try_move_actor_to_valid_position(state,motion,sprite,actor);
 }
 }
 return actor;
}
#include "modules/dungeon_ovl_e0365c.h"

void update_entity_facing_and_ground(void *entity, E_80170A58_S_80170A58_2 *motion, void *monster)
{
    void *actor = entity;
    s32 direction;
    s16 direction_copy;
    s16 old_direction;
    s32 facing_angle;
    E_80170A58_Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        E_80170A58_Callback early_callback;

        early_callback = (*(E_80170A58_Callback *)((u8 *)entity + 0x8C));
        if (early_callback == (E_80170A58_Callback)&update_actor_behavior_facing_and_animation_2) {
            early_callback(entity, motion, monster, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }


    old_direction = (*(s8 *)((u8 *)entity + 0x6D));
    if (refresh_actor_facing_and_lifecycle(entity, motion, monster, entity) != 0) {
        return;
    }

    monster_flags = ((E_80170A58_S_80170A58_0 *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        facing_angle = g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (facing_angle >> 9) & 7;
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = ((E_80170A58_S_80170A58_0 *)monster)->unk_2C;
            if (tile_map != 0) {
                select_indirect_table_entry(monster, tile_map[direction_index], ((E_80170A58_S_80170A58_0 *)monster)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (dir_sprite_flag[direction_copy] != 0) {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 |= 1;
        } else {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(((E_80170A58_S_80170A58_1 *)actor)->unk_1C & 0x20)) {
            if (!(((E_80170A58_S_80170A58_0 *)monster)->unk_14 & 0x40)) {
                func_800478B8(monster);
            }
            apply_monster_koyaw_data(((E_80170A58_S_80170A58_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
        } else {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 |= 0x7000;
            apply_monster_koyaw_data(((E_80170A58_S_80170A58_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
        }
    } else {
        if (monster_flags & 0x0800) {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 = monster_flags & 0x8FFF;
        } else {
            ((E_80170A58_S_80170A58_0 *)monster)->unk_14 = monster_flags | 0x7000;
        }
    }

    callback = (*(E_80170A58_Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, actor);
    }

    D_80174568[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, actor);

    if (old_direction != ((E_80170A58_S_80170A58_1 *)actor)->unk_6D) {
        try_move_actor_to_valid_position(entity, motion, monster, actor);
    }

    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;

    if ((*(u16 *)((u8 *)entity + 0x98)) & 8) {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    } else {
        motion->unk_14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D))++;
    }

    (*(s32 *)((u8 *)entity + 0x90)) += motion->unk_14;

    if (!((*(u16 *)((u8 *)entity + 0x98)) & 4)) {
        floor_height = sample_terrain_surface_height(motion->unk_00.at02.v,
                              motion->unk_04.at02.v,
                              (s16)(((E_80170A58_S_80170A58_1 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((E_80170A58_S_80170A58_1 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height) {
                (*(u16 *)((u8 *)entity + 0x98)) &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor_height - ((E_80170A58_S_80170A58_1 *)actor)->unk_88.u;
                }

                motion->unk_14 = 0;
                ((E_80170A58_S_80170A58_1 *)actor)->unk_1C |= 0x08000000;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
            }
            if (((E_80170A58_S_80170A58_1 *)actor)->unk_1C & 0x40000000) {
                ((E_80170A58_S_80170A58_1 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height((((E_80170A58_S_80170A58_0 *)monster)->unk_24 << 6) | 0x20,
                                      (((E_80170A58_S_80170A58_0 *)monster)->unk_25 << 6) | 0x20,
                                      (s16)(((E_80170A58_S_80170A58_1 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) += ((E_80170A58_S_80170A58_1 *)actor)->unk_88.u - floor_height;
                ((E_80170A58_S_80170A58_1 *)actor)->unk_88.u = floor_height;
            }
        } else {
            ((E_80170A58_S_80170A58_1 *)actor)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((E_80170A58_S_80170A58_1 *)actor)->unk_1C &= 0xF7FFFFFF;
    }

    motion->unk_0A =
        ((E_80170A58_S_80170A58_1 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    ((E_80170A58_S_80170A58_0 *)monster)->unk_14 |= 0x40;

}
#include "modules/dungeon_ovl_e0365c.h"

void update_actor_behavior_facing_and_animation_2(void *actor_in, void *context_in, void *sprite_in, void *status_in)
{
    void *status;
    u8 *anim_table;
    s32 tile_record;
    s32 direction_aux;
    u32 initial_flags = g_dungeon_status.flags;

    status = status_in;

    if (initial_flags & 0x1000) {
        ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A = 0xE;
        advance_actor_path_step(actor_in, context_in, sprite_in, status);
        return;
    }


    if (((E_80170E5C_S_80170E5C_1 *)status)->unk_25 == 0) {
        advance_actor_pending_action(actor_in, context_in, sprite_in, status);
        if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C == D_80174538) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = D_80174530;
        select_sprite_entry(sprite_in,
            D_80174530[((g_game_work.view.camera_rotation.parts.viewAngle + ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x200) {
        if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C == D_80174538) {
            ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A = 0xD;
            ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9B = 1;
            ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_8C = 0;
            ((E_80170E5C_S_80170E5C_1 *)status)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_in, context_in, sprite_in, D_80174530)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor_in, context_in, sprite_in, status);
            return;
        }

        {
            s32 next_state;
            s32 actor_state;

            actor_state = ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A;
            next_state = 0xE;

            if (actor_state != next_state) {
                anim_table = D_80174520;
                if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C != anim_table) {
                    (*(void * *)((u8 *)sprite_in + 0x2C)) = anim_table;
                    select_sprite_entry(sprite_in,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                }
                ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_9A = next_state;
            }
        }

        ((E_80170E5C_S_80170E5C_0 *)actor_in)->unk_98 &= 0xFFF3;
        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_in, context_in, sprite_in, D_80174548)) {
                return;
            }
        }

        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, context_in, sprite_in, status);
            update_actor_landing_and_trap(actor_in, context_in, sprite_in, status);
            return;
        }

        if ((s16)can_entity_gain_level(status) != 0) {
            process_selected_actor_record(actor_in, context_in, sprite_in, status);
        }
    }

    tile_record = find_active_rect_containing_point(((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v);
    ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_26 = tile_record;

    if (((E_80170E5C_S_80170E5C_1 *)status)->unk_6D > 0) {
        if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x20) {
            update_actor_status_and_food(status);
            return;
        }
        if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            update_actor_targeting_and_movement(actor_in, context_in, sprite_in, status);
            return;
        }
        if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(status,
                        (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)select_actor_relation_state(actor_in, context_in, sprite_in, 0) == 0) {
                return;
            }
            ((E_80170E5C_S_80170E5C_1 *)status)->unk_46 |= 0x4000;
            if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
                update_actor_targeting_and_movement(actor_in, context_in, sprite_in, status);
                return;
            }
        }

        switch (((E_80170E5C_S_80170E5C_1 *)status)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)begin_actor_directional_attack(actor_in, context_in, sprite_in, status) == 0) {
                begin_actor_attack_after_status_check(actor_in, context_in, sprite_in, status);
            }
            return;

        case 9:
            if (((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x400) {
                s32 movement_flags;

                movement_flags = ((E_80170E5C_S_80170E5C_1 *)status)->unk_14;

                if (!(movement_flags & 0x80000000)) {
                    ((E_80170E5C_S_80170E5C_1 *)status)->unk_14 = movement_flags | 0x80000000;
                    ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.u += (generate_random_value() & 7) << 9;
                }
            }
            if ((s16)check_actor_ahead_height(actor_in, context_in, sprite_in, status) != 0) {
                return;
            }
            start_actor_directional_animation(actor_in, context_in, sprite_in, status);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *active_actor;
            s32 direction;

            direction = get_rounded_facing_and_rounding_flag(
                ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v,
                D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                &direction_aux);
            active_actor = D_800814A8;
            ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s = direction;
            if (active_actor->unk_9A == 0x11) {
                begin_actor_spell_action(actor_in, context_in, sprite_in, D_80174560, update_actor_behavior_facing_and_animation_2);
                return;
            }
        }

        case 12:
            update_actor_status_and_food(status);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_in, context_in, sprite_in, D_80174560, update_actor_behavior_facing_and_animation_2);
            return;

        case 11:
        case 4:
        default:
            update_actor_targeting_and_movement(actor_in, context_in, sprite_in, status);
            return;
        }
    } else if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x2000)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(D_800E2970[record_index].flags & 2)) {
            if (!(((E_80170E5C_S_80170E5C_1 *)status)->unk_1C & 0x430)) {

                if ((s16)compare_monster_neighbor_values(((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v,
                        ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v, D_80082E80.tile_position.parts.tile_x,
                        D_80082E80.tile_position.parts.tile_y) != 0) {
                    ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s = get_rounded_facing_and_rounding_flag(
                        ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at00.v, ((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &direction_aux);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174520;
    if (((E_80170E5C_S_80170E5C_2 *)sprite_in)->unk_2C == anim_table) {
        return;
    }

update_table:
    (*(void * *)((u8 *)sprite_in + 0x2C)) = anim_table;
    select_sprite_entry(sprite_in,
        *(u8 *)((u32)(((g_game_work.view.camera_rotation.parts.viewAngle + ((E_80170E5C_S_80170E5C_1 *)status)->unk_2A.s + 0x100) >> 9) & 7) +
                (u32)anim_table),
        0);
}
#include "modules/dungeon_ovl_e0365c.h"

void update_actor_targeting_and_movement(u8 *object, void *entry_context, u8 *tile, u8 *actor)
{
    DungeonGlobalStatus *state = &g_dungeon_status;
    s32 actor_flags;
    s32 base_angle;
    s32 random_turn;
    s16 limit_turn;
    s16 turn_index;
    s16 angle;
    u16 state_flags;
    void *target_record;
    u8 *target_tile;
    state_flags = state->flags;
    limit_turn = 0;
    if ((state_flags & 0x4000) || (*(s8 *)(actor + 0x71)) >= 0) {
        if ((*(u8 *)(actor + 0x12)) >= 2 || (begin_actor_directional_attack(object, entry_context, tile, actor) << 16) == 0) {
            update_actor_status_and_food(actor);

            return;
        }
        if ((*((void **) ((u8 *)state + 0xC))) == actor) {
            *(u16 *)(actor + 0x46) = 0xC008;
        }

        return;
    }
    if (!(state_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(tile, actor, 3, 6, object + 0x9C);
    actor_flags = *(s32 *)(actor + 0x1C);
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            target_record = find_valid_monster_neighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25));
            if (target_record != 0) {
                target_tile = *((void **) (((u8 *) target_record) + (-0x14)));
                *(u16 *)(actor + 0x2A) = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(u8 *)(target_tile
                    + 0x24), *(u8 *)(target_tile + 0x25), object + 0x98);
                {
                    u8 path_length = (*(u8 *)(actor + 0x71)) & 0x7F;
                    *(u8 *)(actor + 0x71) = path_length;
                }
                return;
            }
            {
                s32 actor_state = *(s32 *)(actor + 0x14);
                base_angle = 0x80000000;
                if (actor_state >= 0) {
                    actor_state = base_angle | actor_state;
                    *(s32 *)(actor + 0x14) = actor_state;

                    random_turn = generate_random_value();
                    *(u16 *)(actor + 0x2A) += (random_turn & 7) << 9;
                }
            }
        }
        else {
            if (place_actor_at_directional_neighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor + 0x2A)) != 0) {
                *(u8 *)(actor + 0x71) &= 0x7F;
                return;
            }
        }
    }
    else if (actor_flags & 0x2000) {
        if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
            if (!(actor_flags & 0x20000)) {
                rebuild_monster_reachable_tiles(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
            }
            else {
                {
                    s32 direction = *(u8 *)(actor + 0x45);
                    s32 base_angle = *((s16 *) (((u8 *) D_800814A8) + 0x2A));
                    s32 direction_offset;
                    s32 target_x;
                    s32 target_y;
                    direction += base_angle >> 9;
                    direction_offset = (direction & 7) * 2;
                    target_x = (D_80082E80.tile_position.parts.tile_x) + (*((u16 *) (((u8 *) (((s8 *)dir_step_x))) + direction_offset)));
                    target_y = (D_80082E80.tile_position.parts.tile_y) + (*((u16 *) (((u8 *) (((s8 *)dir_step_y))) + direction_offset)));
                    if (((*(u8 *)(tile + 0x24)) == ((u16) target_x)) && ((*(u8 *)(tile + 0x25)) == ((u16) target_y))) {
                        *(u8 *)(actor + 0x71) &= 0x7F;
                        return;
                    }
                    {
                        u16 next_angle = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), (s16) target_x,
                            (s16) target_y, object + 0x98);
                        *(u16 *)(actor + 0x2A) = next_angle;
                        if ((check_movement_clearance_and_height((s16) next_angle, tile, actor, 0x20) << 16) <= 0) {
                            u8 *retry_goal = ((u8 *) (((s8 *)&D_80082E80.tile_position.parts.tile_x))) - 0x24;
                            *(u16 *)(actor + 0x2A) = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                                *(u8 *)(retry_goal + 0x24), *(u8 *)(retry_goal + 0x25), object + 0x98);
                        }
                    }
                }
                {
                    u8 *check_goal = ((u8 *) (((s8 *)&D_80082E80.tile_position.parts.tile_x))) - 0x24;
                    if ((compare_monster_neighbor_values(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(u8 *)(check_goal + 0x24),
                        *(u8 *)(check_goal + 0x25)) << 16) != 0) {
                        limit_turn = 1;
                    }
                }
            }
        }
    }
    else {
        {
            s8 tile_kind = *(s8 *)(tile + 0x26);
            if ((tile_kind >= 0) && (D_800E2970[tile_kind].flags & 2)) {
                rebuild_monster_reachable_tiles(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
            }
            else {
                if (!((*(u16 *)(actor + 0x46)) & 0x8000)) {
                    target_record = place_actor_at_directional_neighbor(actor, *(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), *(s16 *)(actor
                        + 0x2A));
                    if (target_record != 0) {
                        if ((*((s32 *) (((u8 *) target_record) + 0x1C))) & 0x2000) {
                            if ((s16)get_actor_height_difference(target_record, actor) < 0x81) {
                                if ((check_diagonal_side_height(((*(s16 *)(actor + 0x2A)) >> 9) & 0xFFFF, *(u8 *)(tile + 0x24),
                                    *(u8 *)(tile + 0x25), (s16) ((*(u16 *)(actor + 0x88)) - 0x20)) << 16) != 0) {
                                    *(u8 *)(actor + 0x71) &= 0x7F;
                                    return;
                                }
                            }
                        }
                    }
                }
                if (!((*(s32 *)(actor + 0x1C)) & 0x20000)) {
                    rebuild_monster_reachable_tiles(tile, *(s8 *)(object + 0x9C), actor, object + 0x98);
                }
                else {
                    u8 *angle_flags = object + 0x98;
                    *(u16 *)(actor + 0x2A) = get_rounded_facing_and_rounding_flag(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25),
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, angle_flags);
                    if ((compare_monster_neighbor_values(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y)
                         << 16) != 0) {
                        if ((s16)get_actor_height_difference(D_800814A8, actor) < 0x81) {
                            if ((check_diagonal_side_height(((*(s16 *)(actor + 0x2A)) >> 9) & 0xFFFF, *(u8 *)(tile + 0x24),
                                *(u8 *)(tile + 0x25), (s16) ((*(u16 *)(actor + 0x88)) - 0x20)) << 16) != 0) {
                                *(u8 *)(actor + 0x71) &= 0x7F;
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

    {
        turn_index = 0;
        for (; turn_index < 8; turn_index++) {
            base_angle = *(s16 *)(actor + 0x2A);

            if ((*(u16 *)(object + 0x98)) & 2) {
                base_angle -= D_8006CD00[turn_index];
                angle = base_angle;
            }
            else {
                base_angle += D_8006CD00[turn_index];
                angle = base_angle;
            }
            if ((check_movement_clearance_and_height((s16) angle, tile, actor, 0x20) << 16) > 0) {
                if (turn_index >= 3) {
                    s32 turn_limited = limit_turn;
                    if (turn_limited) {
                        *(u8 *)(actor + 0x71) &= 0x7F;
                        return;
                    }
                }
                *(u16 *)(actor + 0x2A) = angle;
                *((u8 *) (((u8 *) (actor + ((*(u8 *)(actor + 0x71)) & 0x7F))) + 0x74)) = *(u8 *)(tile + 0x24);
                *((u8 *) (((u8 *) (actor + ((*(u8 *)(actor + 0x71)) & 0x7F))) + 0x7C)) = *(u8 *)(tile + 0x25);
                (*(u8 *)(actor + 0x71))++;
                update_map_cell_flags_with_item_limit(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), ((*(s32 *)(actor + 0x1C)) & 0x2000)
                    ? (0x300) : (0x3000));
                {
                    s32 direction = ((*(u16 *)(actor + 0x2A)) >> 8) & 0xE;
                    u8 *step_x = (u8 *)dir_step_x;
                    step_x += direction;
                    *(u8 *)(tile + 0x24) += *step_x;
                    *(u8 *)(tile + 0x25) += *((u8 *) (((u8 *) (((s8 *)dir_step_y))) + direction));
                }
                cycle_map_cell_flags(*(u8 *)(tile + 0x24), *(u8 *)(tile + 0x25), ((*(s32 *)(actor + 0x1C)) & 0x2000)
                    ? (0x300) : (0x3000));
                break;
            }
            if (turn_index == 0) {
                if ((*((u16 *) (((u8 *) (((s8 *)&D_80082E80.tile_position.parts.tile_x))) + 0))) != (*(u16 *)(tile + 0x24))) {
                    if ((check_entity_relation(actor, (*((s32 *) (((u8 *) D_800814A8) + 0x58))) + 0x20) << 16) != 0) {
                        return;
                    }
                }
            }

        }
        if (turn_index >= 8) {
            *(u8 *)(actor + 0x71) &= 0x7F;
            *(u16 *)(actor + 0x46) &= 0x7FFF;
            update_actor_status_and_food(actor);
            return;
        }

    }

    *(u16 *)(actor + 0x46) &= 0x7FFF;
    *(u8 *)(object + 0x9C) = *(u8 *)(tile + 0x26);
    (*(u8 *)(actor + 0x6D))--;
    {
        DungeonGlobalStatus *move_state = &g_dungeon_status;
        (((u16)move_state->activity_counts.parts.pending_movement_count))++;
    }
    if ((*(s8 *)(actor + 0x6D)) == 0) {
        *(u8 *)(actor + 0x71) &= 0x7F;

        return;
    }
    {
        turn_index = sample_terrain_surface_height(((*(u8 *)(tile + 0x24)) << 6) | 0x20, ((*(u8 *)(tile
            + 0x25)) << 6) | 0x20, (s16) ((*(u16 *)(actor + 0x88)) - 0x20));
        if (turn_index < 0x200) {
            *(u16 *)(actor + 0x88) = turn_index;
        }
    }

    return;
    return;

}
#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void advance_actor_path_step(void *action, s32 action_id, void *entity, void *move_state) {
    void *state = move_state;
    s32 tile_mask;
    s16 move_result;
    s16 direction;
    s16 x;
    s32 y;
    s32 step_count;
    u8 new_x;
    u8 new_y;

    if (((E_80171B68_S_80171570_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (((E_80171B68_S_80171570_0 *)state)->unk_71.u <= ((E_80171B68_S_80171570_0 *)state)->unk_8A) {
        return;
    }

    if (*(u8 * *)&((SpriteFrameState *)entity)->frameTable != D_80174518) {
        ((SpriteFrameState *)entity)->frameTable = D_80174518;
        select_sprite_entry(
            entity,
            D_80174518[((g_game_work.view.camera_rotation.parts.viewAngle + ((E_80171B68_S_80171570_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((SpriteFrameState *)entity)->unk_24;
    y = ((SpriteFrameState *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((E_80171B68_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(x, y, tile_mask);

    direction = get_rounded_facing_and_rounding_flag(
        x,
        y,
        ((E_80171B68_S_80171570_3 *)((u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A))->unk_74,
        ((E_80171B68_S_80171570_3 *)((u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A))->unk_7C,
        (u8 *)action + 0x98);
    move_result = check_movement_clearance_and_height(direction, entity, state, 0x20);

    ((SpriteFrameState *)entity)->unk_24 =
        ((E_80171B68_S_80171570_3 *)((u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A))->unk_74;
    tile_mask = 0x3000;
    ((SpriteFrameState *)entity)->unk_25 =
        ((E_80171B68_S_80171570_3 *)((u8 *)state + ((E_80171B68_S_80171570_0 *)state)->unk_8A))->unk_7C;
    ((E_80171B68_S_80171570_0 *)state)->unk_8A = (u16)((E_80171B68_S_80171570_0 *)state)->unk_8A + 1;

    new_x = ((SpriteFrameState *)entity)->unk_24;
    new_y = ((SpriteFrameState *)entity)->unk_25;
    if (((E_80171B68_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, tile_mask);
    ((E_80171B68_S_80171570_0 *)state)->unk_2A = direction;

    if (move_result == 3 && !(g_dungeon_status.flags & 0x80)
        && !(((SpriteFrameState *)entity)->flags & 0x8000)) {
        set_actor_directional_animation(action, action_id, entity, state);
        ((E_80171B68_S_80171570_2 *)action)->unk_8C = 0;
    } else {
        ((E_80171B68_S_80171570_2 *)action)->unk_9A = 0x0F;
        ((E_80171B68_S_80171570_2 *)action)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((E_80171B68_S_80171570_2 *)action)->unk_96 = 0;
        return;
    }

    ((E_80171B68_S_80171570_2 *)action)->unk_96 = 8;
    step_count = ((E_80171B68_S_80171570_0 *)state)->unk_71.u;
    if (step_count > 0) {
        ((E_80171B68_S_80171570_2 *)action)->unk_96 = 8 / step_count;
    }
}
#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void set_actor_directional_animation(void *object, void *unused, SpriteFrameState *display, void *orientation) {
    s32 directionIndex;
    u8 *directionTable;

    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    directionTable = D_80174528;
    display->frameTable = directionTable;
    directionIndex = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)orientation + 0x2A) + 0x100) >> 9) & 7;
    select_sprite_entry(display, directionTable[directionIndex], 0);
}
#include "modules/dungeon_ovl_e0365c.h"

s32 begin_actor_directional_attack(void *action_state, void *action_ctx, void *sprite, EntityRec *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    u8 *direction_table;
    s32 move_heading;
    u16 flags;

    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    move_heading = place_actor_at_directional_neighbor(actor, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
        actor->facing);
    if ((check_entity_interaction_compatibility(actor, move_heading) << 0x10) == 0) {
        return 0;
    }
    flags = g_dungeon_status.flags;
    if (flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }
    if ((u32) (((0 - get_actor_height_difference(move_heading, actor)) + 0x3F) & 0xFFFF) >= 0x7FU) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
        return -1;
    }
    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_ctx, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
        ((E_80171E10_S_80171E00_3 *)action_state)->unk_9A = 0x11;
        ((E_80171E10_S_80171E00_3 *)action_state)->unk_9B = 0;
        ((E_80171E10_S_80171E00_3 *)action_state)->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        direction_table = &D_80174540;
        (*(u8 **)((u8 *)sprite + 0x2C)) = direction_table;
        select_sprite_entry(sprite, direction_table[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}
#include "modules/dungeon_ovl_e0365c.h"

void begin_actor_attack_after_status_check(void *action_state, void *action_context, void *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((E_80171FD4_S_80171FC4_1 *)action_state)->unk_9A = 0x11;
            (*(s32 *)((u8 *)action_state + 0x8C)) = 0;
            ((E_80171FD4_S_80171FC4_1 *)action_state)->unk_9B = 0;
            (*(s32 **)((u8 *)sprite + 0x2C)) = &D_80174540;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &D_80174540), 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        }
    }
}
#include "modules/dungeon_ovl_e0365c.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2C];
    u8 *field_2C;
} SpriteFieldView_80DE48EC;


s32 check_actor_ahead_height(void *action_state, void *source_pos, void *sprite, void *actor)
{
    void *output;
    s16 next_x;   /* never assigned: read only in the decision-46 dead arm below */
    s16 next_y;
    u16 result = 0;
    u16 flags;
    s32 direction;
    u16 base_x;
    u16 base_y;
    s32 delta_offset;
    s16 x;
    s16 y;
    u16 *y_delta;
    u16 *x_delta;
    u8 *x_steps;
    s16 height;
    s32 step_y;

    ((E_801720EC_S_801720EC_0 *)actor)->unk_71 &= 0x7f;
    flags = g_dungeon_status.flags;
    if (flags & 0x2000) {
        return -1;
    }

    if (!(((E_801720EC_S_801720EC_0 *)actor)->unk_46 & 0x8000)) {
        if (flags & 8) {
            return -1;
        }
    }

    if ((s16)try_claim_dungeon_action_slot(actor) != 0) {
        return -1;
    }

    output = (u8 *)actor - 0x20;
    apply_camera_offset_and_select_target((s32)output, source_pos, 8, 0x300);
    if ((s16)try_claim_dungeon_action_slot(actor) != 0) {
        return -1;
    }

    base_x = ((E_801720EC_S_801720EC_1 *)sprite)->unk_24;
    base_y = ((E_801720EC_S_801720EC_1 *)sprite)->unk_25;
    x = base_x;
    y = base_y;
    direction = (((E_801720EC_S_801720EC_0 *)actor)->unk_2A.s >> 9) & 7;
    if ((s16)check_layer_offset_height(x << 6, y << 6, ((E_801720EC_S_801720EC_0 *)actor)->unk_88.s, direction << 9) != 0) {
return_tail:
        return result;
    }

    x_steps = (u8 *)dir_step_x;
    x_delta = (u16 *)(x_steps + (direction << 1));
    delta_offset = direction << 1;
    y_delta = (u16 *)((u8 *)dir_step_y + delta_offset);
    {
        s32 step_x;
        step_x = *x_delta;
        step_y = *y_delta;
        if (find_eligible_entry_at_coordinates(actor, (base_x + step_x) & 0xffff,
                          (base_y + step_y) & 0xffff) != 0) {
            goto return_tail;
        }
    }

    if ((s16)increment_bounded_event_counter() == 0) {
        return result;
    }

    height = sample_terrain_surface_height((((x + (s16)*x_delta) << 6) + 0x20) & 0xffe0,
                           (((y + (s16)*y_delta) << 6) + 0x20) & 0xffe0,
                           (s16)(((E_801720EC_S_801720EC_0 *)actor)->unk_88.u - 0x20));
    if (height >= 0x201) {
        return result;
    }
    if ((s16)(height - ((E_801720EC_S_801720EC_0 *)actor)->unk_88.u) < -0x3f) {
        return result;
    }
    ((E_801720EC_S_801720EC_2 *)action_state)->unk_9B = 0;
    ((E_801720EC_S_801720EC_2 *)action_state)->unk_8C = 0;
    ((E_801720EC_S_801720EC_2 *)action_state)->unk_9A = 0x17;
    (((SpriteFieldView_80DE48EC *)sprite)->field_2C) = D_80174558;
    select_sprite_entry(sprite,
                  D_80174558[((g_game_work.view.camera_rotation.parts.viewAngle + ((E_801720EC_S_801720EC_0 *)actor)->unk_2A.u + 0x100) >> 9) & 7],
                  0);
    advance_status_timers(actor);
    /* Decision 46 (owner 2026-10-13): post-combine dead arm. result is never reassigned, so combine folds this test
     * only after flow has counted the arm; scheduling, allocation and reload see it (x_delta's second set, the spilled
     * next_x/next_y slots retail's frame reserves) and jump2 deletes it - no code. The arm's BODY is a reconstruction:
     * the bytes fix its shape, not its content. */
    if (result != 0) {
        x_delta += next_x;
        try_claim_dungeon_action_slot(next_y + *x_delta);
    }
    {
        s32 update_flags = 0x300;
        step_y = 8;
        ((E_801720EC_S_801720EC_0 *)actor)->unk_6D--;
        select_nearby_target_and_initialize_slot((s32)output, source_pos, step_y, update_flags);
    }
    return 1;
}
#include "modules/dungeon_ovl_e0365c.h"

void start_actor_directional_animation(void *actor_state, s32 action_param, void *sprite, EntityRec *actor) {
    actor->unk_71 = actor->unk_71 & 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_param, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            ((E_8017236C_S_8017236C_1 *)actor_state)->unk_9A = 0x18;
            ((E_8017236C_S_8017236C_1 *)actor_state)->unk_8C = 0;
            ((E_8017236C_S_8017236C_1 *)actor_state)->unk_9B = 0;
            (*(s32 * *)((u8 *)sprite + 0x2C)) = &D_80174558;
            select_sprite_entry(sprite,
                          *((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                            + (u8 *)&D_80174558),
                          0);
            advance_status_timers(actor);
            actor->unk_6D = ((u8)actor->unk_6D) - 1;
        }
    }
}
#include "modules/dungeon_ovl_e0365c.h"

void move_actor_to_tile_and_check_trap(E_8017246C_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_actor_movement_to_tile(state,motion,sprite,actor)!=0) {
  reduce_actor_food_meter(actor,4);
  advance_status_timers(actor);
  if((check_actor_floor_trap(sprite,actor)<<16)>0) {
   state->handler=update_actor_behavior_facing_and_animation_2;
   state->timer=0;
  }
 }
}
#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void update_actor_hop_to_tile(void *anim, EntityRec *motion, void *actor, EntityRec *actor_state)
{
    s32 facing_aux;
    s32 hop_frames;
    s16 next_hop_frames;
    u16 move_frames;
    s32 phase;
    s32 actor_flags;
    s32 tile_origin_y;

    phase = ((E_801724E8_S_801724E8_0 *)anim)->unk_9B;
    switch (phase) {
    case 0:
        if (!((((SpriteFrameState *)actor)->unk_04 == 2 &&
               (((SpriteFrameState *)actor)->flags & 0x1000)) ||
              (((SpriteFrameState *)actor)->flags & 0xE000))) {
            break;
        }
        ((E_801724E8_S_801724E8_0 *)anim)->unk_98 |= 8;
        (*(u32 *)&actor_state->flags1C) &= 0xF7FFFFFF;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s = 5;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_A0 = 0;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_9B++;
                        /* fall through */
    case 1:
        hop_frames = ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_90 -= ((E_801724E8_S_801724E8_0 *)anim)->unk_A0;
        if (hop_frames != 0) {
            motion->unk_0C =
                (((((SpriteFrameState *)actor)->unk_24 << 6) - ({ motion->x.w.i - 0x20; })) << 16) / hop_frames;
            motion->unk_10 =
                (((((SpriteFrameState *)actor)->unk_25 << 6) - (tile_origin_y = motion->y.w.i - 0x20)) << 16) /
                ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s;
            ((E_801724E8_S_801724E8_0 *)anim)->unk_A0 =
                (-func_800644B8(((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s * 0x199)) << 9;
        }

        ((E_801724E8_S_801724E8_0 *)anim)->unk_90 += ((E_801724E8_S_801724E8_0 *)anim)->unk_A0;
        next_hop_frames = ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.u - 1;
        ((E_801724E8_S_801724E8_0 *)anim)->unk_9E.s = next_hop_frames;
        if (next_hop_frames < 0) {
            ((E_801724E8_S_801724E8_0 *)anim)->unk_90 = 0;
            ((E_801724E8_S_801724E8_0 *)anim)->unk_98 &= 0xFFF7;
            (*(u32 *)&actor_state->flags1C) |= 0x08000000;
            ((E_801724E8_S_801724E8_0 *)anim)->unk_9B++;
        }
                        /* fall through */
    case 2:
        if (((u32)actor_state->flags1C) & 0x08000000) {
            ((E_801724E8_S_801724E8_0 *)anim)->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)actor)->unk_24, ((SpriteFrameState *)actor)->unk_25);
            ((SpriteFrameState *)actor)->frameTable = D_80174520;
            select_sprite_entry(
                actor,
                D_80174520[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
                0);
            ((E_801724E8_S_801724E8_0 *)anim)->unk_9B++;
        }
        break;
    default:
        break;
    }

    move_frames = ((E_801724E8_S_801724E8_0 *)anim)->unk_96 - 1;
    ((E_801724E8_S_801724E8_0 *)anim)->unk_96 = move_frames;
    if ((s16)move_frames <= 0) {
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)actor)->unk_24, ((SpriteFrameState *)actor)->unk_25);
        reduce_actor_food_meter(actor_state, 4);
        advance_status_timers(actor_state);

        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count--;
        }

        actor_flags = actor_state->flags1C;
        if (actor_flags & 0x2000) {
            if (actor_state->unk_46 & 0x8000) {
                actor_state->unk_46 &= 0x7FFF;
            }
        } else {
            if (!(actor_flags & 0x410)) {
                if (actor_flags & 0x20000) {
                    actor_state->facing = get_rounded_facing_and_rounding_flag(
                        ((SpriteFrameState *)actor)->unk_24, ((SpriteFrameState *)actor)->unk_25,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, &facing_aux);
                }
            }
        }

        if ((check_actor_floor_trap(actor, actor_state) << 16) > 0) {
            ((E_801724E8_S_801724E8_0 *)anim)->unk_8C = update_actor_behavior_facing_and_animation_2;
            on_actor_status_updated(actor_state);
        }
    }
}
#include "modules/dungeon_ovl_e0365c.h"

void update_linked_actor_motion_and_trap(E_80172850_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_linked_actor_motion(state,motion,sprite,actor)!=0 &&
    (check_actor_floor_trap(sprite,actor)<<16)>0) state->handler=update_actor_behavior_facing_and_animation_2;
}
#include "modules/dungeon_ovl_e0365c.h"

void resolve_actor_attack_damage(void *obj, EntityRec *record, void *entity, void *actor) {
    s32 state;

    state = ((E_801728B4_S_801728B4_0 *)obj)->unk_9B;
    switch (state) {
    case 0:
        if (((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0x8000) {
            ((E_801728B4_S_801728B4_0 *)obj)->unk_9B = 2U;
            ((E_801728B4_S_801728B4_1 *)entity)->unk_14 =
                (u16)(((E_801728B4_S_801728B4_1 *)entity)->unk_14 | 0x6000);
            resolve_attack_damage_and_effects(actor, entity, ((E_801728B4_S_801728B4_2 *)actor)->unk_2A, 1);
            return;
        }
        record->flags14 = 0;
        record->unk_10 = 0;
        record->unk_0C = 0;
        ((E_801728B4_S_801728B4_0 *)obj)->unk_9B =
            (u8)(((E_801728B4_S_801728B4_0 *)obj)->unk_9B + 1);
        return;

    case 1:
        if ((((E_801728B4_S_801728B4_1 *)entity)->unk_04 == 7) &&
            (((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0x1000)) {
            play_sound_if_enabled(0x808);
        }
        if (((((E_801728B4_S_801728B4_1 *)entity)->unk_04 == 9) &&
             (((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0x1000)) ||
            (((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0xE000)) {
            resolve_attack_damage_and_effects(actor, entity, ((E_801728B4_S_801728B4_2 *)actor)->unk_2A, 1);
            ((E_801728B4_S_801728B4_0 *)obj)->unk_9B =
                (u8)(((E_801728B4_S_801728B4_0 *)obj)->unk_9B + 1);
        } else {
            return;
        }
                        /* fall through */

    case 2:
        if (!(((E_801728B4_S_801728B4_1 *)entity)->unk_14 & 0xE000)) {
            return;
        }
        reduce_actor_food_meter(actor, 0x100);
        ((E_801728B4_S_801728B4_0 *)obj)->unk_8C = update_actor_behavior_facing_and_animation_2;
        g_dungeon_status.active_actor = 0;
        ((E_801728B4_S_801728B4_2 *)actor)->unk_46 =
            (u16)((*(u16 *)((u8 *)actor + 0x46)) & 0x7FFF);
        advance_status_timers(actor);
        break;

    default:
        break;
    }
}
#include "modules/dungeon_ovl_e0365c.h"

void update_actor_spell_action(void *arg0, E_80172A58_S_80172A58_6 *arg1, E_80172A58_S_80172A58_5 *arg2, void *arg3) {
    s32 result;
    s32 next_ticks;
    s16 use_player_target;
    s8 unused_result_byte;
    s8 unused_state_byte;
    u16 remaining_ticks;
    u8 *action_entry;
    u8 phase;
    E_80172A58_S_80172A58_4 *target_position;
    void *target_link;

    phase = ((E_80172A58_S_80172A58_0 *)arg0)->unk_9B;
    use_player_target = 0;
    switch (phase) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if (((E_80172A58_S_80172A58_1 *)arg3)->unk_1C & 0x2000) {
            switch (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x3FFF) {
            case 7: use_player_target=1;
            case 3: action_entry=(u8 *)arg3+0xE; break;
            case 6: use_player_target=1;
            case 2: action_entry=(u8 *)arg3+0xB; break;
            case 5: use_player_target=1;
            case 1: action_entry=(u8 *)arg3+8; break;
            default: action_entry=0; break;
            }
        } else {
            switch (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x3FFF) {
            case 3: action_entry=(u8 *)arg3+0xE; break;
            case 2: action_entry=(u8 *)arg3+0xB; break;
            case 1: action_entry=(u8 *)arg3+8; break;
            default: action_entry=0; break;
            }
        }
        if (*action_entry != 0) {
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_98 = (u16) (((E_80172A58_S_80172A58_0 *)arg0)->unk_98 & 0xFF7F);
            if (use_player_target != 0) {
                target_link = D_800814A8;
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_60 = target_link;
                    target_position = ((E_80172A58_S_80172A58_3_pre *)target_link)[-1].unk_00;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = (s8) target_position->unk_24;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = (s8) target_position->unk_25;
            } else if (((E_80172A58_S_80172A58_2 *)(((*action_entry * 0x14) + D_8006DE24)))->unk_12 == 2) {
                target_link = ((E_80172A58_S_80172A58_1 *)arg3)->unk_60;
                if (target_link != NULL) {
                    target_position = ((E_80172A58_S_80172A58_3_pre *)target_link)[-1].unk_00;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = (s8) target_position->unk_24;
                    ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = (s8) target_position->unk_25;
                }
            } else {
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_60 = scan_monster_along_heading(arg3, arg2->unk_24, arg2->unk_25, ((E_80172A58_S_80172A58_1 *)arg3)->unk_2A, 0x10);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = abs(((E_80172A58_S_80172A58_1 *)arg3)->unk_72);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = abs(((E_80172A58_S_80172A58_1 *)arg3)->unk_73);
            }
            if (create_actor_spell_effect(arg3, action_entry, use_player_target, arg0 + 0x98) != 0) {
                create_actor_linked_effect(arg3);
                ((E_80172A58_S_80172A58_0 *)arg0)->unk_9B = (u8) (((E_80172A58_S_80172A58_0 *)arg0)->unk_9B + 1);
                return;
            }
            return;
        }
        arg1->unk_14 = 0;
        arg1->unk_10 = 0;
        arg1->unk_0C = 0;
        set_record_integer_tile_center(arg1, arg2->unk_24, arg2->unk_25);
        g_dungeon_status.active_actor = 0;
        ((E_80172A58_S_80172A58_7 *)D_800814A8)->unk_A6 = (u16) (((E_80172A58_S_80172A58_7 *)D_800814A8)->unk_A6 - 1);
        advance_status_timers(arg3);
        ((E_80172A58_S_80172A58_1 *)arg3)->unk_6D = (u8) (((E_80172A58_S_80172A58_1 *)arg3)->unk_6D - 1);
        ((E_80172A58_S_80172A58_0 *)arg0)->unk_8C = update_actor_behavior_facing_and_animation_2;
        ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = 0;
        ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = 0;
        ((E_80172A58_S_80172A58_1 *)arg3)->unk_46 = (u16) (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x7FFF);
        return;
    case 1:                                         /* switch 1 */
        if (get_cd_command_queue_depth() != 0) {
            arg2->unk_14 = (u16) (arg2->unk_14 | 0x800);
            return;
        }
        arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
        ((E_80172A58_S_80172A58_0 *)arg0)->unk_9B = (u8) (((E_80172A58_S_80172A58_0 *)arg0)->unk_9B + 1);
    case 2:                                         /* switch 1 */
        if (((arg2->unk_04 == 3) && (arg2->unk_14 & 0x1000)) || (arg2->unk_14 & 0xE000)) {
            arg2->unk_14 = (u16) (arg2->unk_14 | 0x800);
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 = 1U;
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_98 = (u16) (((E_80172A58_S_80172A58_0 *)arg0)->unk_98 | 0x80);
        }
        remaining_ticks = ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 - 1;
        ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 = remaining_ticks;
        if ((remaining_ticks << 0x10) <= 0) {
            ((E_80172A58_S_80172A58_0 *)arg0)->unk_96 = 0U;
            arg2->unk_14 = (u16) (arg2->unk_14 & 0xF7FF);
        }
        if (arg2->unk_14 & 0xE000) {
            arg1->unk_14 = 0;
            arg1->unk_10 = 0;
            arg1->unk_0C = 0;
            set_record_integer_tile_center(arg1, arg2->unk_24, arg2->unk_25);
            if (arg2->unk_2C != D_80174520) {
                arg2->unk_2C = D_80174520;
                select_sprite_entry(arg2, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((E_80172A58_S_80172A58_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) + D_80174520), 0);
            }
            if (g_dungeon_status.active_actor == 0) {
                g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (g_dungeon_status.activity_counts.parts.pending_action_count - 1);
                ((E_80172A58_S_80172A58_0 *)arg0)->unk_8C = update_actor_behavior_facing_and_animation_2;
                advance_status_timers(arg3);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_73 = 0;
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_72 = 0;
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_6D = (u8) (((E_80172A58_S_80172A58_1 *)arg3)->unk_6D - 1);
                ((E_80172A58_S_80172A58_1 *)arg3)->unk_46 = (u16) (((E_80172A58_S_80172A58_1 *)arg3)->unk_46 & 0x7FFF);
                play_sound_if_enabled(0xB4);
            }
        }
        break;
    }
}
#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void dampen_actor_movement_to_tile(E_80172ED0_S_80172ED0_0 *action, EntityRec *motion, SpriteFrameState *tile_state, void *entity)
{
    s16 timer;
    s32 tracked_entity;

    switch (action->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->unk_0C =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                     ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 19;
        motion->unk_10 =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                     ((((EntityRec *)entity)->unk_6A >> 8) & 0xE)) << 19;
        action->unk_9B++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, tile_state, &D_80174550);
            return;
        }
        if (tile_state->flags & 0x8000) {
            action->unk_9B = 2;
            return;
        }
        if (((EntityRec *)entity)->flags1C & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
                        /* fall through */

    case 1:
    {
        s32 velocity_x = motion->unk_0C;
        motion->unk_0C = velocity_x - velocity_x / 4;
    }
        {
            s32 velocity_y = motion->unk_10;
            motion->unk_10 = velocity_y - velocity_y / 4;
        }
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (tile_state->flags & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 != 0) {
            action->unk_96.s = 8;
            action->unk_9B++;
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        begin_actor_display_action(action, motion, tile_state, &D_80174550);
        return;

    case 2:
        timer = action->unk_96.s;
        if (timer > 0) {
            {
                s32 target_x = tile_state->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;
                motion->unk_0C =
                    ((target_x - current_x) << 16) / timer;
            }
            {
                s32 target_y = tile_state->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;
                motion->unk_10 =
                    ((target_y - current_y) << 16) / action->unk_96.s;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        if ((tile_state->flags & 0x6000) &&
            ((EntityRec *)entity)->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            begin_actor_display_action(action, motion, tile_state, &D_80174550);
            return;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, tile_state->unk_24, tile_state->unk_25);

            tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
            if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
                g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
            }
            action->unk_8C = update_actor_behavior_facing_and_animation_2;
            return;
        }

    default:
        return;
    }
}
#include "modules/dungeon_ovl_e0365c.h"

void func_801731BC(void *state,void *position,void *render_state,void *entity) {
    update_actor_defeat_removal(state,position,render_state,entity);
}
#include "modules/dungeon_ovl_e0365c.h"

void func_801731DC(void *state,void *motion,void *sprite,void *actor) {
 update_actor_hop_and_shrink(state,motion,sprite,actor);
}
#include "modules/dungeon_ovl_e0365c.h"

void advance_entity_motion_fade_and_removal(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    advance_actor_removal(state, action, source, target);
}

#include "modules/dungeon_ovl_e0365c.h"

void finish_actor_hop_and_grow_then_resume_facing_animation(E_8017321C_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_actor_hop_and_grow(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
#include "modules/dungeon_ovl_e0365c.h"

void handle_actor_pending_action(void *action, void *context, void *sprite, EntityRec *entity)
{
    void *saved_context;
    u8 state;

    saved_context = context;
#define context saved_context
#define sprite sprite

    state = ((E_80173254_S_80173254_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) {
            u8 *direction_anims;

            direction_anims = D_80174538;
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            ((E_80173254_S_80173254_0 *)action)->unk_9B++;
        }
        return;
    case 1:
        if ((get_entity_effect_value(entity, 1) << 16) != 0) {
            s32 entity_flags;

            if (g_dungeon_status.flags & 0x1000) {
                return;
            }

            if ((entity->unk_64 != 0) &&
                (begin_ready_actor_directional_action(action, context, sprite, 0) != 0)) {
                return;
            }

            if (entity->tileY == 0) {
                if (g_dungeon_status.flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(action, context, sprite, entity);
                return;
            }

            if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
                return;
            }

            entity_flags = entity->flags1C;
            if (entity_flags & 0x100) {
                begin_pushed_actor_move(action, context, sprite, entity);
                return;
            }

            if (entity_flags & 0x80000) {
                begin_actor_move_to_target_facing(action, context, sprite, entity);
                update_actor_landing_and_trap(action, context, sprite, entity);
                return;
            }

            if (entity->unk_6D == 0) {
                return;
            }

            if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
                if ((check_entity_relation(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(entity);
            on_actor_status_updated(entity);

            if ((get_entity_effect_value(entity, 1) << 16) != 0) {
                TileObject *origin;
                s8 coordinate;

                origin = &D_80082E80;
                coordinate = ((Rec_D_80082E80 *)sprite)->unk_26.as_s8;
                if ((((coordinate == origin->room_index) &&
                            (coordinate >= 0)) ||
                     (get_tile_chebyshev_distance(origin, sprite) < 2)) &&
                    ((generate_random_value() & 7) == 0)) {
                    clear_slots_of_type(entity, 1);
                }
            }

            if ((get_entity_effect_value(entity, 1) << 16) != 0) {
                return;
            }
        }

        {
            u8 *direction_anims;

            direction_anims = D_80174520;
            (*(void * *)((u8 *)sprite + 0x2C)) = direction_anims;
            select_sprite_entry(sprite,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C &= ~0x200;
            ((E_80173254_S_80173254_0 *)action)->unk_8C = update_actor_behavior_facing_and_animation_2;
        }
    }
}
#include "modules/dungeon_ovl_e0365c.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2C];
    void *field_2C;
} SpriteFieldView_80DE5D7C;


void handle_actor_action_effects(void *controller, void *context, void *sprite, EntityRec *actor)
{
    u8 state;
    u8 *effect;
    s32 direction;

    state = ((E_8017357C_S_8017357C_0 *)controller)->unk_9B;
    switch (state) {
    case 0:
    {
        u8 *initial_effect;

        if ((((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }

        initial_effect = D_80174538;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        (((SpriteFieldView_80DE5D7C *)sprite)->field_2C) = initial_effect;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        select_sprite_entry(sprite, initial_effect[direction & 7], 0);
        ((E_8017357C_S_8017357C_0 *)controller)->unk_9B++;
        return;
    }
    case 1:
        if (actor->tileY == 0) {
            if (g_dungeon_status.flags & 0x1000) {
                return;
            }

            if ((actor->unk_64 != 0) &&
                begin_ready_actor_directional_action(controller, context, sprite, 0)) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                return;
            }

            {
                void *call_controller = controller;

                if (((u32)actor->flags1C) & 0x100) {
                    do {
                        begin_pushed_actor_move(call_controller, context, sprite, actor);
                    } while (0);
                    return;
                }

                if (((u32)actor->flags1C) & 0x80000) {
                    begin_actor_move_to_target_facing(call_controller, context, sprite, actor);
                    update_actor_landing_and_trap(controller, context, sprite, actor);
                    return;
                }
            }

            if (actor->unk_6D == 0) {
                return;
            }

            if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
                EntityRec *owner;

                owner = D_800814A8;
                if ((s16)check_entity_relation(actor, (u8 *)owner->unk_58 + 0x20) != 0) {
                    return;
                }
            }

            update_actor_status_and_food(actor);
            on_actor_status_updated(actor);
            if (actor->tileY == 0) {
                return;
            }
        }

        effect = D_80174520;
        (((SpriteFieldView_80DE5D7C *)sprite)->field_2C) = effect;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9;
        select_sprite_entry(sprite, effect[direction & 7], 0);
        ((E_8017357C_S_8017357C_0 *)controller)->unk_8C = update_actor_behavior_facing_and_animation_2;
        actor->flags1C &= ~0x200;
    }
}
#include "modules/dungeon_ovl_e0365c.h"

void update_actor_landing_and_trap(E_801737DC_ActionState *state,void *motion,E_801737DC_RenderState *sprite,E_801737DC_RenderActor *actor) {
 if(update_actor_transform_from_parent(state,motion,sprite,actor)!=0) {
  if((check_actor_floor_trap(sprite,actor)<<16)>0) state->handler=update_actor_behavior_facing_and_animation_2;
 } else if(sprite->frames==D_80174538 && !(actor->flags&0x208)) {
  sprite->frames=D_80174518;
  select_sprite_entry(sprite,D_80174518[((g_game_work.view.camera_rotation.parts.viewAngle+actor->facing+0x100)>>9)&7],0);
 }
}
#include "modules/dungeon_ovl_e0365c.h"

void update_thrown_actor_and_trap(E_801738A4_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_thrown_actor_travel(state,motion,sprite,actor)!=0 &&
    (check_actor_floor_trap(sprite,actor)<<16)>0) state->handler=update_actor_behavior_facing_and_animation_2;
}
#include "modules/dungeon_ovl_e0365c.h"

void finish_actor_terrain_interpolation_then_resume_facing_animation(E_80173908_ActionState *state,void *motion,void *sprite,void *actor) {
 if(interpolate_actor_to_terrain_tile(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
#include "modules/dungeon_ovl_e0365c.h"

void finish_spinning_actor_fall_then_resume_facing_animation(E_80173940_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_spinning_actor_fall(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
#include "modules/dungeon_ovl_e0365c.h"

void finish_actor_fade_in_then_resume_facing_animation(E_80173978_ActionState *state,void *motion,void *sprite,void *actor) {
 if(update_actor_fade_in(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
#include "modules/dungeon_ovl_e0365c.h"

void finish_actor_floor_trap_then_resume_facing_animation(E_801739B0_ActionState *state,void *motion,void *sprite,void *actor) {
 if(resolve_actor_floor_trap_once(state,motion,sprite,actor) > 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
#include "modules/dungeon_ovl_e0365c.h"

void finish_actor_action_flag_propagation_then_resume_facing_animation(E_801739E8_ActionState *state,void *motion,void *sprite,void *actor) {
 if(propagate_actor_action_flag(state,motion,sprite,actor) != 0) state->handler=update_actor_behavior_facing_and_animation_2;
}
#include "modules/dungeon_ovl_e0365c.h"

void advance_actor_state_with_child(void *actor, void *context, void *entity, void *creature)
{
    switch (((Rec_func_80173204_arg0 *)actor)->unk_9B) {
    case 0:
    {
        u16 entity_flags = ((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v;

        if (entity_flags & 0x8000) {
            ((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v = entity_flags | 0x6000;
            ((Rec_func_80173204_arg0 *)actor)->unk_9B = 2;
            return;
        }
        ((Rec_func_80173204_arg0 *)actor)->unk_9B = 1;
    }
                        /* fall through */
    case 1:
        if (((((Rec_D_80082E80 *)entity)->unk_04.as_s8 == 8) &&
             (((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x1000)) ||
            (((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000)) {
            func_80174460(creature);
            play_sound_if_enabled(0x80C);
            create_four_directional_effects(actor, context, entity);
            ((Rec_func_80173204_arg0 *)actor)->unk_A4 = create_directional_effect_object(actor, context, entity);
            ((Rec_func_80173204_arg0 *)actor)->unk_9B++;
        }
        return;

    case 2:
    {
        s16 object_value;
        s32 value_total;
        s32 value_bonus;
        u32 offset_index;
        u32 direction_bits;
        u8 *x_offsets;
        u32 object_flag;
        s32 global_flags;
        s16 spawn_height;
        u16 creature_height;
        s32 world_x;
        s16 *x_offset;
        s16 *y_offset;
        void *shadow;
        void *object;

        if (!(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0xE000)) {
            return;
        }

        shadow = ((Rec_func_80173204_arg0 *)actor)->unk_A4;
        ((E_80173A20_S_80173A20_2 *)shadow)->unk_1E |= 0x8000;

        global_flags = object_flag_block.flags;
        direction_bits = ((E_80173A20_S_80173A20_3 *)creature)->unk_2A >> 8;
        creature_height = ((E_80173A20_S_80173A20_3 *)creature)->unk_88.s;
        object_flag_block.flags = global_flags | 0x8000;

        x_offsets = (u8 *)((s8 *)dir_step_x);
        offset_index = direction_bits & 0xE;
        x_offset = (s16 *)(x_offsets + offset_index);
        world_x = ((((Rec_D_80082E80 *)entity)->unk_24 + *x_offset) << 6) & 0xFFC0;
        y_offset = (s16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
        spawn_height = sample_terrain_surface_height(world_x,
            ((((Rec_D_80082E80 *)entity)->unk_25 + *y_offset) << 6) & 0xFFC0,
            (s16)(creature_height - 0x20));

        if (((E_80173A20_S_80173A20_3 *)creature)->unk_88.u < spawn_height) {
            spawn_height = ((E_80173A20_S_80173A20_3 *)creature)->unk_88.s;
        }

        object_flag = ((E_80173A20_S_80173A20_3 *)creature)->unk_1C & 0x2000;
        object = create_actor_with_tile_flags(
            object_flag != 0,
            (s16)(((Rec_D_80082E80 *)entity)->unk_24 + (u16)*x_offset),
            (s16)(((Rec_D_80082E80 *)entity)->unk_25 + (u16)*y_offset),
            spawn_height);
        func_80042640(object, 0x36);

        value_bonus = (((E_80173A20_S_80173A20_3 *)creature)->unk_11 * 2) + (generate_random_value() & 3);
        value_total = ((E_80173A20_S_80173A20_4 *)object)->unk_29 + value_bonus;
        object_value = value_total;
        if (value_total >= 0x100) {
            object_value = 0xFF;
        }
        ((E_80173A20_S_80173A20_4 *)object)->unk_28 = object_value;
        ((E_80173A20_S_80173A20_4 *)object)->unk_29 = object_value;

        reduce_actor_food_meter(creature, 0x400);
        set_record_integer_tile_center(context, ((Rec_D_80082E80 *)entity)->unk_24,
                      ((Rec_D_80082E80 *)entity)->unk_25);
        ((Rec_func_80173204_arg0 *)actor)->unk_8C.as_pv = update_actor_behavior_facing_and_animation_2;
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)creature + 0x46)) &= 0x7FFF;
        return;
    }
    }
}
#include "modules/dungeon_ovl_e0365c.h"

void advance_actor_state_when_allowed(void *state_ctx, s32 entity_id, void *action, void *entity)
{
    s32 state;
    u16 flags;

    state = ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_9B;
    switch (state) {
    case 0:
        flags = ((E_80173CE0_S_80173CE0_1 *)action)->unk_14;
        if (flags & 0x8000) {
            ((E_80173CE0_S_80173CE0_1 *)action)->unk_14 = flags | 0x6000;
            ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_9B = 2;
            return;
        }
        ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_9B = 1;

    case 1:
        if (!((((E_80173CE0_S_80173CE0_1 *)action)->unk_04 == 8) &&
              (((E_80173CE0_S_80173CE0_1 *)action)->unk_14 & 0x1000)) &&
            !(((E_80173CE0_S_80173CE0_1 *)action)->unk_14 & 0xE000)) {
            return;
        }
        display_entity_action_message(entity);
        play_sound_if_enabled(0x80C);
        create_four_directional_effects(state_ctx, entity_id, action);
        ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_9B++;
        return;

    case 2:
        if (((E_80173CE0_S_80173CE0_1 *)action)->unk_14 & 0xE000) {
            reduce_actor_food_meter(entity, 0x400);
            set_record_integer_tile_center(entity_id, ((E_80173CE0_S_80173CE0_1 *)action)->unk_24, ((E_80173CE0_S_80173CE0_1 *)action)->unk_25);
            ((E_80173CE0_S_80173CE0_0 *)state_ctx)->unk_8C = update_actor_behavior_facing_and_animation_2;
            g_dungeon_status.active_actor = 0;
            (*(u16 *)((u8 *)entity + 0x46)) &= 0x7FFF;
        }

        return;
    }
}
#include "modules/dungeon_ovl_e0365c.h"

s32 select_actor_relation_state(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        update_actor_targeting_and_movement(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((E_80173E48_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_food(entity);
        result = 0;
        return result;
    case 2:
        update_actor_targeting_and_movement(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((E_80173E48_S_80172628_0 *)entity)->unk_71 = (u8) (((E_80173E48_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((E_80173E48_S_80172628_0 *)entity)->unk_71 = (u8) (((E_80173E48_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((E_80173E48_S_80172628_0 *)entity)->unk_46 = (u16) (((E_80173E48_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}
#include "modules/dungeon_ovl_e0365c.h"

void dampen_actor_motion(void *state_data, s32 *motion, E_80173F8C_Func80DE678C_Obj *object) {
    func_800478B8(object);
    if (object->flags & 0x6000) {
        *(u16 *)((u8 *)state_data - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }

    object->field1e += 0x200;
    object->field1c = object->field1e;
    motion[3] /= 2;
    motion[4] /= 2;
    motion[5] -= 20000;
    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];
}
#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void create_four_directional_effects(void *owner_arg, void *motion_arg, void *origin_arg) {
    u16 offsets[3];
    s32 effect_index;
    E_80174084_S_80DE6884_5 *owner;
    s32 *effect_data;
    E_80174084_S_80DE6884_0 *origin;
    void *render_config;
    SpriteFrameState *render_data;
    E_80174084_S_80DE6884_4 *motion;
    E_80174084_S_80DE6884_1 *effect;

    origin = origin_arg;
    offsets[2] = 0;
    offsets[1] = 0;
    offsets[0] = 0;
    owner = owner_arg;
    resolve_record_orientation_or_fallback(origin->unk_08, origin, (s16 *)offsets, 0);
    effect_index = 0;
    effect_data = (s32 *)((u32)dampen_actor_motion);
    do {
        effect = func_8003FC64(0x212);
        if (effect != 0) {
            render_config = &D_800DEA68;
            render_data = effect->unk_0C;
            effect->unk_10 = effect_data;
            render_data->color.c.b = 0x60;
            render_data->color.c.g = 0x60;
            render_data->color.c.r = 0x60;
            render_data->flags = set_flags(render_data->flags, 0xC);
            render_data->tpage_abr = set_flags(render_data->tpage_abr, 0x20);
            func_8003DB94(render_data, render_config, 0);
            func_800478B8(render_data);
            render_data->angle_z = rand() % 0x1000;
            render_data->scale_y = 0x1000;
            render_data->scale_x = 0x1000;
            register_node(effect, project_sprite_chain);
            motion = effect->unk_08;
            *(E_80174084_S_80DE6884_3 *)motion = *(E_80174084_S_80DE6884_3 *)motion_arg;
            motion->unk_00.at02.v = offset_coord(motion->unk_00.at02.v, offsets[0]);
            motion->unk_04.at02.v = offset_coord(motion->unk_04.at02.v, offsets[1]);
            motion->unk_08.at02.v = offset_coord(motion->unk_08.at02.v, offsets[2]);
            motion->unk_0C = (s32)((func_80064584(owner->unk_2A) >> 4) << 0xB);
            motion->unk_10 = (s32)((func_800644B8(owner->unk_2A) >> 4) << 0xB);
            motion->unk_14 = 0x9C40;
        }
        effect_index += 1;
    } while (effect_index < 4);
}

/* MECHANISM: the 24-byte motion block is one aggregate copy from motion_arg (movstrsi leaves its fourth
   word in a1, which the one-argument trig call never reads); the small u16 helpers keep the loop at 88
   real insns so loop.c does not hoist the 0x60 colour constant into a callee-saved register. */
#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void advance_effect_record_counters(u16 *counter, s32 unused, SpriteFrameState *record) {
    u16 step;
    u16 field_value;

    step = *counter + 1;
    *counter = step;
    if ((s16) step < 9) {
        field_value = record->scale_y + 0x100;
        record->scale_y = field_value;
        record->scale_x = field_value;
    }
    func_800478B8(record);
}
#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

s32 create_directional_effect_object(E_801742AC_S_80DE6AAC_2 *source, void *initial_position, E_801742AC_S_80DE6AAC_4 *tile_origin) {
    SpriteFrameState *sprite;
    E_801742AC_S_80DE6AAC_5 *position;
    E_801742AC_S_80DE6AAC_1 *effect_state;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect_state = effect + 0x20;
        ((E_801742AC_S_80DE6AAC_0 *)effect)->unk_10 = advance_effect_record_counters;
        ((E_801742AC_S_80DE6AAC_0 *)effect)->unk_20 = 0;
        effect_state->unk_02 = (s16)(((u16)source->unk_2A >> 9) & 7);
        sprite = ((E_801742AC_S_80DE6AAC_0 *)effect)->unk_0C;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        sprite->clut = 0x7E40;
        sprite->flags = (u16)(sprite->flags | 0x100);
        func_8003DB94(sprite, &D_800DEEC0, 0);
        func_800478B8(sprite);
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;
        register_node(effect, project_sprite_chain);
        position = ((E_801742AC_S_80DE6AAC_0 *)effect)->unk_08;
        *(E_801742AC_Copy24 *)position = *(E_801742AC_Copy24 *)initial_position;
        {
            s32 world_y;
            s32 direction_offset;
            s32 height_limit;
            s32 world_x;

            direction_offset = effect_state->unk_02 * 2;
            world_x = (s32)((tile_origin->unk_24 + *(u16 *)((u8 *)dir_step_x + direction_offset)) << 0x10) >> 0xA;
            world_y = (s32)((tile_origin->unk_25 + *(u16 *)((u8 *)dir_step_y + direction_offset)) << 0x10) >> 0xA;
            position->unk_02 = (s16)(world_x + 0x20);
            position->unk_06 = (s16)(world_y + 0x20);
            height_limit = sample_terrain_surface_height(world_x & 0xFFC0, world_y & 0xFFC0, (s16)(source->unk_88 - 0x20)) << 0x10;
            if (height_limit < position->unk_08) {
                position->unk_08 = height_limit;
            }
        }
        return (s32)effect;
    }
    return 0;
}

/* MECHANISM: A typed 24-byte assignment restores the packed lw/sw copy and natural seven-register
   frame. An unsigned color byte plus a post-copy schedule seam fixes the immediate and held table-base
   order. The moved shape selects 2.7.2-cdk-G0. */
#include "modules/dungeon_ovl_e0365c.h"

void func_80174460(void *record) {
 u8 *original;
 u8 *current;
 u8 *cursor;
 cursor=append_entity_display_text(record,current=get_unused_text_buffer());
 original=current;
 current=cursor;
 func_80099290((s8 *)expand_text_control_codes(D_801745CC,current));
 display_text_with_fullwidth_adjustment((s8 *)original);
}
#include "modules/dungeon_ovl_e0365c.h"

void display_entity_action_message(void *record) {
 u8 *original;
 u8 *current;
 u8 *cursor;
 cursor=append_entity_display_text(record,current=get_unused_text_buffer());
 original=current;
 current=cursor;
 func_80099290((s8 *)expand_text_control_codes(D_801745F8,current));
 display_text_with_fullwidth_adjustment((s8 *)original);
}
