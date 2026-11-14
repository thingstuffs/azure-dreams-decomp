#ifndef TOWN_MAP_OBJECT_H
#define TOWN_MAP_OBJECT_H
/* Prototypes of the functions defined in src/town/map/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"

struct S_8008BA44_0;
struct S_800A54FC_0;
struct S_800BB798_0;
struct S_func_800BB508_0;
struct TownCameraState;
struct TownCourseActor;
struct TownPropPosition;
struct ObjectNodeHeader;

/* create_map_cursor_input_object.c */
void create_map_cursor_input_object(void);

/* create_idle_map_object.c */
void create_idle_map_object(void);

/* check_building_entity_compatibility.c */
s32 check_building_entity_compatibility(s32 record_id, s32 entity_id);

/* clear_object_link_and_mark_complete_g01169.c */
void retire_object_when_out_of_bounds(struct S_func_800BB508_0 *object, void *context);
void update_spinning_object(void *object, void *context, SpriteFrameState *state);
void init_spinning_object_long_delay(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *state);
void update_static_object(void *object, void *value);
void init_static_object_long_delay(void *object, void *context, void *state);
void init_spinning_object_short_delay(TownObjectRecord *object, ObjectPosition *context, SpriteFrameState *state);
void init_static_object_short_delay(void *object, void *context, void *state);

/* copy_object_position_and_velocity.c */
void copy_object_position_and_velocity(ObjectPosition *destination, ObjectPosition *source);

/* create_short_lived_spawner.c */
s32 create_short_lived_spawner(struct S_800BB798_0 *spawn_data, s16 state_48, s16 state_4a);

/* create_burst_particle_spawner.c */
s32 create_burst_particle_spawner(s32 *values);

/* create_positioned_graphic_object.c */
void *create_town_prop_graphic_object(struct TownPropPosition *position, s32 object_param, s32 graphics_id);

/* create_positioned_visual_object.c */
void *create_positioned_visual_object(struct TownPropPosition *source_pos, s32 object_data, s32 angle, s32 visual_data);

/* update_player_spun_object.c */
void update_player_spun_object(void *object, ObjectPosition *position, SpriteFrameState *rotation);

/* decrease_town_map_object_field_and_transition.c */
void lower_town_map_object_value_to_input(struct S_8008BA44_0 *obj);

/* init_minigame_player_actor.c */
void init_minigame_player_actor(struct TownCourseActor *object_data, void *unused, SpriteFrameState *render_data);

/* select_title_handler_when_script_idle.c */
void select_title_handler_when_script_idle(struct S_800A54FC_0 *object, struct ObjectNodeHeader *value_1, s32 value_2, s32 value_3);

/* init_default_sprite_object.c */
void init_default_sprite_object(void *object, ObjectPosition *init_arg, SpriteFrameState *state);

/* select_camera_target.c */
void select_camera_target(struct TownCameraState *object);

/* enable_camera_target_selection.c */
void enable_camera_target_selection(struct TownCameraState *object);

#endif
