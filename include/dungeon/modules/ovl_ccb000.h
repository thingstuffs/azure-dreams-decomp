#ifndef INCLUDE_DUNGEON_MODULES_OVL_CCB000_H
#define INCLUDE_DUNGEON_MODULES_OVL_CCB000_H

/* Contracts owned by src/dungeon/modules/ovl_ccb000.c. */
#include "modules/dungeon_ovl_ccb000.h"

void update_growing_rotating_fade_slot_c(void *effect, void *unused, void *visual);
void *spawn_block_slot_c(s16 spawn_flags, s16 tile_x, s16 tile_y, s32 spawn_height);
void update_block_motion_and_facing_slot_c(void *entity, CL_CCB000_80170C24_S_80170C24_2 *motion, void *monster);
void dispatch_block_turn_actions_slot_c(CL_CCB000_8017102C_S_8017102C_0 *state, void *motion, CL_CCB000_8017102C_S_8017102C_2 *sprite, CL_CCB000_8017102C_S_8017102C_1 *actor);
void advance_block_path_slot_c(void *motion, s32 update_param, void *entity, void *state);
void choose_block_move_slot_c(Rec_func_800A9E70_arg0 *move_data, void *context, TileObject *position_data, ActorRecord *actor_data);
void begin_block_hop_slot_c(CL_CCB000_80171F58_S_80171F58_0 *state, void *unused_position, CL_CCB000_80171F58_S_80171F58_1 *render_state, CL_CCB000_80171F58_S_80171F58_2 *entity);
s32 try_begin_block_attack_slot_c(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, void *sprite_arg, ActorRecord *actor);
void begin_block_attack_slot_c(CL_CCB000_80172180_S_80172180_1 *state, s32 position, CL_CCB000_80172180_S_80172180_2 *render_state, void *entity);
s32 check_block_action_ready_slot_c(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void finish_block_tile_move_slot_c(void *state_arg,void *position,void *render_state,void *entity);
void update_block_hop_slot_c(void *action, ObjectPosition *motion, SpriteFrameState *map_entry, ActorRecord *actor);
void finish_block_linked_motion_slot_c(S_80172944_0 *state,void *position,void *render_state,void *entity);
void update_block_attack_slot_c(void *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_block_spell_slot_c(CL_CCB000_80172BCC_S_func_80C953CC_1 *work, CL_CCB000_80172BCC_S_func_80C953CC_2 *position, CL_CCB000_80172BCC_S_func_80C953CC_3 *entity,
    CL_CCB000_80172BCC_S_func_80C953CC_4 *actor);
void update_block_value_reaction_slot_c(CL_CCB000_801730E0_S_801730E0_0 *state, ObjectPosition *motion, SpriteFrameState *action, EntityRec *entity);
void update_block_defeat_slot_c(void *state,void *position,void *render_state,void *entity);
void update_block_hop_shrink_slot_c(void *state,void *position,void *render_state,void *entity);
void update_block_removal_slot_c(void *state,void *position,void *render_state,void *entity);
void finish_block_hop_grow_slot_c(S_80173364_0 *state,void *position,void *render_state,void *entity);
void update_block_status_animation_slot_c(void *action, void *context, void *sprite_in, void *actor_in);
void wait_block_mp_recovery_slot_c(void *actor_in, ObjectPosition *position, void *target, void *entity_in);
void update_block_parent_motion_slot_c(S_80173A38_0 *state, void *position, CL_CCB000_80173A38_S_80173A38_1 *sprite, CL_CCB000_80173A38_S_80173A38_2 *actor);
void finish_block_thrown_travel_slot_c(S_80173B00_0 *state,void *position,void *render_state,void *entity);
void finish_block_terrain_move_slot_c(S_80173B64_0 *state,void *position,void *render_state,void *entity);
void finish_block_spinning_fall_slot_c(S_80173B9C_0 *state,void *position,void *render_state,void *entity);
void finish_block_fade_in_slot_c(S_80173BD4_0 *state,void *position,void *render_state,void *entity);
void spin_and_fade_gray_sprite_slot_c(void *effect, s32 unused, void *primitive);
void create_gray_fading_sprite_slot_c(void *unused_context, Rec_func_80173CFC_arg1 *source_pos, s32 unused_value, s16 scale);
void draw_shaded_effect_quad_slot_c(void *quad, void *position, void *render_info, s16 depth_bias);
s32 draw_linked_effect_quads_slot_c(void *point, void *position, void *color);
void update_flashing_effect_segment_slot_c(u8 *effect, s32 *position, s32 effect_param);
void create_segmented_effect_rings_slot_c(CL_CCB000_80174724_S_80C96F24_0 *owner, void *origin, void *entity);
void begin_block_action_23_slot_c(S_80174B3C_1 *state, void *unused_position, void *unused_render_state, CL_CCB000_80174B3C_S_80174B3C_0 *entity);
void restore_scene_tint_slot_c(u8 *task, void *context, u8 *input);
void update_block_replacement_slot_c(void *state, EntityRec *position, SpriteFrameState *entity, void *actor);
void finish_block_floor_trap_slot_c(CL_CCB000_8017523C_CallbackState *state,void *position,void *sprite,void *entity);
void finish_block_action_flag_slot_c(CL_CCB000_80175274_CallbackState *state,void *position,void *sprite,void *entity);

#endif
