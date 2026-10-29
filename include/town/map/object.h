#ifndef TOWN_MAP_OBJECT_H
#define TOWN_MAP_OBJECT_H
/* Prototypes of the functions defined in src/town/map/object/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

struct S_8008BA44_0;
struct S_800A54FC_0;
struct S_800BB798_0;
struct S_func_800BB508_0;
struct TownCameraState;
struct TownCourseActor;
struct TownPropPosition;

/* allocate_first_object_variant.c */
void allocate_first_object_variant(void);

/* allocate_object_with_data_pointer.c */
void allocate_object_with_data_pointer(void);

/* check_building_entity_compatibility.c */
s32 check_building_entity_compatibility(s32 record_id, s32 entity_id);

/* clear_object_link_and_mark_complete_g01169.c */
void clear_object_link_and_mark_complete(struct S_func_800BB508_0 *object, void *context);
void advance_object_state_angle(void *object, void *context, void *state);
void initialize_object_appearance_with_delay(void *object, void *context, void *state);
void clear_object_link_and_complete(void *object, void *value);
void set_handler_variant_b_with_counter_30(void *object, void *context, void *state);
void init_object_with_countdown(void *object, void *context, void *state);
void set_handler_variant_b_with_counter_14(void *object, void *context, void *state);

/* copy_entity_record_fields.c */
void copy_entity_record_fields(ObjectPosition *destination, ObjectPosition *source);

/* create_object_from_polar_spawn_data.c */
s32 create_object_from_polar_spawn_data(struct S_800BB798_0 *spawn_data, s16 state_48, s16 state_4a);

/* create_object_from_three_values.c */
s32 create_object_from_three_values(s32 *values);

/* create_positioned_graphic_object.c */
void *create_positioned_graphic_object_2(struct TownPropPosition *position, s32 object_param, s32 graphics_id);

/* create_positioned_visual_object.c */
void *create_positioned_visual_object(struct TownPropPosition *source_pos, s32 object_data, s32 angle, s32 visual_data);

/* deactivate_object_triggered.c */
void deactivate_object_triggered(void *object, void *position, void *rotation);

/* decrease_town_map_object_field_and_transition.c */
void decrease_town_map_object_field_0a_and_transition(struct S_8008BA44_0 *obj);

/* initialize_object_rendering_resources.c */
void initialize_object_rendering_resources(struct TownCourseActor *object_data, void *unused, SpriteFrameState *render_data);

/* initialize_object_when_inactive.c */
void initialize_object_when_inactive(struct S_800A54FC_0 *object, s32 value_1, s32 value_2, s32 value_3);

/* initialize_object_with_default_data.c */
void initialize_object_with_default_data(void *object, void *init_arg, SpriteFrameState *state);

/* select_object_value_with_idle_fallback.c */
void select_object_value_with_idle_fallback(struct TownCameraState *object);

/* set_object_callback_when_active.c */
void set_object_callback_when_active(struct TownCameraState *object);

#endif
