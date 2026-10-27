#include "shared/object_node.h"
#include "shared/entity.h"
#include "sdk/libgpu.h"
#include "dungeon/level/room_flags.h"
#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* Block actor spawning, movement, attacks, and radial visual effects. */
#include "dungeon/monster/block.h"
#include "shared/actor_action_flags.h"
#include "shared/monster_ids.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/effect.h"
#include "engine/cd.h"

void *(*const cb3000_spawn_entry)(s16,s16,s16,s32) = create_linked_object_position;
void (*const cb3000_update_entry)(void *,CB_80170C24_S_80170C24_2 *,void *) = set_boss_effect_flag;

/* Stores the owner value, copies the source position, and initializes a gray sprite for rendering. */
void initialize_block_sprite_copy(CB_8017087C_Object *object, s32 field60_value, CB_8017087C_CopyFields *source_coords)
{
    CB_8017087C_Part *part;
    CB_8017087C_CopyFields *copy;

    object->field60 = field60_value;
    register_node(object, project_sprite_chain);

    part = object->part;
    part->field10 = 0x20;
    part->field14 |= 0xC;

    copy = object->copy;
    copy->x = source_coords->x;
    copy->y = source_coords->y;
    copy->z = source_coords->z;

    part = object->part;
    part->field1E = 0x1000;
    part->field1C = 0x1000;
    part->b = 0x80;
    part->g = 0x80;
    part->r = 0x80;
}


/* Expands and brightens the rotating effect, then shrinks and fades it until its timer expires. */
void expand_then_shrink_effect(void *effect, void *unused, void *visual)
{
    s16 state;
    s32 fade_brightness;
    u8 brightness;

    state = ((CB_80170920_S_80170920_0 *)effect)->unk_1C.s;
    switch (state) {
    case 0:
        ((CB_80170920_S_80170920_1 *)visual)->unk_1C += 0x258;
        ((CB_80170920_S_80170920_1 *)visual)->unk_1E += 0x258;
        brightness = ((CB_80170920_S_80170920_1 *)visual)->unk_0E + 0xC;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0E = brightness;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0D = brightness;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0C = brightness;
        if (((CB_80170920_S_80170920_1 *)visual)->unk_1C < 0x1770) {
            break;
        }
        ((CB_80170920_S_80170920_0 *)effect)->unk_1C.u++;
        break;
    case 1:
        ((CB_80170920_S_80170920_1 *)visual)->unk_10 = 0x20;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0E = 0x50;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0D = 0x50;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0C = 0x50;
        ((CB_80170920_S_80170920_0 *)effect)->unk_1C.u++;
        break;
    case 2:
        ((CB_80170920_S_80170920_1 *)visual)->unk_10 = 0x60;
        ((CB_80170920_S_80170920_0 *)effect)->unk_24.s--;
        ((CB_80170920_S_80170920_1 *)visual)->unk_1C -= 0x190;
        ((CB_80170920_S_80170920_1 *)visual)->unk_1E -= 0x190;
        fade_brightness = (((CB_80170920_S_80170920_0 *)effect)->unk_24.u << 7) /
                   ((CB_80170920_S_80170920_0 *)effect)->unk_26;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0E = fade_brightness;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0D = fade_brightness;
        ((CB_80170920_S_80170920_1 *)visual)->unk_0C = fade_brightness;
        break;
    }

    ((CB_80170920_S_80170920_1 *)visual)->unk_1A += 0x190;
    if (((CB_80170920_S_80170920_0 *)effect)->unk_24.u <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a Block actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_linked_object_position(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    void *result;
    void *object;
    CB_80170A5C_S_80170A5C_2 *part0;
    SpriteFrameState *part1;
    CB_80170A5C_S_80170A5C_4 *result_copy;

    result = 0;
    object = allocate_list_node(0x112, &scene_object_list_anchor.next);
    if (object != 0) {
        result = (u8 *)object;
        result += 0x20;
        ((CB_80170A5C_S_80170A5C_0 *)object)->unk_10 = set_boss_effect_flag;
        ((CB_80170A5C_S_80170A5C_1 *)result)->unk_13 = MONSTER_BLOCK;
        register_node(object, project_sprite_chain);

        {
            void *handler;

            part0 = ((CB_80170A5C_S_80170A5C_0 *)object)->unk_08;
            handler = block_slot_g_direction_frames;
            part0->unk_0A = attr_c;
            part1 = ((CB_80170A5C_S_80170A5C_0 *)object)->unk_0C;
            kind = spawn_flags & 3;
            part1->tile_y = attr_b;
            result_copy = result;
            part1->frameTable = handler;
        }
        part1->tile_x = attr_a;

        if (kind == 1) {
            flags0 = ((CB_80170A5C_S_80170A5C_1 *)result)->unk_14;
            flags1 = ((CB_80170A5C_S_80170A5C_1 *)result)->unk_1C;
            flags0 |= 0x6000;
            flags1 |= 0x6000;
            ((CB_80170A5C_S_80170A5C_1 *)result)->unk_14 = flags0;
            ((CB_80170A5C_S_80170A5C_1 *)result)->unk_1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((CB_80170A5C_S_80170A5C_1 *)result)->unk_14;
            flags1 = ((CB_80170A5C_S_80170A5C_1 *)result)->unk_1C;
            flags0 |= 0x2000;
            flags1 |= 0x2000;
            ((CB_80170A5C_S_80170A5C_1 *)result)->unk_14 = flags0;
            ((CB_80170A5C_S_80170A5C_1 *)result)->unk_1C = flags1;
        } else if (((spawn_flags & -4) << 16) == 0 &&
                   (((CB_80170A5C_S_80170A5C_1 *)result)->unk_14 & ACTOR_RESIST_SLEEP) == 0 &&
                   (generate_random_value() & 1) != 0) {
            set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
            part1->frameTable = block_frame_set_1;
        }

        initialize_actor_sprite_and_animation(object, part0, part1, spawn_flags);
        result_copy->unk_9A = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C = dispatch_actor_turn_and_motion;
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }
    return result;
}

/*
 * Runs actor callbacks and updates facing, animation, movement, and ground contact.
 *
 * MECHANISM: 2.7.2-cdk-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw /
 * addiu). The two byte parameters arrive as s16: their narrowing copies survive cse, combine folds
 * the a1/a2 temps into them, so sched1 schedules the parameter copies and the entry order is
 * retail's.
 */
void set_boss_effect_flag(void *entity, CB_80170C24_S_80170C24_2 *motion, void *monster)
{
    void *actor = entity;
    s32 direction;
    s16 direction_copy;
    s32 direction_value;
    s16 old_direction;
    CB_80170C24_Callback callback;
    u16 monster_flags;
    s16 floor_height;
    s16 actor_height;
    s16 direction_index;

    if (g_dungeon_status.flags & 0x2000) {
        CB_80170C24_Callback early_callback;

        early_callback = (*(CB_80170C24_Callback *)((u8 *)entity + 0x8C));
        if (early_callback == dispatch_actor_turn_and_motion) {
            early_callback(entity, motion, monster, entity);
        } else {
            (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        }
        return;
    }


    old_direction = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    if (refresh_actor_facing_and_lifecycle(entity, motion, monster, entity) != 0) {
        return;
    }

    callback = (*(CB_80170C24_Callback *)((u8 *)entity + 0x8C));
    if (callback != 0) {
        callback(entity, motion, monster, entity);
    }

    block_callbacks[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, monster, entity);

    if ((s16)old_direction != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, monster, entity);
    }

    monster_flags = ((CB_80170C24_S_80170C24_0 *)monster)->unk_14;
    if (!(monster_flags & 0x8000)) {
        direction_value = g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100;
        direction = (direction_value >> 9) & 7;
        direction_index = direction;
        direction_copy = direction;

        if ((*(s16 *)((u8 *)entity + 0x94)) != direction_index) {
            u8 *tile_map = ((CB_80170C24_S_80170C24_0 *)monster)->unk_2C;
            if (tile_map != 0) {
                select_indirect_table_entry(monster, tile_map[direction_index], ((CB_80170C24_S_80170C24_0 *)monster)->unk_04);
            }
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }

        if (dir_sprite_flag[direction_copy] != 0) {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 |= 1;
        } else {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 &= 0xFFFE;
        }

        if (!(((CB_80170C24_S_80170C24_1 *)actor)->unk_1C & 0x20)) {
            if (!(((CB_80170C24_S_80170C24_0 *)monster)->unk_14 & 0x40)) {
                advance_sprite_animation_and_textures(monster);
            }
        } else {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 |= 0x7000;
        }

        apply_monster_koyaw_data(((CB_80170C24_S_80170C24_1 *)actor)->unk_1C, (u8 *)monster + 0xC);
    } else {
        if (monster_flags & 0x0800) {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 = monster_flags & 0x8FFF;
        } else {
            ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 = monster_flags | 0x7000;
        }
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
                              (s16)(((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u - 0x20));
        if (floor_height < 0x200) {
            actor_height = ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.s;
            if ((*(s16 *)((u8 *)entity + 0x92)) + actor_height < floor_height) {
                ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xF7FFFFFF;
            } else {
                if (floor_height >= actor_height) {
                    (*(s32 *)((u8 *)entity + 0x90)) = 0;
                } else {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor_height - ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u;
                }

                motion->unk_14 = 0;
                ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C |= 0x08000000;
                (*(u8 *)((u8 *)entity + 0x9D)) = 0;
            }
            if (((CB_80170C24_S_80170C24_1 *)actor)->unk_1C & 0x40000000) {
                ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xBFFFFFFF;
                floor_height = sample_terrain_surface_height((((CB_80170C24_S_80170C24_0 *)monster)->unk_24 << 6) | 0x20,
                                      (((CB_80170C24_S_80170C24_0 *)monster)->unk_25 << 6) | 0x20,
                                      (s16)(((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u - 0x20));
                (*(s16 *)((u8 *)entity + 0x92)) += ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u - floor_height;
                ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u = floor_height;
            }
        } else {
            ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xF7FFFFFF;
        }
    } else {
        ((CB_80170C24_S_80170C24_1 *)actor)->unk_1C &= 0xF7FFFFFF;
    }

    motion->unk_0A =
        ((CB_80170C24_S_80170C24_1 *)actor)->unk_88.u + (*(u16 *)((u8 *)entity + 0x92));
    ((CB_80170C24_S_80170C24_0 *)monster)->unk_14 |= 0x40;

}


/* Selects movement, attacks, and spells from actor status, MP, and its position relative to the player. */
void dispatch_actor_turn_and_motion(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
 u16 terrain_flags;
 u8 *frames;
 s32 room;
 s32 actor_flags;
 u16 flags;
 if(g_dungeon_status.flags & 0x1000) {
  state->action_id.u=14;
  advance_actor_stored_path(state,motion,sprite,actor);
  return;
 }
 if(actor->mp_value.parts.whole==0) {
  advance_actor_pending_action(state,motion,sprite,actor);
  if(sprite->frameTable==block_frame_set_1) return;
  sprite->frameTable=block_frame_set;
  select_sprite_entry(sprite,block_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle+actor->facing+0x100)>>9)&7],0);
  return;
 }
 {
  if(actor->flags1C & 0x200) {
   if(sprite->frameTable==block_frame_set_1) {
    state->action_id.u=13;
    state->action_phase.u=1;
    state->unk_8C.handler=0;
    actor->flags1C &= 0xFFFBFFFF;
    return;
   }
   if(reset_actor_action_state(state,motion,sprite,block_frame_set)!=0) return;
  }
  if(!(g_dungeon_status.flags & 0x2000)) {
   if(actor->flags1C & 0x100) {
    begin_pushed_actor_move(state,motion,sprite,actor);
    return;
   }
   if(state->action_id.u!=14) {
    if(sprite->frameTable!=block_slot_g_direction_frames) {
     sprite->frameTable=block_slot_g_direction_frames;
     select_sprite_entry(sprite,block_slot_g_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle+actor->facing+0x100)>>9)&7],0);
    }
    state->action_id.u=14;
   }
   state->action_state_flags &= 0xFFF3;
   if(actor->hp_delta!=0 && begin_ready_actor_directional_action(state,motion,sprite,D_801752BC)!=0) return;
   if(actor->flags1C & 0x80000) {
    begin_actor_move_to_target_facing(state,motion,sprite,actor);
    update_transformed_actor_and_trap(state,motion,sprite,actor);
    return;
   }
   if((can_entity_gain_level(actor)<<16)!=0 && (process_selected_actor_record(state,motion,sprite,actor)<<16)!=0)
    wait_actor_activity_then_complete(state,motion,sprite,actor);
  }
  room=find_active_rect_containing_point(sprite->tile_x,sprite->tile_y);
  sprite->room_index=room;
  if(actor->pending_turn_updates>0) {
   if(actor->flags1C & 0x20) {
    update_actor_status_and_mp(actor);
    return;
   }
   if((*(u16 *)&sprite->tile_x)==reference_tile_position_alias) {
    choose_and_step_actor_path(state,motion,sprite,actor);
    return;
   }
   if(!(actor->action_flags & 0x8000)) {
    if((!(g_dungeon_status.flags & 0x2000) || (check_entity_relation(actor,primary_actor_record->previous_actor_header+0x20)<<16)==0)
       && (resolve_actor_action_readiness(state,motion,sprite,0)<<16)!=0) {
     flags=actor->action_flags | 0x4000;
     actor->action_flags=flags;
     if(!(flags & 0x8000)) {
      choose_and_step_actor_path(state,motion,sprite,actor);
      return;
     }
    } else return;
   }
   switch(actor->action_flags & 0x3FFF) {
   case 8: case 9:
    if((try_begin_adjacent_actor_attack(state,motion,sprite,actor)<<16)==0)
     begin_unchecked_directional_attack(state,motion,sprite,actor);
    return;
   case 5: case 6: case 7:
    actor->facing=get_rounded_facing_and_rounding_flag(sprite->tile_x,sprite->tile_y,reference_tile_object.tile_position.parts.tile_x,reference_tile_object.tile_position.parts.tile_y,&terrain_flags);
    if(primary_actor_record->action_id.u==17) {
     begin_actor_spell_action(state,motion,sprite,D_801752EC,dispatch_actor_turn_and_motion);
     return;
    }
    /* A failed pursuit falls through to the same completion path as action 12. */
   case 12:
    update_actor_status_and_mp(actor);
    return;
   case 1: case 2: case 3:
    begin_actor_spell_action(state,motion,sprite,D_801752EC,dispatch_actor_turn_and_motion);
    return;
   default:
    choose_and_step_actor_path(state,motion,sprite,actor);
    return;
   }
  }
  actor_flags=actor->flags1C;
  if(!(actor_flags & 0x2000) && ((s8)room<0 || !(((CB_8017102C_S_8017102C_5 *)((u8 *)dungeon_rooms+(s8)room*20))->unk_0C & 2)) && !(actor_flags & 0x430)) {
   if((test_neighbor_position_relation(sprite->tile_x,sprite->tile_y,reference_tile_object.tile_position.parts.tile_x,reference_tile_object.tile_position.parts.tile_y)<<16)!=0)
    actor->facing=get_rounded_facing_and_rounding_flag(sprite->tile_x,sprite->tile_y,reference_tile_object.tile_position.parts.tile_x,reference_tile_object.tile_position.parts.tile_y,&terrain_flags);
  }
  if((g_dungeon_status.flags & 0x2000) || (sprite->flags & 0x40)) return;
  frames=block_slot_g_direction_frames;
  if(sprite->frameTable==frames) return;
 }
 sprite->frameTable=frames;
 select_sprite_entry(sprite,*((((g_game_work.view.camera_rotation.parts.viewAngle+actor->facing+0x100)>>9)&7)+frames),0);
}

/* Advances one stored path step, updates occupied tiles and facing, and selects the movement animation and
 * delay. */
void advance_actor_stored_path(ActorRecord *motion, ObjectPosition *update_param, SpriteFrameState *entity, ActorRecord *state) {
    ActorRecord *rounding_owner = motion;
    s32 tile_mask;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s16 heading;
    s16 move_result;
    s16 stored_result;
    s32 result_code;

    if (((CB_80171590_S_80171590_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (!((s32)((CB_80171590_S_80171590_0 *)state)->unk_71.u > ((CB_80171590_S_80171590_0 *)state)->unk_8A.s)) {
        return;
    }

    if (((CB_80171590_S_80171590_1 *)entity)->unk_2C != block_frame_set_2) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = block_frame_set_2;
        select_sprite_entry(
            entity,
            block_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7],
            0);
    }

    old_x = ((CB_80171590_S_80171590_1 *)entity)->unk_24;
    old_y = ((CB_80171590_S_80171590_1 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((CB_80171590_S_80171590_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

    heading = get_rounded_facing_and_rounding_flag(
        old_x,
        old_y,
        ((CB_80171590_S_80171590_3 *)((u8 *)state + ((CB_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_74,
        ((CB_80171590_S_80171590_3 *)((u8 *)state + ((CB_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_7C,
        &rounding_owner->action_state_flags);
    move_result = check_movement_clearance_and_height(heading, entity, state, 0x20);

    ((CB_80171590_S_80171590_1 *)entity)->unk_24 =
        ((CB_80171590_S_80171590_3 *)((u8 *)state + ((CB_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_74;
    ((CB_80171590_S_80171590_1 *)entity)->unk_25 =
        ((CB_80171590_S_80171590_3 *)((u8 *)state + ((CB_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_7C;
    ((CB_80171590_S_80171590_0 *)state)->unk_8A.u++;

    new_x = ((CB_80171590_S_80171590_1 *)entity)->unk_24;
    new_y = ((CB_80171590_S_80171590_1 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((CB_80171590_S_80171590_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, tile_mask);
    state->facing = heading;

    stored_result = move_result;
    result_code = move_result;
    if (result_code == 2) {
        if (!(g_dungeon_status.flags & 0x80)) {
            if (!(((CB_80171590_S_80171590_1 *)entity)->unk_14 & 0x8000)) {
                begin_directional_actor_animation(motion, update_param, entity, state);
                ((CB_80171590_S_80171590_2 *)motion)->unk_A4 = stored_result;
            } else {
                ((CB_80171590_S_80171590_2 *)motion)->unk_9A = 15;
            }
        } else {
            ((CB_80171590_S_80171590_2 *)motion)->unk_9A = 15;
        }
    } else {
        if (result_code == 3 && !(g_dungeon_status.flags & 0x80) && !(((CB_80171590_S_80171590_1 *)entity)->unk_14 & 0x8000)) {
            begin_directional_actor_animation(motion, update_param, entity, state);
            ((CB_80171590_S_80171590_2 *)motion)->unk_A4 = stored_result;
        } else {
            ((CB_80171590_S_80171590_2 *)motion)->unk_9A = 15;
        }
    }

    ((CB_80171590_S_80171590_2 *)motion)->unk_8C = 0;
    (*(u32 *)&state->flags1C) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((CB_80171590_S_80171590_2 *)motion)->unk_96 = 0;
        return;
    }
    ((CB_80171590_S_80171590_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((CB_80171590_S_80171590_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((CB_80171590_S_80171590_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
    return;
}

/* Chooses a clear step or attack, records the actor's path, and updates occupied tiles and movement
 * counts. */
void choose_and_step_actor_path(Rec_func_800A9E70_arg0 *move_data, ObjectPosition *context, TileObject *position_data, ActorRecord *actor_data)
{
    u16 dungeon_flags = g_dungeon_status.flags;
    s32 limit_detour = 0;
    s16 detour_check;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;
    EntityRec *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_data->movement_queue_state >= 0) {
        if (actor_data->unk_12 >= 2 ||
            (s16)try_begin_adjacent_actor_attack(move_data, context, position_data, actor_data) == 0) {
            update_actor_status_and_mp(actor_data);
            return;
        }
        if (g_dungeon_status.active_actor == actor_data) {
            actor_data->action_flags = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    update_actor_proximity_flag(position_data, actor_data, 3, 6, &move_data->unk_9C.as_s8);
    actor_flags = actor_data->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)find_adjacent_actor(actor_data, position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y);
            blocker = (EntityRec *)current_angle;
            if (blocker != 0) {
                SpriteFrameState *blocker_owner = ((ObjectNodeHeader *)blocker - 1)->sprite;
                s16 target_angle = (s16)get_rounded_facing_and_rounding_flag(
                    position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                    blocker_owner->tile_x, blocker_owner->tile_y,
                    &move_data->unk_98);
                actor_data->facing = target_angle;
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
            if (!(actor_data->flags14 & 0x80000000)) {
                actor_data->flags14 |= 0x80000000;
                actor_data->facing += (generate_random_value() & 7) << 9;
            }
        } else {
            if (probe_directional_neighbor(actor_data, position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y, actor_data->facing) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u8 *turn_data;
                {
                    TileObject *target_position = &reference_tile_object;
                    s32 target_facing = ((u16)primary_actor_record->facing);
                    s32 offset_index =
                        ((((u8 *)&actor_data->unk_44)[1] + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position->tile_position.parts.tile_x +
                        *(u16 *)((u8 *)((s8 *)dir_step_x) + offset_index);
                    target_y = target_position->tile_position.parts.tile_y +
                        *(u16 *)((u8 *)((s8 *)dir_step_y) + offset_index);
                }

                if (position_data->tile_position.parts.tile_x == (u16)target_x &&
                    position_data->tile_position.parts.tile_y == (u16)target_y) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }

                turn_data = (u8 *)&move_data->unk_98;
                target_angle = (s16)get_rounded_facing_and_rounding_flag(
                    position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                    (s16)target_x, (s16)target_y, (u16 *)turn_data);
                actor_data->facing = target_angle;
                if (check_movement_clearance_and_height(target_angle, position_data, actor_data, 0x20) <= 0) {
                    actor_data->facing = (s16)get_rounded_facing_and_rounding_flag(
                        position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, (u16 *)turn_data);
                }
                if ((s16)test_neighbor_position_relation(
                        position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    limit_detour = 1;
                }
            } else {
                select_actor_route_target((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                              &move_data->unk_98);
            }
        }
    } else if (position_data->room_index >= 0 &&
               dungeon_rooms[position_data->room_index].flags & ROOM_HOLY_BEAM) {
        select_actor_route_target((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                      &move_data->unk_98);
    } else if (!(actor_data->action_flags & ACTOR_ACTION_PENDING)) {
        current_angle = (s32)probe_directional_neighbor(actor_data, position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y, actor_data->facing);
        blocker = (EntityRec *)current_angle;
        if (blocker != 0 &&
            (blocker->flags1C & ACTOR_PLAYER_SIDE) &&
            (s16)get_actor_height_difference(blocker, actor_data) < 0x81) {
            if (check_diagonal_side_height(
                    ((s16)*(u16 *)&actor_data->facing >> 9) & 0xFFFF,
                    position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                    (s16)((u16)actor_data->ground_height - 0x20)) != 0) {
                actor_data->movement_queue_state &= 0x7F;
                return;
            }
        }

        if (actor_data->flags1C & ACTOR_PLAYER_AWARE) {
            TileObject *target_position = &reference_tile_object;
            actor_data->facing = (s16)get_rounded_facing_and_rounding_flag(
                position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y, &move_data->unk_98);
            if ((s16)test_neighbor_position_relation(
                    position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                    target_position->tile_position.parts.tile_x, target_position->tile_position.parts.tile_y) != 0) {
                if (get_actor_height_difference(primary_actor_record, actor_data) < 0x81) {
                    if (check_diagonal_side_height(
                            ((s16)*(u16 *)&actor_data->facing >> 9) & 0xFFFF,
                            position_data->tile_position.parts.tile_x,
                                position_data->tile_position.parts.tile_y,
                            (s16)((u16)actor_data->ground_height - 0x20)) != 0) {
                        actor_data->movement_queue_state &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            select_actor_route_target((u8 *)position_data, move_data->unk_9C.as_s8, (u8 *)actor_data,
                          &move_data->unk_98);
        }
    }

    turn_index = 0;
    turn_table = actor_turn_angle_offsets;

    for (; turn_index < 8; turn_index++) {
        turn_flags = move_data->unk_98;
        current_angle = actor_data->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - turn_table[turn_index];
        } else {
            trial_angle = current_angle + turn_table[turn_index];
        }

        if (check_movement_clearance_and_height(trial_angle, position_data, actor_data, 0x20) > 0) {
            if (turn_index >= 3) {
                detour_check = limit_detour;
                if (detour_check != 0) {
                    actor_data->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_data->facing = trial_angle;
            /* remember the cell in the actor's trail of visited cells */
            ((u8 *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))[0x74] = position_data->tile_position.parts.tile_x;
            ((u8 *)((u8 *)actor_data + (actor_data->movement_queue_state & 0x7F)))[0x7C] = position_data->tile_position.parts.tile_y;
            actor_data->movement_queue_state++;

            update_map_cell_flags_with_item_limit(
                position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                (actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)((s8 *)dir_step_x);
                step_offset = (*(u16 *)&actor_data->facing >> 8) & 0xE;
                x_step += step_offset;
                position_data->tile_position.parts.tile_x += *x_step;
                position_data->tile_position.parts.tile_y += *((u8 *)((s8 *)dir_step_y) + step_offset);
            }

            cycle_map_cell_flags(
                position_data->tile_position.parts.tile_x, position_data->tile_position.parts.tile_y,
                (actor_data->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)(&reference_tile_object.tile_position.parts.tile_x) != *(u16 *)&position_data->tile_position.parts.tile_x) {
            if ((s16)check_entity_relation(actor_data,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                return;
            }
        }

    }

    if (turn_index >= 8) {
        actor_data->movement_queue_state &= 0x7F;
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        update_actor_status_and_mp(actor_data);
        return;
    }

    {
        actor_data->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        move_data->unk_9C.as_u8 = position_data->room_index;
        actor_data->pending_turn_updates--;
        g_dungeon_status.activity_counts.parts.pending_movement_count++;
    }
    if (actor_data->pending_turn_updates == 0) {
        actor_data->movement_queue_state &= 0x7F;
        return;
    }

    turn_index = sample_terrain_surface_height(
        (position_data->tile_position.parts.tile_x << 6) | 0x20,
        (position_data->tile_position.parts.tile_y << 6) | 0x20,
        (s16)((u16)actor_data->ground_height - 0x20));
    if (turn_index < 0x200) {
        actor_data->ground_height = turn_index;
    }
}


/*
 * Sets action state 0x10, clears its tick, and selects the camera-relative eight-way sprite entry
 * from D_801752C4.
 */
void begin_directional_actor_animation(ActorRecord *state, ObjectPosition *unused_position, SpriteFrameState *render_state, ActorRecord *entity) {
    state->action_id.u = 0x10;
    state->action_phase.u = 0;
    render_state->frameTable = D_801752C4;
    select_sprite_entry(render_state, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) + D_801752C4), 0);
}

/* Checks target compatibility, height, and action availability; starts an adjacent attack when allowed. */
s32 try_begin_adjacent_actor_attack(Rec_func_800A9E70_arg0 *action_state, ObjectPosition *motion_param, void *sprite_arg, ActorRecord *actor)
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

    target_angle = probe_directional_neighbor(actor, ((CB_80171FBC_S_80171DA0_1 *)sprite_arg)->unk_24,
                           ((CB_80171FBC_S_80171DA0_1 *)sprite_arg)->unk_25, actor->facing);
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

    apply_camera_offset_and_select_target((u8 *)actor - 0x20, motion_param, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) == 0) {
        action_state->unk_9A.as_u8 = 0x11;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        ((CB_80171FBC_S_80171DA0_1 *)sprite_arg)->unk_2C = block_slot_g_direction_frames;
        select_sprite_entry(sprite_arg, block_slot_g_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates--;
        prepare_directional_attack(actor, sprite_arg, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}

/* Claims an action slot, starts the directional attack animation, and prepares its target and damage
 * state. */
void begin_unchecked_directional_attack(ActorRecord *state, ObjectPosition *position, SpriteFrameState *render_state, ActorRecord *entity) {
    entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
    if (!(dungeon_status_flags_alias & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target(((u8 *)entity - 0x20), position, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            state->action_id.u = 0x11;
            state->unk_8C.handler = 0;
            state->action_phase.u = 0;
            render_state->frameTable = block_slot_g_direction_frames;
            select_sprite_entry(render_state, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) + block_slot_g_direction_frames), 0);
            ((CB_80172180_S_80172180_0 *)entity)->unk_6D = (u8) (((CB_80172180_S_80172180_0 *)entity)->unk_6D - 1);
            prepare_directional_attack(entity, render_state, entity->facing, 1, 0);
            ((CB_80172180_S_80172180_0 *)entity)->unk_84 = 0x7C;
            ((CB_80172180_S_80172180_0 *)entity)->unk_85 = 0;
        }
    }
}

/* Relinks actor state, updates status or movement as needed, and reports whether a new action may start. */
s32 resolve_actor_action_readiness(void *entity_arg, ObjectPosition *primary_context_arg, void *secondary_context_arg, s32 force_state_arg) {
    s16 state_type;
    s32 result;
    void *entity = entity_arg;

    state_type = (s16)relink_entity_and_clear_high_flag(primary_context_arg, secondary_context_arg, entity, 3, 6, entity + 0x9C);
    if (state_type < 0) return 0;
    if ((force_state_arg << 0x10) != 0) {
        choose_and_step_actor_path(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    }
    switch (state_type) {
    case 0:
        ((CB_80172298_S_80172628_0 *)entity)->unk_9A = 0xE;
        update_actor_status_and_mp(entity);
        result = 0;
        return result;
    case 2:
        choose_and_step_actor_path(entity, primary_context_arg, secondary_context_arg, entity);
        result = 0;
        return result;
    case 1:
        ((CB_80172298_S_80172628_0 *)entity)->unk_71 = (u8) (((CB_80172298_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((has_pending_dungeon_activity(entity) << 0x10) != 0) {
            break;
        }
                                /* fall through */
    default:
        ((CB_80172298_S_80172628_0 *)entity)->unk_71 = (u8) (((CB_80172298_S_80172628_0 *)entity)->unk_71 & 0x7F);
        if ((g_dungeon_status.flags & 8) == 0) {
            result = 1;
            return result;
        }
        break;
    }
    result = 0;
    ((CB_80172298_S_80172628_0 *)entity)->unk_46 = (u16) (((CB_80172298_S_80172628_0 *)entity)->unk_46 & 0x7FFF);
    return result;
}

/*
 * When tile movement finishes, spends MP and advances status timers; resumes turn dispatch and
 * clears its counter only after a positive signed floor-trap check. /
 */
void finish_actor_step_and_status(ActorRecord *state_arg, ObjectPosition *position, SpriteFrameState *render_state, ActorRecord *entity) {
    ActorRecord *state=state_arg;
    if (update_actor_movement_to_tile(state,position,render_state,entity) != 0) {
        spend_actor_mp(entity, 4);
        advance_status_timers(entity);
        if ((check_actor_floor_trap(render_state, entity) << 0x10) > 0) {
            state->unk_8C.handler = dispatch_actor_turn_and_motion;
            state->unk_90.value = 0;
        }
    }
}

/* Interpolates movement and height to the destination tile, emits landing effects, spends MP, and checks
 * traps. */
void update_tile_movement_and_height(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *map_entry, ActorRecord *actor) {
    u16 facing_output;
    s32 move_frames;
    s16 next_move_frame;
    s16 height_frame;
    s32 actor_flags;
    s32 scaled_height_delta;
    s32 move_value;
    s32 flags_mask;
    s32 move_operand;
    u16 timer_or_flags;
    s32 phase;

    phase = action->action_phase.u;
    switch (phase) {
    case 0:
        if (!(map_entry->flags & 0x6000)) {
            break;
        }
        map_entry->frameTable = D_801752CC;
        select_sprite_entry(map_entry, D_801752CC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        action->action_state_flags = (u16) (action->action_state_flags | 8);
        actor->flags1C = (s32) (actor->flags1C & ACTOR_GROUNDED_CLEAR_MASK);
        ((CB_80172458_S_80172458_0 *)action)->unk_9E = 5;
        ((CB_80172458_S_80172458_0 *)action)->unk_A0 = 0;
        action->action_phase.u = (u8) (action->action_phase.u + 1);
        ((CB_80172458_S_80172458_0 *)action)->unk_A6 = sample_terrain_surface_height((map_entry->tile_x << 6) | 0x20,
            (map_entry->tile_y << 6) | 0x20, (s16) (((u16)actor->ground_height) - 0x20));
        ((CB_80172458_S_80172458_0 *)action)->unk_A8 = (u16) ((u16)motion->z.w.i);
                        /* fall through */
    case 1:
        move_frames = ((CB_80172458_S_80172458_0 *)action)->unk_9E;
        ((CB_80172458_S_80172458_0 *)action)->unk_90 = (s32) (((CB_80172458_S_80172458_0 *)action)->unk_90 - ((CB_80172458_S_80172458_0 *)action)->unk_A0);
        if (move_frames != 0) {
            move_value = map_entry->tile_x;
            move_operand = motion->x.w.i;
            move_value <<= 6;
            move_operand -= 0x20;
            move_value = ((move_value - move_operand) << 0x10) / move_frames;
            move_operand = motion->y.w.i;
            motion->velocity_x = move_value;
            move_value = map_entry->tile_y;
            move_operand -= 0x20;
            move_value <<= 6;
            move_value -= move_operand;
            move_operand = ((CB_80172458_S_80172458_0 *)action)->unk_9E;
            move_value = (move_value << 0x10) / move_operand;
            motion->velocity_y = move_value;
            if (((CB_80172458_S_80172458_0 *)action)->unk_A4 == 3) {
                ((CB_80172458_S_80172458_0 *)action)->unk_A0 = (s32) ((0 - rsin(((CB_80172458_S_80172458_0 *)action)->unk_9E * 0x155))
                    << 9);
                ((CB_80172458_S_80172458_0 *)action)->unk_90 += ((CB_80172458_S_80172458_0 *)action)->unk_A0;
            } else {
                motion->velocity_z = 0;
                height_frame = ((CB_80172458_S_80172458_0 *)action)->unk_9E;
                switch (height_frame) {
                case 6:
                    flags_mask = 0xF7FF0000;
                    ((CB_80172458_S_80172458_0 *)action)->unk_90 = (s32) (0xFFFE0000 - ((((CB_80172458_S_80172458_0 *)action)->unk_A6
                        - (s16) ((CB_80172458_S_80172458_0 *)action)->unk_A8) << 0x10));
                    flags_mask |= 0xFFFF;
                    actor->flags1C = (s32) (actor->flags1C & flags_mask);
                    break;
                case 5:
                    flags_mask = 0xF7FF0000;
                    ((CB_80172458_S_80172458_0 *)action)->unk_90 = (s32) (0 - ((((CB_80172458_S_80172458_0 *)action)->unk_A6
                        - (s16) ((CB_80172458_S_80172458_0 *)action)->unk_A8) << 0x10));
                    flags_mask |= 0xFFFF;
                    actor->flags1C = (s32) (actor->flags1C & flags_mask);
                    break;
                case 4:
                    scaled_height_delta = (((CB_80172458_S_80172458_0 *)action)->unk_A6
                        - (s16) ((CB_80172458_S_80172458_0 *)action)->unk_A8) * 3;
                    ((CB_80172458_S_80172458_0 *)action)->unk_90 = (s32) (0 - ((scaled_height_delta / 4) << 0x10));
                    actor->flags1C = (s32) (actor->flags1C & ACTOR_GROUNDED_CLEAR_MASK);
                    break;
                case 3:
                    ((CB_80172458_S_80172458_0 *)action)->unk_90 = (s32) (0 - ((((((CB_80172458_S_80172458_0 *)action)->unk_A6
                        - (s16) ((CB_80172458_S_80172458_0 *)action)->unk_A8) * 2) / 5) << 0x10));
                    break;
                default:
                    ((CB_80172458_S_80172458_0 *)action)->unk_90 = 0;
                    break;
                }
            }
        }
        next_move_frame = (u16) ((CB_80172458_S_80172458_0 *)action)->unk_9E - 1;
        ((CB_80172458_S_80172458_0 *)action)->unk_9E = next_move_frame;
        if (next_move_frame < 0) {
            ((CB_80172458_S_80172458_0 *)action)->unk_90 = 0;
            action->action_state_flags = (u16) (action->action_state_flags & 0xFFF7);
            actor->flags1C = (s32) (actor->flags1C | ACTOR_GROUNDED);
            action->action_phase.u = (u8) (action->action_phase.u + 1);
        }
                        /* fall through */
    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            action->action_state_flags = (u16) (action->action_state_flags & 0xFFF7);
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, map_entry->tile_x, map_entry->tile_y);
            map_entry->frameTable = D_801752D4;
            select_sprite_entry(map_entry, D_801752D4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            initialize_timed_motion_step(4, 8);
            emit_scattered_effects_unless_blocked(motion);
            action->action_phase.u = 3U;
        }
        break;
    default:
        break;
    }
    timer_or_flags = ((CB_80172458_S_80172458_0 *)action)->unk_96 - 1;
    ((CB_80172458_S_80172458_0 *)action)->unk_96 = timer_or_flags;
    if ((timer_or_flags << 0x10) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, map_entry->tile_x, map_entry->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count = (s16) ((u16) g_dungeon_status.activity_counts.parts.pending_movement_count - 1);
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            timer_or_flags = actor->action_flags;
            if (timer_or_flags & 0x8000) {
                actor->action_flags = timer_or_flags & 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(map_entry->tile_x,
                    map_entry->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_output);
            }
        }
        if ((check_actor_floor_trap(map_entry, actor) << 0x10) > 0) {
            ((CB_80172458_S_80172458_0 *)action)->unk_8C = dispatch_actor_turn_and_motion;
            on_actor_status_updated(actor);
        }
    }
}

/*
 * Resumes turn dispatch after linked motion completes and the signed floor-trap check returns
 * positive.
 */
void finish_linked_motion_and_trap(ActorRecord *state, ObjectPosition *position, SpriteFrameState *render_state, ActorRecord *entity) {
    if ((update_linked_actor_motion(state,position,render_state,entity) != 0) && ((check_actor_floor_trap(render_state, entity) << 0x10) > 0)) {
        state->unk_8C.handler = dispatch_actor_turn_and_motion;
    }
}

/* Times an attack animation and sound, applies damage, spends MP, and restores actor movement. */
void complete_timed_actor_animation(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 state;
    s32 next_state;
    s32 start_state;
    u16 timer;

    state = ((CB_801729A8_S_801729A8_0 *)action)->phase;
    start_state = 1;
    switch (state) {
    case 0:
        ((CB_801729A8_S_801729A8_0 *)action)->phase = start_state;
                        /* fall through */
    case 1:
        if (sprite->flags & 0x8000) {
            ((CB_801729A8_S_801729A8_0 *)action)->phase = 3;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        ((CB_801729A8_S_801729A8_3 *)motion)->unk_14 = 0;
        ((CB_801729A8_S_801729A8_3 *)motion)->unk_10 = 0;
        ((CB_801729A8_S_801729A8_3 *)motion)->unk_0C = 0;
        sprite->frameTable = D_801752DC;
        select_sprite_entry(sprite,
            D_801752DC[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        next_state = ((CB_801729A8_S_801729A8_0 *)action)->phase;
        ((CB_801729A8_S_801729A8_0 *)action)->timer.s = 0;
        next_state++;
        ((CB_801729A8_S_801729A8_0 *)action)->phase = next_state;
        return;
    case 2:
        timer = ((CB_801729A8_S_801729A8_0 *)action)->timer.s + 1;
        ((CB_801729A8_S_801729A8_0 *)action)->timer.s = timer;
        if ((s16)timer == 7 || (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        }
        if (((CB_801729A8_S_801729A8_0 *)action)->timer.u == 6) {
            play_sound_if_enabled(0x808);
        }
        if (((CB_801729A8_S_801729A8_0 *)action)->timer.u == 8) {
            sprite->flags |= 0x0800;
        }
        if (((CB_801729A8_S_801729A8_0 *)action)->timer.u == 15 ||
            (sprite->flags & 0x8000)) {
            sprite->flags &= 0xF7FF;
            next_state = ((CB_801729A8_S_801729A8_0 *)action)->phase;
            next_state++;
            ((CB_801729A8_S_801729A8_0 *)action)->phase = next_state;
        }
        return;
    case 3:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            ((CB_801729A8_S_801729A8_0 *)action)->unk_8C = dispatch_actor_turn_and_motion;
            g_dungeon_status.active_actor = 0;
            advance_status_timers(actor);
            actor->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        }
        return;
    default:
        return;
    }
}

/* Starts a targeted spell with an expanding effect, then restores movement and status after the animation. */
void advance_actor_item_action_effect(CB_80172BCC_S_func_80C953CC_1 *work, CB_80172BCC_S_func_80C953CC_2 *position, CB_80172BCC_S_func_80C953CC_3 *entity,
    CB_80172BCC_S_func_80C953CC_4 *actor)
{
    CB_80172BCC_S_func_80C953CC_9 *part;
    s32 alternate = 0;

    switch (work->unk_9B) {
    case 0:
        if (actor->unk_1C & ACTOR_PLAYER_SIDE) {
            switch (actor->unk_46 & 0x3FFF) {
            case 7:
                alternate = 1;
                /* fallthrough */
            case 3:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 0xE);
                break;
            case 6:
                alternate = 1;
                /* fallthrough */
            case 2:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 0xB);
                break;
            case 5:
                alternate = 1;
                /* fallthrough */
            case 1:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 8);
                break;
            default:
                part = 0;
                break;
            }
        } else {
            switch (actor->unk_46 & 0x3FFF) {
            case 3:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 0xE);
                break;
            case 2:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 0xB);
                break;
            case 1:
                part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)actor + 8);
                break;
            default:
                part = 0;
                break;
            }
        }

        if (part->unk_00 != 0) {
            void *target_actor;
            CB_80172BCC_S_func_80C953CC_3 *target_entity;

            (work->unk_98) &= 0xFF7F;
            if ((s8)alternate) {
                actor->unk_60 = target_actor = primary_actor_record;
                target_entity = *(CB_80172BCC_S_func_80C953CC_3 **)((u8 *)target_actor - 0x14);
                actor->unk_72.u8 = target_entity->unk_24;
                actor->unk_73.u8 = target_entity->unk_25;
            } else if (item_action_definitions[part->unk_00].kind == 2) {
                if ((target_actor = actor->unk_60) != 0) {
                    target_entity = *(CB_80172BCC_S_func_80C953CC_3 **)((u8 *)target_actor - 0x14);
                    actor->unk_72.u8 = target_entity->unk_24;
                    actor->unk_73.u8 = target_entity->unk_25;
                }
            } else {
                s32 target_x;
                s32 target_y;

                actor->unk_60 =
                    scan_actor_along_heading(actor, entity->unk_24,
                                  entity->unk_25,
                                  actor->unk_2A, 0x10);
                target_x = abs(actor->unk_72.s8);
                target_y = abs(actor->unk_73.s8);
                actor->unk_72.u8 = target_x;
                actor->unk_73.u8 = target_y;
            }

            if (create_actor_spell_effect(actor, part, alternate, (u8 *)work + 0x98) != 0) {
                work->unk_9B++;
            }
        } else {
            CB_80172BCC_S_func_80C953CC_5 *active_actor;

            position->unk_14 = 0;
            position->unk_10 = 0;
            position->unk_0C = 0;
            set_record_integer_tile_center(position, entity->unk_24,
                          entity->unk_25);
            active_actor = primary_actor_record;
            g_dungeon_status.active_actor = 0;
            (active_actor->unk_A6)--;
            advance_status_timers(actor);
            actor->unk_6D--;
            work->unk_8C = dispatch_actor_turn_and_motion;
            actor->unk_73.u8 = 0;
            actor->unk_72.u8 = 0;
            actor->unk_46 &= 0x7FFF;
        }
        break;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            entity->unk_14 |= 0x800;
            break;
        }

        entity->unk_14 &= 0xF7FF;
        work->unk_9B++;
        actor = allocate_flagged_object_node(0x212);
        if (actor != 0) {
            CB_80172BCC_S_func_80C953CC_6 *transform;
            CB_80172BCC_S_func_80C953CC_7 *node;
            CB_80172BCC_S_func_80C953CC_8 *model;

            initialize_block_sprite_copy(actor, work, position);
            transform = (CB_80172BCC_S_func_80C953CC_6 *)((u8 *)actor + 0x20);
            transform->unk_24 = 10;
            transform->unk_26 = 10;
            node = actor->unk_08;
            actor->unk_10 = expand_then_shrink_effect;
            node->unk_0A -= 0x1E;
            model = actor->unk_0C;
            model->unk_10 = 0x60;
            model->unk_06 = 6;
            model->unk_1E = 0;
            model->unk_1C = 0;
            model->unk_0E = 0;
            model->unk_0D = 0;
            model->unk_0C = 0;
            *(CB_80172BCC_Copy12 *)((u8 *)actor + 0x9A) = D_8017539C;
            model->unk_08 = (u8 *)actor + 0x9A;
        }
        play_sound_if_enabled(0x703);
        break;

    case 2:
        if ((entity->unk_04 == 5 &&
             (entity->unk_14 & 0x1000)) ||
            (entity->unk_14 & 0xE000)) {
            work->unk_96 = 0x20;
            work->unk_98 |= 0x80;
            work->unk_9B++;
        }
        break;

    case 3:
        part = (CB_80172BCC_S_func_80C953CC_9 *)((u8 *)((s32 *)&g_dungeon_status.active_actor) - 0x0C);
        if (part->unk_0C == 0) {
            work->unk_96 = 0;
        }
        if (!(entity->unk_14 & 0xE000)) {
            break;
        }

        position->unk_14 = 0;
        position->unk_10 = 0;
        position->unk_0C = 0;
        set_record_integer_tile_center(position, entity->unk_24,
                      entity->unk_25);
        if (entity->unk_2C != block_slot_g_direction_frames) {
            s32 direction;

            (entity->unk_2C) = block_slot_g_direction_frames;
            direction = (g_game_work.view.camera_rotation.parts.viewAngle + actor->unk_2A + 0x100) >> 9;
            select_sprite_entry(entity, block_slot_g_direction_frames[direction & 7], 0);
        }
        if (part->unk_0C != 0) {
            break;
        }

        part->unk_0A--;
        work->unk_8C = dispatch_actor_turn_and_motion;
        advance_status_timers(actor);
        actor->unk_73.u8 = 0;
        actor->unk_72.u8 = 0;
        actor->unk_6D--;
        actor->unk_46 &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        break;
    }
}

/* Applies a value change, emits scattered effects, waits for recovery, then recenters and restores the
 * actor. */
void update_block_value_reaction(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *action, ActorRecord *entity) {
    s16 phase;
    u16 ticks_left;
    s16 wait_ticks;
    u8 *next_script;

    phase = state->action_phase.u;
    switch (phase) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        emit_scattered_effects_unless_blocked(motion);
        emit_scattered_effects_unless_blocked(motion);
        emit_scattered_effects_unless_blocked(motion);
        emit_scattered_effects_unless_blocked(motion);
        initialize_timed_motion_step(4, 6);
        state->action_phase.s = state->action_phase.u + 1;
        if (entity->hp != 0) {
            if (action->flags & 0x8000) {
                state->action_timer.s = 0;
                state->action_phase.s = 2;
                return;
            }
            wait_ticks = -1U;
            if (entity->flags1C & 0x228)
                wait_ticks = 8;
            state->action_timer.s = wait_ticks;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(state, motion, action, &D_801752E4);
            return;
        }
    case 1:
        if (state->action_timer.s > 0) {
            ticks_left = state->action_timer.u - 1;
            state->action_timer.s = ticks_left;
        } else {
            if (action->flags & 0x6000)
                state->action_timer.s = 0;
        }
        if (state->action_timer.s != 0)
            return;
        if (entity->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(state, motion, action, &D_801752E4);
            return;
        }
        initialize_timed_motion_step(1, 1);
        state->action_timer.s = 8;
        state->action_phase.s = state->action_phase.u + 1;
        return;
    case 2:
        ticks_left = state->action_timer.u - 1;
        state->action_timer.s = ticks_left;
        if ((ticks_left << 0x10) > 0)
            return;
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, action->tile_x, action->tile_y);
        if (((s32)g_dungeon_status.pending_display_owner) == ((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = ((s32)g_dungeon_status.pending_display_owner) & 0x7FFFFFFF;
        }
        next_script = dispatch_actor_turn_and_motion;
        state->unk_8C.address = next_script;
        return;
    }
}

/* Runs the shared actor defeat and removal sequence with the supplied callback arguments. */
void remove_defeated_block(void *state,void *position,void *render_state,void *entity) {
    update_actor_defeat_removal(state,position,render_state,entity);
}

/* Runs the shared hop and shrink sequence for the actor with the supplied callback arguments. */
void shrink_hopping_block(void *state,void *position,void *render_state,void *entity) {
    update_actor_hop_and_shrink(state,position,render_state,entity);
}

/* Runs the shared actor removal sequence with the supplied callback arguments. */
void advance_block_removal(void *state,void *position,void *render_state,void *entity) {
    advance_actor_removal(state,position,render_state,entity);
}

/*
 * Runs update_actor_hop_and_grow and installs dispatch_actor_turn_and_motion when it returns
 * nonzero.
 */
void resume_actor_after_growth(ActorRecord *state, ObjectPosition *position, SpriteFrameState *render_state, ActorRecord *entity) {
    if (update_actor_hop_and_grow(state,position,render_state,entity) != 0) {
        state->unk_8C.handler = dispatch_actor_turn_and_motion;
    }
}

/* Waits for a status effect to clear, updates actor status and activity counts, then restores movement. */
void wait_actor_status_and_animate(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite_in, ActorRecord *actor_in) {
    s32 state;
    void *actor_to_check;
    DungeonGlobalStatus *status;
    s32 actor_flags;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        if (!(((CB_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = block_frame_set_1;
        select_sprite_entry(sprite_in,
            block_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor_in->facing + 0x100) >> 9) & 7],
            0);
        {
            DungeonGlobalStatus *counter_base;

            counter_base = &g_dungeon_status;
            counter_base->activity_counts.parts.pending_action_count =
                ((u16)counter_base->activity_counts.parts.pending_action_count) - 1;
        }
        action->action_phase.u++;
        return;

    case 1:
        if ((get_entity_effect_value(actor_in, STATUS_SLEEP) << 16) != 0) {
            status = &g_dungeon_status;
            if (status->flags & 0x1000) {
                return;
            }
            if (actor_in->hp_delta != 0) {
                if (begin_ready_actor_directional_action(action, context, sprite_in, 0) != 0) {
                    return;
                }
            }
            if (actor_in->mp_value.parts.whole == 0) {
                if (status->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(action, context, sprite_in, actor_in);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_in) << 16) != 0) {
                return;
            }
            actor_flags = actor_in->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(action, context, sprite_in, actor_in);
                update_transformed_actor_and_trap(action, context, sprite_in, actor_in);
                return;
            }
            if (actor_in->pending_turn_updates == 0) {
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
            do {
            if ((get_entity_effect_value(actor_in, STATUS_SLEEP) << 16) != 0) {
                s8 coordinate = ((CB_8017339C_S_80173D4C_1 *)sprite_in)->unk_26;
                TileObject *origin = &reference_tile_object;
                s32 probe_result;

                if ((coordinate != origin->room_index) || (coordinate < 0)) {
                    probe_result = get_tile_chebyshev_distance(origin, sprite_in);
                    actor_to_check = actor_in;
                    if (probe_result >= 2) {
                        break;
                    }
                    if (!(generate_random_value(actor_in) & 7)) {
                        clear_slots_of_type(actor_in, STATUS_SLEEP);
                    }
                } else {
                    if (!(generate_random_value(origin) & 7)) {
                        clear_slots_of_type(actor_in, STATUS_SLEEP);
                    }
                }
            }

            actor_to_check = actor_in;
            } while (0);

            if ((get_entity_effect_value(actor_to_check, STATUS_SLEEP) << 16) != 0) {
                return;
            }

            (*(void * *)((u8 *)sprite_in + 0x2C)) = block_status_frames;
            select_sprite_entry(sprite_in,
                block_status_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor_in->facing + 0x100) >> 9) & 7],
                0);
            if (((CB_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
                ((CB_8017339C_S_80173D4C_0 *)action)->unk_8C = dispatch_actor_turn_and_motion;
                return;
            }
            g_dungeon_status.activity_counts.parts.pending_action_count++;

            action->action_phase.u++;
            return;
        }
        (*(void * *)((u8 *)sprite_in + 0x2C)) = block_status_frames;
        select_sprite_entry(sprite_in,
            block_status_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor_in->facing + 0x100) >> 9) & 7],
            0);
        if (((CB_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0x8000) {
            ((CB_8017339C_S_80173D4C_0 *)action)->unk_8C = dispatch_actor_turn_and_motion;
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count++;

        action->action_phase.u++;
        return;

    case 2:
        if (!(((CB_8017339C_S_80173D4C_1 *)sprite_in)->unk_14 & 0xE000)) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;

        ((CB_8017339C_S_80173D4C_0 *)action)->unk_8C = dispatch_actor_turn_and_motion;

        return;
    }
}

/* Waits for MP recovery while processing actor status, then restores the normal animation and movement. */
void wait_actor_mp_and_animate(ActorRecord *actor_in, ObjectPosition *actor_index, SpriteFrameState *target, ActorRecord *entity_in) {
    ActorRecord *entity = entity_in;
    s32 state;
    s32 entity_flags;
    s32 direction;
    DungeonGlobalStatus *shared_state;
    state = actor_in->action_phase.u;
    switch (state) {
    case 0:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count--;
    }
    (*(void * *)((u8 *)target + 0x2C)) = block_frame_set_1;
    direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
    select_sprite_entry(target, block_frame_set_1[direction & 7], 0);
    actor_in->action_phase.u++;
    return;

    case 1:
    if (entity->mp_value.parts.whole != 0) {
        DungeonGlobalStatus *shared_counter;

        (*(void * *)((u8 *)target + 0x2C)) = block_status_frames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, block_status_frames[direction & 7], 0);
        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count++;
        actor_in->action_phase.u++;
        return;
    } else {
        shared_state = &g_dungeon_status;
        if (shared_state->flags & 0x1000) {
            return;
        }
        if (entity->hp_delta != 0) {
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
            update_transformed_actor_and_trap(actor_in, actor_index, target, entity);
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
            update_actor_status_and_mp(entity);
        } else {
            update_actor_status_and_mp(entity);
        }
        on_actor_status_updated(entity);
        if (entity->mp_value.parts.whole == 0) {
            return;
        }
        (*(void * *)((u8 *)target + 0x2C)) = block_status_frames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, block_status_frames[direction & 7], 0);
        shared_state->activity_counts.parts.pending_action_count++;
    }
    actor_in->action_phase.u++;
    return;

    case 2:
    if (!(((Rec_D_80082E80 *)target)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count--;
    }
    ((CB_8017372C_S_801740DC_0 *)actor_in)->unk_8C = dispatch_actor_turn_and_motion;

    return;
    default:
        return;
    }
}

/*
 * Resumes turn dispatch after parent motion and a positive signed floor-trap check; during motion,
 * restores the direction frames when the alternate table is active and flags 0x208 are clear.
 */
void update_transformed_actor_and_trap(ActorRecord *state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    if (update_actor_transform_from_parent(state,position,sprite,actor) != 0) {
        if ((check_actor_floor_trap(sprite, actor) << 0x10) > 0) {
            state->unk_8C.handler = dispatch_actor_turn_and_motion;
        }
    } else if ((sprite->frameTable == block_frame_set_1) && !(actor->flags1C & 0x208)) {
        sprite->frameTable = block_frame_set_2;
        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + block_frame_set_2), 0);
    }
}

/*
 * Resumes turn dispatch after thrown travel completes and the signed floor-trap check returns
 * positive.
 */
void finish_actor_throw_and_trap(ActorRecord *state, ObjectPosition *position, SpriteFrameState *render_state, ActorRecord *entity) {
    if ((update_thrown_actor_travel(state,position,render_state,entity) != 0) && ((check_actor_floor_trap(render_state, entity) << 0x10) > 0)) {
        state->unk_8C.handler = dispatch_actor_turn_and_motion;
    }
}

/*
 * Runs interpolate_actor_to_terrain_tile and installs dispatch_actor_turn_and_motion when it
 * returns nonzero.
 */
void finish_block_terrain_move(ActorRecord *state, ObjectPosition *position, SpriteFrameState *render_state, ActorRecord *entity) {
    if (interpolate_actor_to_terrain_tile(state,position,render_state,entity) != 0) {
        state->unk_8C.handler = dispatch_actor_turn_and_motion;
    }
}

/*
 * Runs update_spinning_actor_fall and installs dispatch_actor_turn_and_motion when it returns
 * nonzero.
 */
void resume_actor_after_spinning_fall(ActorRecord *state, ObjectPosition *position, SpriteFrameState *render_state, ActorRecord *entity) {
    if (update_spinning_actor_fall(state,position,render_state,entity) != 0) {
        state->unk_8C.handler = dispatch_actor_turn_and_motion;
    }
}

/* Runs update_actor_fade_in and installs dispatch_actor_turn_and_motion when it returns nonzero. */
void resume_actor_after_fade(ActorRecord *state, ObjectPosition *position, SpriteFrameState *render_state, ActorRecord *entity) {
    if (update_actor_fade_in(state,position,render_state) != 0) {
        state->unk_8C.handler = dispatch_actor_turn_and_motion;
    }
}

/* Rotates the primitive, scales its color by remaining lifetime, and flags it for removal on timeout. */
void fade_timed_primitive_effect(void *effect, s32 unused, void *primitive)
{
    u16 ticks_left;

    *(u16 *)((u8 *)primitive + 0x1A) += 0x320;
    *(s8 *)((u8 *)primitive + 0x0C) =
        (*(u8 *)((u8 *)effect + 0) * *(s16 *)((u8 *)effect + 0x24)) / 5;
    *(s8 *)((u8 *)primitive + 0x0D) =
        (*(u8 *)((u8 *)effect + 1) * *(s16 *)((u8 *)effect + 0x24)) / 5;
    *(s8 *)((u8 *)primitive + 0x0E) =
        (*(u8 *)((u8 *)effect + 2) * *(s16 *)((u8 *)effect + 0x24)) / 5;

    ticks_left = *(u16 *)((u8 *)effect + 0x24) - 1;
    *(s16 *)((u8 *)effect + 0x24) = ticks_left;
    if ((ticks_left << 16) <= 0) {
        ObjectFlagBlock *global_flags = &object_flag_block;

        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        global_flags->flags |= 0x8000;
    }
}

/* Creates a small gray fading sprite at the source position with the supplied scale and randomized
 * rotation. */
void create_randomized_rotated_effect(void *unused_context, Rec_func_80173CFC_arg1 *source_pos, s32 unused_value, s16 scale)
{
    ObjectNodeHeader * effect;
    CB_80173CFC_S_80173CFC_0 *effect_part;
    SpriteFrameState *effect_data;
    ObjectPosition *effect_pos;

    effect = allocate_flagged_object_node(0x212);
    if (effect != 0) {
        effect_part = (u8 *)effect + 0x20;
        effect_part->unk_24 = 5;
        (effect->update_callback) = fade_timed_primitive_effect;
        register_node(effect, project_sprite_chain);
        effect_data = effect->sprite;
        effect_data->tpage_abr = 0x60;
        effect_data->flags |= 0xC;
        effect_pos = effect->position;
        effect_pos->x.w.i = source_pos->unk_00.at02_u16.v;
        effect_pos->y.w.i = source_pos->unk_04.at02_u16.v;
        effect_pos->z.w.i = source_pos->unk_0A - 0x28;
        effect_data = effect->sprite;
        effect_data->depth_bias = 6;
        effect_data->scale_y = scale;
        effect_data->scale_x = scale;
        effect_part->unk_01 = 0x30;
        effect_part->unk_02 = 0x30;
        (*(s8 *)((u8 *)effect + 0x20)) = 0x30;
        effect_data->color.c.b = 0x30;
        effect_data->color.c.g = 0x30;
        effect_data->color.c.r = 0x30;
        effect_data->angle_z = rand() & 0xFFF;
        (*(CB_80173CFC_Copy12 *)((u8 *)effect + 0x9A)) = (*(CB_80173CFC_Copy12 *)((u8 *)D_80175324 + 0));
        effect_data->source = (u8 *)effect + 0x9A;
    }
}

/*
 * Projects an effect quad, checks its screen bounds and depth, and queues visible shaded polygons.
 *
 * MECHANISM: The four-argument ABI keeps source_pos/scale in s3/s4 while effect, effect_data, and
 * effect+0x20 occupy s2/s1/s0, producing retail's 0x28 frame and full save set. One packed 12-byte
 * assignment emits the retail lwl/lwr and swl/swr copy.
 */
void project_visible_effect_quad(void *quad, void *position, void *render_info, s16 depth_bias)
{
    u8 *scratch = (u8 *)0x1F800000;
    u8 *packet;
    u8 *texture;
    s32 ot_index;
    u16 render_flags;
    u16 texture_page;
    u8 texture_flags;
    GameWork *render_state_ptr = &g_game_work;
    CB_80173E40_MATRIX current_matrix;

    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p = *(u8 **)((u8 *)(&g_game_work)) + 0xB0;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_88 = ((CB_80173E40_S_80173E40_1 *)position)->unk_02;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_8C = ((CB_80173E40_S_80173E40_1 *)position)->unk_06;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_90 = ((CB_80173E40_S_80173E40_1 *)position)->unk_0A;
    ((CB_80173E40_S_80173E40_2 *)render_info)->unk_14 |= 0x8000;

    PushMatrix();

    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_3C = 0x2000;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_38 = 0x2000;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_34 = 0x2000;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_A4 = ((CB_80173E40_S_80173E40_2 *)render_info)->unk_16;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_A8 = ((CB_80173E40_S_80173E40_2 *)render_info)->unk_1A;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_A6 = ((CB_80173E40_S_80173E40_2 *)render_info)->unk_18;
    RotMatrix(scratch + 0xA4, scratch + 0x74);
    ReadRotMatrix(&current_matrix);
    CompMatrix(&current_matrix, scratch + 0x74, scratch + 0x54);
    ScaleMatrix(scratch + 0x54, scratch + 0x34);
    SetTransMatrix(scratch + 0x54);
    SetRotMatrix(scratch + 0x54);

    texture = (*(u8 * *)((u8 *)render_info + 8));
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_28 = ((CB_80173E40_S_80173E40_2 *)render_info)->unk_14;
    packet = ((CB_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_8D0;
    ((CB_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_8D0 = packet + 0xC;
    texture_page = GetTPage(0, 0, 0, 0);
    SetDrawMode(packet, 0, 0, texture_page, 0);

    (*(u32 *)((u8 *)packet + 0)) = (((CB_80173E40_S_80173E40_4 *)packet)->unk_00 & 0xFF000000) |
        (((CB_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_B0 & 0x00FFFFFF);
    (*(u32 *)((u8 *)(g_game_work.draw_buffer) + 0xB0)) =
        (((CB_80173E40_S_80173E40_3 *)(g_game_work.draw_buffer))->unk_B0 & 0xFF000000) |
        ((u32)packet & 0x00FFFFFF);

    {
        u8 *render_state = g_game_work.draw_buffer;
        packet = ((CB_80173E40_S_80173E40_5 *)render_state)->unk_8D0;
        ((CB_80173E40_S_80173E40_5 *)render_state)->unk_8D0 = packet + 0x24;
    }

    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_B0 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_44;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_B8 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_4A;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_C0 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_50;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_C8 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_56;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_B2 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_46;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_BA = ((CB_80173E40_S_80173E40_6 *)quad)->unk_4C;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_C2 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_52;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_CA = ((CB_80173E40_S_80173E40_6 *)quad)->unk_58;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_B4 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_48;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_BC = ((CB_80173E40_S_80173E40_6 *)quad)->unk_4E;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_C4 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_54;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_CC = ((CB_80173E40_S_80173E40_6 *)quad)->unk_5A;

    ot_index = RotAverage4(scratch + 0xB0, scratch + 0xB8,
                             scratch + 0xC0, scratch + 0xC8,
                             packet + 8, packet + 0x10,
                             packet + 0x18, packet + 0x20,
                             scratch + 0xD0, scratch + 0xD4) - depth_bias - 6;
    ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 = ot_index;

    if ((u32)ot_index < 0x1E0) {
        if ((((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_08 + 0x20) < 0x181) &&
             ((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_0A + 0x20) < 0x121)) |
            (((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_10 + 0x20) < 0x181) &&
             ((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_12 + 0x20) < 0x121)) |
            (((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_18 + 0x20) < 0x181) &&
             ((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_1A + 0x20) < 0x121)) |
            (((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_20 + 0x20) < 0x181) &&
             ((u16)(((CB_80173E40_S_80173E40_4 *)packet)->unk_22 + 0x20) < 0x121))) {
            ((CB_80173E40_S_80173E40_2 *)render_info)->unk_14 &= 0x7FFF;
            texture_flags = texture[1];
            ((CB_80173E40_S_80173E40_2 *)render_info)->unk_0F = texture_flags;
            render_flags = ((CB_80173E40_S_80173E40_0 *)scratch)->unk_28;
            if (render_flags & 8) {
                ((CB_80173E40_S_80173E40_2 *)render_info)->unk_0F = (render_flags & 4) ?
                    (texture_flags | 2) : (texture_flags & 0xFD);
            }

            ((CB_80173E40_S_80173E40_4 *)packet)->unk_04.at00.v = ((CB_80173E40_S_80173E40_6 *)quad)->unk_04;
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_0C = ((CB_80173E40_S_80173E40_6 *)quad)->unk_08;
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_14 = ((CB_80173E40_S_80173E40_6 *)quad)->unk_0C;
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_1C = ((CB_80173E40_S_80173E40_6 *)quad)->unk_10;
            SetPolyG4(packet);
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_04.at03.v |= 2;

            ((CB_80173E40_S_80173E40_4 *)packet)->unk_00 = (((CB_80173E40_S_80173E40_4 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2) + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);

            packet = ((CB_80173E40_S_80173E40_7 *)(render_state_ptr->draw_buffer))->unk_8D0;
            ((CB_80173E40_S_80173E40_7 *)(render_state_ptr->draw_buffer))->unk_8D0 = packet + 0xC;
            texture_page = GetTPage(0, 1, 0, 0);
            SetDrawMode(packet, 0, 0, texture_page, 0);
            ((CB_80173E40_S_80173E40_4 *)packet)->unk_00 = (((CB_80173E40_S_80173E40_4 *)packet)->unk_00 & 0xFF000000) |
                ((*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0x00FFFFFF);
            (*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2) + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) =
                ((*(u32 *)((u8 *)(((CB_80173E40_S_80173E40_0 *)scratch)->unk_24.p2)
                    + ((CB_80173E40_S_80173E40_0 *)scratch)->unk_100 * 4)) & 0xFF000000) |
                ((u32)packet & 0x00FFFFFF);
        }
    }

    PopMatrix();
}

/* Traverses linked effect nodes and projects each node's visible quad into render packets. */
s32 advance_boss_command_stream(void *point, void *position, void *color) {
 void *next;
 for (;;) {
  project_visible_effect_quad(point,position,color,0);
  next=((CB_80174320_S_80174320_0_pre *)point)[-1].unk_00;
  point=next+0x20;
  if(next==0) break;
  position=((CB_80174320_S_80174320_1 *)next)->unk_08;
  color=((CB_80174320_S_80174320_1 *)next)->unk_0C;
 }
 return 0;
}

/* Fades radial segment colors, emits a particle burst, moves the segments outward, and expires them. */
void create_angular_offset_effect(u8 *effect, s32 *position, s32 effect_param)
{
    s16 state;
    s16 life_left;
    s16 red;
    s16 burst_index;
    s32 division_magic;
    u16 age;
    u8 green;
    u8 blue;

    state = F16(effect, 0x1C);
    switch (state) {
    case 0:
        age = FU16(effect, 0x26) + 1;
        FU16(effect, 0x26) = age;
        if ((s16)age >= F16(effect, 0x2C)) {
            division_magic = 0x2AAA0000;
            if ((s16)age - F16(effect, 0x2C) < 7) {
                division_magic = 0x2AAAAAAB;
                red = (F8(effect, 0) * ((s16)age - F16(effect, 0x2C))) / 6;
                F8(effect, 0x10) = red;
                F8(effect, 0x0C) = red;
                F8(effect, 0x08) = red;
                F8(effect, 0x04) = red;
                green = (F8(effect, 1) * (F16(effect, 0x26) - F16(effect, 0x2C))) / 6;
                F8(effect, 0x11) = green;
                F8(effect, 0x0D) = green;
                F8(effect, 0x09) = green;
                F8(effect, 0x05) = green;
                blue = (F8(effect, 2) * (F16(effect, 0x26) - F16(effect, 0x2C))) / 6;
                F8(effect, 0x12) = blue;
                F8(effect, 0x0E) = blue;
                F8(effect, 0x0A) = blue;
                F8(effect, 0x06) = blue;
            }
        }
        if (F16(effect, 0x26) >= 0x22) {
            FU16(effect, 0x1C) = FU16(effect, 0x1C) + 1;
        }
        break;
    case 1:
        if (F16(effect, 0x2A) < 4) {
            age = FU16(effect, 0x26) + 1;
            FU16(effect, 0x26) = age;
            if ((s16)age + F16(effect, 0x2A) == 0x2D) {
                F8(effect, 0x12) = 0x80;
                F8(effect, 0x0E) = 0x80;
                F8(effect, 0x0A) = 0x80;
                F8(effect, 0x06) = 0x80;
                F8(effect, 0x11) = 0x80;
                F8(effect, 0x0D) = 0x80;
                F8(effect, 0x09) = 0x80;
                F8(effect, 0x05) = 0x80;
                F8(effect, 0x10) = 0x80;
                F8(effect, 0x0C) = 0x80;
                F8(effect, 0x08) = 0x80;
                F8(effect, 0x04) = 0x80;
            } else {
                u8 base_red = F8(effect, 0);
                u8 base_green = F8(effect, 1);
                u8 base_blue = F8(effect, 2);
                F8(effect, 0x10) = base_red;
                F8(effect, 0x0C) = base_red;
                F8(effect, 0x08) = base_red;
                F8(effect, 0x04) = base_red;
                F8(effect, 0x11) = base_green;
                F8(effect, 0x0D) = base_green;
                F8(effect, 0x09) = base_green;
                F8(effect, 0x05) = base_green;
                F8(effect, 0x12) = base_blue;
                F8(effect, 0x0E) = base_blue;
                F8(effect, 0x0A) = base_blue;
                F8(effect, 0x06) = base_blue;
            }
        }

        if (F16(effect, 0x24) < 0x0C) {
            FU16(effect, 0x1C) = FU16(effect, 0x1C) + 1;
            F32(effect, 0x94) = (F16(effect, 0x44) + F16(effect, 0x56)) << 15;
            F32(effect, 0x98) = (F16(effect, 0x46) + F16(effect, 0x58)) << 15;
            F32(effect, 0x9C) = (F16(effect, 0x48) + F16(effect, 0x5A) + 0x40) << 15;
            if (F16(effect, 0x2A) == 0) {
                burst_index = 1;
                do {
                    create_randomized_rotated_effect(effect, position, effect_param, (burst_index << 26) >> 16);
                    burst_index++;
                } while (burst_index < 8);
            }
        }
        break;
    case 2:
        blue = (F8(effect, 0) * F16(effect, 0x24)) / 10;
        F8(effect, 0x12) = blue;
        F8(effect, 0x0E) = blue;
        F8(effect, 0x0A) = blue;
        F8(effect, 0x06) = blue;
        F8(effect, 0x11) = blue;
        F8(effect, 0x0D) = blue;
        F8(effect, 0x09) = blue;
        F8(effect, 0x05) = blue;
        F8(effect, 0x10) = blue;
        F8(effect, 0x0C) = blue;
        F8(effect, 0x08) = blue;
        F8(effect, 0x04) = blue;
        position[0] += F32(effect, 0x94);
        position[1] += F32(effect, 0x98);
        position[2] += F32(effect, 0x9C);
        break;
    }

    life_left = FU16(effect, 0x24) - 1;
    F16(effect, 0x24) = life_left;
    if ((life_left << 16) <= 0) {
        FU16(effect, -2) |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates three bands of eight colored radial segments around the supplied position. */
void create_radial_effect_bands(CB_80174724_S_80C96F24_0 *owner, void *origin, void *entity) {
    u16 band;
    register s32 shade_offset;

    owner->unk_A4 = 0;
    band = 0;

    do {
        s32 band_index;
        s16 segment;

        {

            band_index = (s16)band;
            segment = 0;
        }
        shade_offset = band_index * 0x10;

        do {
            s16 end_radius = 0;
            s16 start_radius = 0;
            s32 last_band;
            void *effect;

            if (band_index == 0) {
                start_radius = 0x18;
            }

            last_band = 2;
            if (band_index == 1) {
                start_radius = 0x18;
                end_radius = 0x18;
            }
            if (band_index == last_band) {
                start_radius = 0;
                end_radius = 0x18;
            }

            effect = allocate_flagged_object_node(0x12);
            if (effect != 0) {
                void *render_state;
                void *effect_data;
                CB_80174724_S_80C96F24_5 *position;
                s16 init_value;
                s16 angle_index;
                s32 start_angle;
                s32 end_angle;

                effect_data = (u8 *)effect + 0x20;

                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_24 = 0x42;
                init_value = 0x17;
                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_26 = 0;
                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_2A = segment;

                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_2C =
                    init_value - ((CB_80174724_S_80C96F24_2 *)owner)->unk_A4;
                ((CB_80174724_S_80C96F24_3 *)effect)->unk_10 = create_angular_offset_effect;
                register_node(effect, advance_boss_command_stream);

                render_state = ((CB_80174724_S_80C96F24_3 *)effect)->unk_0C;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_10 = 0x20;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_14 |= 0x0C;

                {

                    position = ((CB_80174724_S_80C96F24_3 *)effect)->unk_08;
                    position->unk_00 =
                        ((CB_80174724_S_80C96F24_6 *)origin)->unk_00;
                    position->unk_04 =
                        ((CB_80174724_S_80C96F24_6 *)origin)->unk_04;
                    position->unk_08 =
                        ((CB_80174724_S_80C96F24_6 *)origin)->unk_08 + 0x200000;
                }

                render_state = ((CB_80174724_S_80C96F24_3 *)effect)->unk_0C;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_1E = 0x1000;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_1C = 0x1000;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_0E = 0x80;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_0D = 0x80;
                ((CB_80174724_S_80C96F24_4 *)render_state)->unk_0C = 0x80;

                ((CB_80174724_S_80C96F24_3 *)effect)->unk_20 =
                    (rand() & 0x1F) + 0x10 + shade_offset;
                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_01 =
                    (rand() & 0x1F) + 0x10 + shade_offset;
                ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_02 =
                    (rand() & 0x1F) + 0x10 + shade_offset;

                {
                    s32 segment_index = (s16)segment;

                    if ((segment_index == 1) || (segment_index == 6)) {
                        ((CB_80174724_S_80C96F24_3 *)effect)->unk_20 += 0x0A;
                        ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_01 += 0x0A;
                        ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_02 += 0x0A;
                    }
                }
                if (((s16)segment == 2) || ((s16)segment == 5)) {
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_00 += 0x14;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_01 += 0x14;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_02 += 0x14;
                }
                if ((u16)(segment - 3) < 2U) {
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_00 += 0x1E;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_01 += 0x1E;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_02 += 0x1E;
                }

                {
                    u8 *template_data;
                    template_data = D_80175330;
                    *(CB_80174724_Copy12 *)((u8 *)effect_data + 0x7A) = *(CB_80174724_Copy12 *)template_data;
                }

                {
                    s16 end_radius_copy;
                    void *render_data;
                    u32 trig_angle;
                    s32 trig_value;
                    s32 product;

                    angle_index = (s16)segment;
                    end_angle = (angle_index + 1) << 9;
                    trig_angle = end_angle;
                    render_data = effect_data + 0x7A;
                    ((CB_80174724_S_80C96F24_4 *)render_state)->unk_08 = render_data;

                    product = start_radius * rcos(trig_angle);
                    start_angle = angle_index << 9;
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_44 = last_band;
                    product = start_radius * rcos(start_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_4A = last_band;
                    trig_value = rcos(end_angle);
                    end_radius_copy = end_radius;
                    product = end_radius_copy * trig_value;
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_50 = last_band;
                    product = end_radius_copy * rcos(start_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_56 = last_band;
                    product = start_radius * rsin(end_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_46 = last_band;
                    product = start_radius * rsin(start_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_4C = last_band;
                    product = end_radius_copy * rsin(end_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_52 = last_band;
                    product = end_radius_copy * rsin(start_angle);
                    last_band = product >> 12;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_58 = last_band;
                }

                {
                    s32 last_band_z;
                    s16 end_z = 0;
                    s16 start_z = end_z;

                    if (band_index == 0) {
                        start_z = -0x14;
                    }

                    last_band_z = 2;
                    if (band_index == 1) {
                        start_z = -0x2E;
                        end_z = -0x14;
                    }
                    if (band_index == last_band_z) {
                        start_z = -0x42;
                        end_z = -0x2E;
                    }
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_4E = start_z;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_48 = start_z;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_5A = end_z;
                    ((CB_80174724_S_80C96F24_1 *)effect_data)->unk_54 = end_z;
                }
            }

            {
                s32 segment_step;
                u16 effect_count;

                segment++;
                segment_step = segment;
                effect_count = ((CB_80174724_S_80C96F24_7 *)owner)->unk_A4;
                segment_step = segment_step < 8;
                effect_count++;
                ((CB_80174724_S_80C96F24_7 *)owner)->unk_A4 = effect_count;
                if (segment_step) {
                    continue;
                }
                break;
            }
        } while (1);

        {
            s16 next_band;

            next_band = (s16)(band + 1);
            band = (u16)next_band;
            if (next_band >= 3) {
                break;
            }
        }
    } while (1);
}

/* Stops movement and waits for dungeon activity to finish, then clears the callback and counts the new
 * action. */
void wait_actor_activity_then_complete(ActorRecord *state, ObjectPosition *unused_position, SpriteFrameState *unused_render_state, ActorRecord *entity) {
    entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
    state->unk_8C.handler = wait_actor_activity_then_complete;
    state->action_id.u = 0x17;
    state->action_phase.u = 0;
    entity->pending_turn_updates = 0;
    if (!(((CB_80174B3C_S_80174B3C_2 *)(&D_80083460))->unk_02 & 0x2000) && ((has_pending_dungeon_activity(entity) << 0x10) == 0)) {
        state->unk_8C.handler = NULL;
        state->action_id.u = 0x17;
        state->action_phase.u = 0;
        actor_action_reset_value = 0;
        ((CB_80174B3C_S_80174B3C_2 *)(&D_80083460))->unk_0A = (u16) (((CB_80174B3C_S_80174B3C_2 *)(&D_80083460))->unk_0A + 1);
    }
}

/* Advances the transition sprite, then restores the view tint to neutral and removes the effect. */
void finish_sprite_and_restore_tint(u8 *task, void *context, u8 *input)
{
    s16 frames_left;
    GameWork *fade_state = &g_game_work;

    if (task[0x9A] == 0) {
        D_801753AC = *(s32 *)(input + 8);
        advance_sprite_animation_and_textures(input);
        if (*(u16 *)(input + 0x14) & 0xE000) {
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
void replace_actor_with_faded_effect(void *state, EntityRec *position, SpriteFrameState *entity, void *actor) {
    s16 direction;
    u16 fade_ticks;
    u16 finish_ticks;
    u16 previous_ticks;
    u8 status;
    u8 next_state;
    CB_80174D14_S_80C97514_4 *effect_data;
    GameWork *scene_color = &g_game_work;
    CB_80174D14_S_80C97514_7 *render_obj;
    CB_80174D14_S_80C97514_5 *effect;
    void *new_model;
    void *model;

    status = ((CB_80174D14_S_80C97514_0 *)state)->phase;
    switch (status) {
    case 0:
        next_state = ((CB_80174D14_S_80C97514_0 *)state)->phase + 1;
        ((CB_80174D14_S_80C97514_0 *)state)->phase = next_state;
        return;
    case 1:
        run_cd_image_commands(&block_image_commands, &block_image_load_done, 0);
        ((CB_80174D14_S_80C97514_0 *)state)->unk_A4 = 0;
        ((CB_80174D14_S_80C97514_0 *)state)->phase = (u8) (((CB_80174D14_S_80C97514_0 *)state)->phase + 1);
        ((Rec_D_80082E80 *)actor)->unk_8A = (u16) ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v;
    case 2:
        direction = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v + 0x100)
            >> 9) & 7;
        if ((*(u8 *)&block_image_load_done) == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v = (u16) (((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v + 0x200);
            return;
        }

        run_cd_image_commands(&block_image_commands, &block_image_load_done, 1);
        sound_set_cd_cue_parameters(0, cd_cue_base, 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, read_stream_cue_start_offset(), NULL);
        (*(s8 *)&block_effect_load_done) = 0;
        Control_CD(0xFF, &resource_completion_callback_address, &block_effect_load_done);
        select_nearby_target_and_initialize_slot(actor - 0x20, position, 8, 0x300);
        ((CB_80174D14_S_80C97514_0 *)state)->timer = 0x10U;
        ((CB_80174D14_S_80C97514_0 *)state)->phase = (u8) (((CB_80174D14_S_80C97514_0 *)state)->phase + 1);
        create_radial_effect_bands(state, position, entity);
    case 3:
        previous_ticks = ((CB_80174D14_S_80C97514_0 *)state)->timer;
        fade_ticks = previous_ticks - 1;
        ((CB_80174D14_S_80C97514_0 *)state)->timer = fade_ticks;
        if ((fade_ticks << 0x10) <= 0) {
            status = ((CB_80174D14_S_80C97514_2 *)(&block_effect_load_done))->unk_00;
            ((CB_80174D14_S_80C97514_0 *)state)->timer = previous_ticks;
            if (status == 0) {
                return;
            }
            ((CB_80174D14_S_80C97514_0 *)state)->phase = (u8) (((CB_80174D14_S_80C97514_0 *)state)->phase + 1);
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            return;
        }
        effect_data = ((void **)&actor_effect_color_targets)[lookup_masked_byte_table(actor)];
        scene_color->view.tint.parts.tint_r = (u8) (scene_color->view.tint.parts.tint_r + ((s32) (effect_data->unk_00
            - scene_color->view.tint.parts.tint_r) / (s16) ((CB_80174D14_S_80C97514_0 *)state)->timer));
        scene_color->view.tint.parts.tint_g = (u8) (scene_color->view.tint.parts.tint_g + ((s32) (effect_data->unk_01
            - scene_color->view.tint.parts.tint_g) / (s16) ((CB_80174D14_S_80C97514_0 *)state)->timer));
        scene_color->view.tint.parts.tint_b = (u8) (scene_color->view.tint.parts.tint_b + ((s32) (effect_data->unk_02
            - scene_color->view.tint.parts.tint_b) / (s16) ((CB_80174D14_S_80C97514_0 *)state)->timer));
        return;
    case 4:
    {
        s32 effect_type;
        s16 effect_index;

        effect = allocate_flagged_object_node(0x12);
        if (effect == NULL) {
            return;
        }
        effect->unk_10 = finish_sprite_and_restore_tint;
        register_node(effect, project_sprite_chain);
        ((CB_80174D14_S_80C97514_0 *)state)->unk_AC = effect;
        ((CB_80174D14_S_80C97514_14 *)(((CB_80174D14_S_80C97514_12 *)effect)->unk_08))->unk_00 = (s32) position->x.v;
        ((CB_80174D14_S_80C97514_14 *)(((CB_80174D14_S_80C97514_12 *)effect)->unk_08))->unk_04 = (s32) position->y.v;
        ((CB_80174D14_S_80C97514_14 *)(((CB_80174D14_S_80C97514_12 *)effect)->unk_08))->unk_08 = (s32) position->z.v;
        render_obj = effect->unk_0C;
        render_obj->unk_1E = 0x1000;
        render_obj->unk_1C = 0x1000;
        render_obj->unk_0C.s = 0x808080;
        effect_type = lookup_masked_byte_table(actor) - 1;
        effect_index = effect_type;
        if ((effect_type << 0x10) < 0) {
            effect_index = rand() % 3;
        }
        effect_data = (void *)(*((s32 *)&D_80175318 + (s16) effect_index) + (u8 *)&dungeon_resource_buffer);
        select_record_entry_and_value(render_obj, effect_data, 0);
        entity->flags = (u16) (entity->flags | 0x80);
        ((CB_80174D14_S_80C97514_0 *)state)->timer = 0U;
        next_state = ((CB_80174D14_S_80C97514_0 *)state)->phase + 1;
        ((CB_80174D14_S_80C97514_0 *)state)->phase = next_state;
        return;
    }
    case 5:
        render_obj = ((CB_80174D14_S_80C97514_0 *)state)->unk_AC;
        render_obj = render_obj->unk_0C.u;
        if (render_obj->unk_14 & 0xE000) {
            ((CB_80174D14_S_80C97514_0 *)state)->phase = (u8) (((CB_80174D14_S_80C97514_0 *)state)->phase + 1);
        }
    case 6:
        if (((CB_80174D14_S_80C97514_0 *)state)->phase != 6) {
            return;
        }
        if (create_status_linked_render_effect(position, D_801753AC, D_80175314, &staged_spawn_count) == 0) {
            return;
        }
        ((CB_80174D14_S_80C97514_0 *)state)->timer = 0x10U;
        ((CB_80174D14_S_80C97514_0 *)state)->phase = (u8) (((CB_80174D14_S_80C97514_0 *)state)->phase + 1);
        decrement_monster_entry_count(((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v, 3);
        update_map_cell_flags_with_item_limit(entity->tile_x, entity->tile_y, 0x300);
        unlink_entity_node(actor);
        render_obj = actor - 0x20;
        render_obj->unk_10 = (s32) (render_obj->unk_10 | 0x80000000);
        return;
    case 7:
        new_model = advance_staged_entity_load(entity, actor);
        ((Rec_D_80082E80 *)actor)->unk_60.as_pv = new_model;
        if (new_model == NULL) {
            return;
        }
        ((CB_80174D14_S_80C97514_0 *)state)->timer = 0x10U;
        ((CB_80174D14_S_80C97514_0 *)state)->phase = (u8) (((CB_80174D14_S_80C97514_0 *)state)->phase + 1);
        ((CB_80174D14_S_80C97514_15 *)(((Rec_D_80082E80 *)actor)->unk_60.as_pv))->unk_2A =
            (u16) ((Rec_D_80082E80 *)actor)->unk_28.at02_u16.v;
        model = ((Rec_D_80082E80 *)actor)->unk_60.as_pv;
        render_obj = ((CB_80174D14_S_80C97514_9_pre *)model)[-1].unk_00;
        select_indirect_table_entry(render_obj, render_obj->unk_2C[((s32) (g_game_work.view.camera_rotation.parts.viewAngle
            + (s16) ((CB_80174D14_S_80C97514_9 *)model)->unk_2A + 0x100) >> 9) & 7], render_obj->unk_04);
        render_obj->unk_14 = (u16) (render_obj->unk_14 & 0xFFFE);
    case 8:
        finish_ticks = ((CB_80174D14_S_80C97514_0 *)state)->timer - 1;
        ((CB_80174D14_S_80C97514_0 *)state)->timer = finish_ticks;
        if ((finish_ticks << 0x10) > 0) {
            return;
        }
        ((CB_80174D14_S_80C97514_15 *)(((Rec_D_80082E80 *)actor)->unk_60.as_pv))->unk_2A = (u16) ((Rec_D_80082E80 *)actor)->unk_8A;
        ((CB_80174D14_S_80C97514_0_pre *)state)[-1].unk_00 = (u16) (((CB_80174D14_S_80C97514_0_pre *)state)[-1].unk_00 | 0x8000);
        (*(s32 *)&object_flag_block.flags) = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        ((Rec_D_80082E80 *)actor)->unk_6D = 0;
        return;
    }
}

/*
 * Runs resolve_actor_floor_trap_once and installs dispatch_actor_turn_and_motion when it returns
 * positive.
 */
void resume_actor_after_floor_trap(ActorRecord *state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *entity) {
 if(resolve_actor_floor_trap_once(state,position,sprite,entity) > 0)
  state->unk_8C.handler=dispatch_actor_turn_and_motion;
}

/*
 * Runs propagate_actor_action_flag and installs dispatch_actor_turn_and_motion when it returns
 * nonzero.
 */
void resume_actor_after_action_flag(ActorRecord *state, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *entity) {
 if(propagate_actor_action_flag(state,position,sprite,entity) != 0)
  state->unk_8C.handler=dispatch_actor_turn_and_motion;
}
