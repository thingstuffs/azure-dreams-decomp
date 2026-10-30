#ifndef DUNGEON_MONSTER_BELDO_LARGE_H
#define DUNGEON_MONSTER_BELDO_LARGE_H

/* Function contracts owned by src/dungeon/monster/beldo_large/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
extern ObjectNodeHeader *beldo_camera_object;

extern ObjectNodeHeader *D_80175D64;

/* Both the constructor and phase loop visit sixteen node slots. */
extern ObjectNodeHeader *D_80175D78[16];

extern ObjectNodeHeader *encounter_offset_object;

void create_multi_form_segment_ring(EntityRec *origin);
void advance_linked_actor_motion_script(ActorRecord *state_in, ObjectPosition *motion_in, struct SpriteFrameState *sprite_in);




void update_actor_callbacks_and_motion(void *owner_arg, ObjectPosition *motion, SpriteFrameState *data);
void update_vertical_motion_and_effect(void *motion, ObjectPosition *position, void *effect);
void *prepare_encounter_resource_descriptor(s32 input_value);
void register_encounter_cd_callbacks(s32 input_value);

/* Callback entry points. */
void advance_timed_blink_effect(void *state_data, void *unused, void *color_data);
void darken_encounter_view_color(u16 *entry);
void update_dungeon_actor_behavior(void *effect);
void create_timed_offset_motion_effect(u8 *unused, s16 duration, s32 offset_x, s32 offset_y, s32 offset_z);
void start_actor_directional_action(Rec_func_800A9E70_arg0 *state, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *actor);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct BeldoMoveState;
void advance_actor_movement_step(struct BeldoMoveState *movement_in, ObjectPosition *action_ctx, SpriteFrameState *position, ActorRecord *actor);
void emit_multi_form_ring_geometry(void *animation, s32 *origin, void *color);
void initialize_action_offset_and_notify(void *action, void *position);
void update_multi_form_actor_control(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);
void upload_encounter_texture(void);

void complete_actor_facing_action(Rec_func_800A9E70_arg0 *entity, ObjectPosition *unused_1, s32 unused_2, ActorRecord *target);
void create_player_centered_sequence_effect(void);
s32 try_actor_attack(ActorRecord *action_state, ObjectPosition *action_id, SpriteFrameState *target, ActorRecord *actor);

#endif
