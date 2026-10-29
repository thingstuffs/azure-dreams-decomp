#ifndef TOWN_EVENT_STATE_H
#define TOWN_EVENT_STATE_H
/* Prototypes of the functions defined in src/town/event/state/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"

struct S_8009C46C_0;
struct S_8009C4E8_2;
struct SpriteFrameState;

/* initialize_object_state_from_selector.c */
void initialize_object_state_from_selector(void *context, void *selector, SpriteFrameState *state);

/* initialize_optional_object_state.c */
void initialize_optional_object_state(void *object, void *context, void *state, void *init_value);

/* initialize_record_pointers_and_clear_state.c */
void initialize_record_pointers_and_clear_state(void *record_data, void *placement, struct SpriteFrameState *unused_sprite);

/* initialize_variant_record_pointers_and_clear_state.c */
void initialize_variant_record_pointers_and_clear_state(void *record_data, void *placement, struct SpriteFrameState *unused_sprite);

/* select_object_state_by_mode.c */
void select_object_state_by_mode(Rec_D_800CFCB4 *record, void *context, SpriteFrameState *state, void *default_value, void *alternate_value, void *update_value);

/* set_actor_drop_state.c */
void set_actor_drop_state(Rec_func_80094268_arg0 *object, Rec_D_800CFCB4 *state);

/* spawn_and_flag_object_parts_g01128.c */
void spawn_and_flag_object_parts(unsigned short *object, s32 unused, s32 action_id);
void unlink_and_remove_scene_object(void *object);
void *create_town_effect_object(s32 parent, IntVector3 *position, s32 object_value, s32 state_value);
void run_object_secondary_callback(struct S_8009C46C_0 *object, void *motion, void *context);
void update_timed_object_to_height_limit(void *object, ObjectPosition *motion, struct S_8009C4E8_2 *appearance);
void fade_object_primitive(void *object, void *unusedContext, u8 *primitive);
void spawn_randomized_effect_parts(u8 *source_data, s32 spawn_arg);

#endif
