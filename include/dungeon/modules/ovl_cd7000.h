#ifndef INCLUDE_DUNGEON_MODULES_OVL_CD7000_H
#define INCLUDE_DUNGEON_MODULES_OVL_CD7000_H
struct ObjectPosition;
struct SpriteFrameState;
struct GrayFadeSpriteBody;
struct ObjectPosition;
struct ActorRecord;

/* Contracts owned by src/dungeon/modules/ovl_cd7000.c. */
#include "modules/dungeon_ovl_cd7000.h"

void initialize_gray_sprite_copy_slot_a(CL_CD7000_8017087C_Object *object, struct ActorRecord *field60_value, struct ObjectPosition *source_coords);
void update_growing_rotating_fade_slot_a(void *effect, void *unused, SpriteFrameState *visual);
void *spawn_block_slot_a(s16 spawn_flags, s16 tile_x, s16 tile_y, s32 spawn_height);
void update_block_motion_and_facing_slot_a(ActorRecord *entity, struct ObjectPosition *motion, SpriteFrameState *sprite);
void dispatch_block_turn_actions_slot_a(CL_CD7000_8017102C_S_8017102C_0 *state, void *motion, CL_CD7000_8017102C_S_8017102C_2 *sprite, CL_CD7000_8017102C_S_8017102C_1 *actor);
void advance_block_path_slot_a(void *motion, s32 update_param, void *entity, void *state);
void begin_block_hop_slot_a(ActorRecord *state, void *unused_position, CL_CD7000_80171F58_S_80171F58_1 *render_state, ActorRecord *entity);
s32 try_begin_block_attack_slot_a(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, void *sprite_arg, ActorRecord *actor);
void begin_block_attack_slot_a(CL_CD7000_80172180_S_80172180_1 *state, s32 position, CL_CD7000_80172180_S_80172180_2 *render_state, void *entity);
s32 check_block_action_ready_slot_a(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg);
void finish_block_tile_move_slot_a(void *state_arg,void *position,void *render_state,void *entity);
void update_block_hop_slot_a(CL_CD7000_80172458_S_80172458_0 *action, ObjectPosition *motion, SpriteFrameState *map_entry, ActorRecord *actor);
void finish_block_linked_motion_slot_a(S_80172944_0 *state,void *position,void *render_state,void *entity);
void update_block_attack_slot_a(CL_CD7000_801729A8_S_801729A8_0 *action, void *motion, SpriteFrameState *sprite, ActorRecord *actor);
void update_block_spell_slot_a(struct ActorRecord *work, struct ObjectPosition *position, struct SpriteFrameState *entity,
    CL_CD7000_80172BCC_S_func_80C953CC_4 *actor);
void update_block_defeat_slot_a(void *state,void *position,void *render_state,void *entity);
void update_block_hop_shrink_slot_a(ActorRecord *state,ObjectPosition *position,SpriteFrameState *render_state,ActorRecord *entity);
void update_block_removal_slot_a(void *state,ObjectPosition *position,SpriteFrameState *render_state,ActorRecord *entity);
void finish_block_hop_grow_slot_a(S_80173364_0 *state,ObjectPosition *position,SpriteFrameState *render_state,ActorRecord *entity);
void update_block_status_animation_slot_a(void *action, void *context, SpriteFrameState *sprite_in, CL_CD7000_8017339C_S_80173D4C_2 *actor_in);
void wait_block_mp_recovery_slot_a(void *actor_in, ObjectPosition *position, SpriteFrameState *target, void *entity_in);
void update_block_parent_motion_slot_a(S_80173A38_0 *state, void *position, SpriteFrameState *sprite, CL_CD7000_80173A38_S_80173A38_2 *actor);
void finish_block_thrown_travel_slot_a(ActorRecord *state,void *position,void *render_state,void *entity);
void finish_block_terrain_move_slot_a(S_80173B64_0 *state,void *position,void *render_state,void *entity);
void finish_block_spinning_fall_slot_a(S_80173B9C_0 *state,void *position,void *render_state,void *entity);
void finish_block_fade_in_slot_a(S_80173BD4_0 *state,void *position,void *render_state,void *entity);
void spin_and_fade_gray_sprite_slot_a(struct GrayFadeSpriteBody *effect, s32 unused, SpriteFrameState *sprite);
void create_gray_fading_sprite_slot_a(void *unused_context, struct ObjectPosition *source_pos, s32 unused_value, s16 scale);
void draw_shaded_effect_quad_slot_a(CL_CD7000_80173E40_S_80173E40_6 *quad, struct ObjectPosition *position, SpriteFrameState *render_info, s16 depth_bias);
s32 draw_linked_effect_quads_slot_a(void *point, struct ObjectPosition *position, SpriteFrameState *color);
void update_flashing_effect_segment_slot_a(u8 *effect, ObjectPosition *position, s32 effect_param);
void create_segmented_effect_rings_slot_a(CL_CD7000_80174724_S_80C96F24_0 *owner, struct ObjectPosition *origin, SpriteFrameState *entity);
void begin_block_action_23_slot_a(S_80174B3C_1 *state, void *unused_position, void *unused_render_state, CL_CD7000_80174B3C_S_80174B3C_0 *entity);
void restore_scene_tint_slot_a(u8 *task, void *context, u8 *input);
void update_block_replacement_slot_a(CL_CD7000_80174D14_S_80C97514_0 *state, struct ObjectPosition *position, SpriteFrameState *entity, ActorRecord *actor);
void finish_block_floor_trap_slot_a(CL_CD7000_8017523C_CallbackState *state,void *position,void *sprite,void *entity);
void finish_block_action_flag_slot_a(CL_CD7000_80175274_CallbackState *state,void *position,void *sprite,void *entity);

#endif
