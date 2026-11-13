#ifndef TOWN_PLAYER_POSITION_HANDLERS_H
#define TOWN_PLAYER_POSITION_HANDLERS_H
struct SpriteFrameState;

/* Position handlers and coordinate queries; private body access views stay opaque. */
struct Func8009AA20Arg0;
struct ObjectPosition;
struct Rec_func_80097D54_arg0;
struct S_80098544_0;
struct S_80098B70_0;
struct S_80098F10_0;
struct SpriteFrameState;
struct Struct_func_8009BDDC_arg0;
struct TownObjectRecord;

void update_actor_and_select_ground_handler(int context, struct ObjectPosition *record, struct SpriteFrameState *action_data);
void update_actor_movement_actions(struct TownObjectRecord *action, struct ObjectPosition *actor, int context);
void update_threshold_countdown_action(void *state, struct ObjectPosition *object, struct SpriteFrameState *context);
void invoke_handler_when_countdown_expires(struct TownObjectRecord *state, struct ObjectPosition *update_ctx, struct SpriteFrameState *handler_ctx);
void accelerate_toward_input_keep_speed(struct ObjectPosition *object);
void set_player_y_and_sync_collision(struct ObjectPosition *record, int initial_value);
void set_player_x_and_sync_collision(struct ObjectPosition *record, int initial_value);
void initialize_object_handler_and_countdown(struct TownObjectRecord *object, struct ObjectPosition *context, void *ptr2);
void advance_coordinates_toward_target(struct S_80098544_0 *state, struct ObjectPosition *position);
void bind_default_data_and_clear_record(struct S_80098B70_0 *object, struct ObjectPosition *forwarded_arg);
void clear_record_and_set_next_handler(struct S_80098F10_0 *object, struct ObjectPosition *setup_arg);
void begin_countdown_initialize_action(struct TownObjectRecord *object, struct ObjectPosition *preparationValue, struct SpriteFrameState *initializationValue);
void advance_timed_script_controller(struct Rec_func_80097D54_arg0 *record, struct ObjectPosition *call_arg_1, struct SpriteFrameState *call_arg_2, int check_arg);
void tick_countdown_or_advance_cursor(struct Func8009AA20Arg0 *countdown_state, struct ObjectPosition *cursor_state, struct SpriteFrameState *context_value);
int query_lower_bound_with_x_offset(struct ObjectPosition *input_pos);
int get_probe_min_result(struct ObjectPosition *input_pos);
short get_probe_max_result(struct ObjectPosition *input);
void initialize_indexed_object_state(struct Struct_func_8009BDDC_arg0 *object, struct ObjectPosition *context, void *ptr2);
void interpolate_actor_height_until_timeout(struct TownObjectRecord *state, struct ObjectPosition *motion, void *context);
void update_threshold_object(void *context, struct ObjectPosition *object, void *update_data);

#endif
