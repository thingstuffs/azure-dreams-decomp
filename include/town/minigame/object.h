#ifndef TOWN_MINIGAME_OBJECT_H
#define TOWN_MINIGAME_OBJECT_H
/* Prototypes of the functions defined in src/town/minigame/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/dungeon_moving_views.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct GymScoreObject;
struct IndicatorChild;
struct S_800BF72C_0;
struct S_800BF72C_1;
struct State8081A3D8;

/* advance_object_bounded_movement_phases.c */
void advance_object_bounded_movement_phases(struct S_800BF72C_0 *object, struct S_800BF72C_1 *position);

/* advance_object_spawning_displays_high.c */
void advance_object_spawning_displays_high(struct State8081A3D8 *controller);

/* apply_minigame_object_tint.c */
void apply_minigame_object_tint(struct IndicatorChild *state, MovingPosition *selected_values, SpriteFrameState *render_state);

/* create_gym_mesh_object.c */
void create_gym_mesh_object(void *source_words, s32 data_value_08, s32 object_value_10, s32 object_value_20);

/* create_scene_object_with_byte_payload.c */
void create_scene_object_with_48_byte_payload(s32 init_value, void *init_data);

/* create_scene_object_with_record_payload.c */
void create_scene_object_with_record_payload(s32 object_value, void *record);

/* decrement_object_counter.c */
void decrement_object_counter(void *entry);

/* fade_linked_object_color.c */
void fade_linked_object_color(void *fade);

/* retire_scene_node_when_linked_value_clears.c */
void retire_scene_node_when_linked_value_clears(void *record);

/* update_gym_score_object.c */
void update_gym_score_object(struct GymScoreObject *obj, ObjectPosition *motion);

/* update_object_movement_proximity_reactions.c */
void update_object_movement_proximity_reactions(void *state_data, void *position_data, void *sprite_data);

#endif
