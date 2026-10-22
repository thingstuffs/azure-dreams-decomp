#ifndef DUNGEON_PLAYER_H
#define DUNGEON_PLAYER_H

/* Function contracts owned by src/dungeon/player/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "records/Rec_func_8008D024_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void begin_actor_turn_toward_target(void *action, void *unused, void *actor, void *motion);
s32 begin_familiar_command_selection(Rec_func_8008D024_arg0 *actor, s32 context, SpriteFrameState *display, s32 target_index, s32 action_mode);
s32 begin_familiar_summoning(void *record, s32 input1, void *pointer_input, s32 value_input);
void begin_player_damage_reaction(void *action, s32 unused, void *sprite, EntityRec *actor);
void begin_player_pickup_animation(u8 *actor, s32 effect_arg, u8 *target, u8 *source);
void begin_player_sleep_action(void *record, s32 unused, void *object, EntityRec *entity);
void begin_player_wait_turn(void *state, s32 mode, void *sprite, EntityRec *entity);
s32 begin_selected_target_level_up(void *actor_state, s32 action_arg, void *sprite, void *target);
s32 begin_target_flagged_action(void *actor, s32 action_arg, s32 unused, void *target);
void begin_wake_nearby_monsters(u8 *state_ptr, s32 value, u8 *target_ptr, u8 *angle_ptr);
void clear_player_linked_action_flags(void);
s32 dispatch_dungeon_category_action(void *actor, void *action, s16 dispatch_mode, s32 handler_param);
s32 reject_forbidden_familiar_recall(s32 entry_index);
void select_state_16_directional_animation(void *entity, void *unused, void *animation, EntityRec *state);
void set_familiar_formation_offset(s32 entry_index, s8 value);
void set_linked_actor_code_and_mirror(s16 object_index, s8 value);
void set_linked_actor_pending_halfword(s32 entry_index, s32 value);
void update_player_height_step(void *actor, ObjectPosition *motion, SpriteFrameState *sprite, EntityRec *model);


#endif
