#ifndef DUNGEON_H
#define DUNGEON_H
/* Prototypes of the functions defined in src/dungeon/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct ActionState;
struct ActorMotion;
struct PairAction;
struct S_800C9F34_3;

/* func_8009A590.c */
s16 set_item_w0(s32 start_x, s32 start_y, s32 end_x, s32 end_y);

/* func_800A46D8.c */
s32 uses_direct_actor_sprite_frames(void *record);

/* func_800A4F54.c */
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);

/* func_800A4FF4.c */
void apply_actor_delta_and_cap_value(s32 unused_0, s32 unused_1, s32 unused_2, u8 *record);

/* func_800C47D4.c */
void dispatch_actor_behavior_state(ActorRecord *actor_state, s32 context, struct S_800C9F34_3 *position, ActorRecord *entity);

/* func_800C497C.c */
void advance_actor_along_path_points(void *motion, s32 unused, void *position, void *path);

/* func_800D7364.c */
void initialize_nine_entry_links(void *entry_data, s32 enable_flag);

/* func_800D7484.c */
s32 run_object_setup_and_finalize(s32 *value_ptr, s32 context);

/* func_80F908F4.c */
void begin_actor_hit_reaction_slot_f(void *work, void *part_a, void *part_b, EntityRec *actor);

/* func_80F90A60.c */
void update_actor_timed_visual_slot_f(ActorRecord *state_input, ObjectPosition *motion_input, SpriteFrameState *animation_input, ActorRecord *actor_input);

/* func_80FE16A8.c */
void update_dungeon_entity_action_and_facing(struct ActionState *actor, void *context, SpriteFrameState *sprite, ActorRecord *entity);

/* func_8100E664.c */
void restore_bank_actor_callback(struct PairAction *actor, struct ActorMotion *motion, SpriteFrameState *sprite, void *entity);

/* func_8127E460.c */
void reset_state_occupied_entries(void);

/* func_81328A1C.c */
void empty_reserved_callback(void);

/* func_81329928.c */
void empty_reserved_callback_alt(void);

/* func_8184A800.c */
void func_8184A800(void *owner, void *unused, SpriteFrameState *target);

#endif
