#ifndef TOWN_EVENT_H
#define TOWN_EVENT_H
/* Prototypes of the functions defined in src/town/event/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"
#include "shared/town_object.h"
#include "records/Rec_D_80082D58.h"

struct S_8009B0EC_0;
struct S_8009B9BC_1;
struct S_800AA044_0;
struct S_800AA044_1;
struct S_func_800AC9AC_0;
struct SpriteFrameState;

/* actor_script_motion_g00549.c */
void update_actor_surface_motion(TownObjectRecord *actor, void *subject, void *motion, SpriteFrameState *context);
void update_actor_slots_and_output(void *state_owner, void *update_target, void *update_context, SpriteFrameState *output);

/* advance_timed_action_handler.c */
void advance_timed_action_handler(struct S_8009B0EC_0 *object);

/* initialize_actor_action_with_default_data.c */
void initialize_actor_action_with_default_data(TownObjectRecord *actor, ObjectPosition *action_id, struct SpriteFrameState *action_state);

/* initialize_actor_action_with_defaults.c */
void initialize_actor_action_with_defaults(void *actor, ObjectPosition *action_id, struct SpriteFrameState *action_state, void *state_data);

/* initialize_object_resource_table.c */
void initialize_object_resource_table(void *object, ObjectPosition *context, SpriteFrameState *state);

/* initialize_object_resource_tables.c */
void initialize_object_resource_tables(TownObjectRecord *object, ObjectPosition *init_arg, SpriteFrameState *state);

/* initialize_object_state_and_position.c */
void initialize_object_state_and_position(void **object, IntVector3 *start_position, void *ptr2);

/* item_query_checks_g01145.c */
s32 find_sentinel_table_value_index(s32 target_value);
s32 test_selected_resident_flag(s32 table_index);
s32 get_query_result_for_check_type(s32 check_type);
s32 check_slot_threshold_or_fallback(s32 slot);
s32 classify_item_check_result(s32 input);
s32 classify_listed_entry_type(u8 *entry);
s32 filter_entry_by_kind(s32 unused, u8 *entry);
s32 get_group_record_table_entry(s32 group_id, void *record);
void increment_query_group_count_capped_at_three(s32 entry_index);
s32 is_expected_movie_state(void);
s32 test_niko_kenkatyu(void);
s32 test_far_kenkatyu(void);
void *find_unflagged_node_by_key(s32 target_key);
void delete_carry_item_and_retry_sound(void);
void *select_response_text(void *source, void *target);

/* mesh_quad_transform_g00591.c */
void narrow_vector_to_svector(struct S_800AA044_0 *dst, struct S_800AA044_1 *src);
void transform_vector(s32 transform, void *vector, void *transformed);
void transform_and_queue_mesh_quads(struct S_func_800AC9AC_0 *mesh, void *transform);

/* no_op_action_callback.c */
void no_op_action_callback(TownObjectRecord *unused_object, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite);

/* noop_hook.c */
void noop_hook(void);

/* resolve_owner_position_and_dispatch.c */
void resolve_owner_position_and_dispatch(Rec_D_80082D58 *object, struct S_8009B9BC_1 *owner, EntityRec *resolved_pos, s32 dispatch_param);

/* target_record_angles_g00590.c */
void queue_two_mesh_quad_sets(void *target, ObjectPosition *setup_data);
void update_positions_from_origin(ObjectPosition *origin);

#endif
