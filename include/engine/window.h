#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H
/* Prototypes of the functions defined in src/engine/window/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_D_80081FDC.h"
#include "records/Rec_func_80036210_arg0.h"

struct Container;
struct CursorState;
struct Func37534State;
struct Func800359FCEvent;
struct Func800359FCState;
struct Func80035AF8State;
struct Func80035BE0State;
struct Func80035C80Object;
struct Func80037C7CState;
struct Object;
struct RuntimeObject;
struct S_800355EC_0;
struct S_80035614_0;
struct S_8003566C_0;
struct S_8003571C_0;
struct S_80035760_0;
struct S_800357B0_0;
struct S_800357D0_0;
struct Rec_func_80036210_arg0;
struct S_80036110_0;
struct S_8003626C_0;
struct S_800362A0_0;
struct S_80036434_0;
struct S_80036484_0;
struct S_800364BC_0;
struct S_8003661C_0;
struct S_80036880_0;
struct S_80036900;
struct S_8004A24C_0;
struct S_8004A330_Entity;
struct S_func_80035484_4;
struct S_func_80035484_5;
struct S_func_800362D0_0;
struct S_func_8003666C_0;
struct S_func_800368D0_0;
struct Source;

/* advance_cursor_extent.c */
void advance_cursor_extent(struct S_80036900 *state);

/* cleanup_window_object.c */
void cleanup_window_object(void *record);

/* confirm_list_menu_choice.c */
void confirm_list_menu_choice(struct S_80036880_0 *object);

/* confirm_menu_choice.c */
void confirm_menu_choice(struct S_80036434_0 *object);

/* confirm_timed_menu_choice.c */
void confirm_timed_menu_choice(struct S_8003661C_0 *object);

/* copy_window_params.c */
void copy_window_params(struct Container *container, struct Source *source);
void func_800375C0(struct Container *container, struct Source *source);

/* create_blinking_cursor_object.c */
void create_blinking_cursor_object(s32 node_addr, Rec_D_80081FDC *record, s32 *config, s16 initial_mode, s32 initial_value, s32 setup_id);

/* create_cursor_object.c */
void create_cursor_object(s32 task_buffer, Rec_D_80081FDC *record, s32 *source, s16 state_value, s32 setup_arg);

/* create_default_window_object.c */
void create_default_window_object(s32 value);
void func_80034F58(s32 value);

/* create_runtime_task.c */
void initialize_message_window_runtime_task(void);

/* create_window_object.c */
void create_window_object(s32 object_addr, struct S_func_80035484_4 *model, struct S_func_80035484_5 *config);
void func_80035484(s32 object_addr, struct S_func_80035484_4 *model, struct S_func_80035484_5 *config);

/* create_window_overlay_object.c */
void create_window_overlay_object(s32 node_addr, void *display, u8 *image, s32 *state_ref, s32 option, u8 *owner);

/* entry_copy_window_offset_rectangle.c */
void select_menu_initializer_from_message_handler(void *object);

/* entry_runtime_reset_state_on_trigger_bits.c */
void create_window_cursor_and_install_reset(Rec_func_80036210_arg0 *object);

/* entry_sd_call.c */
void handle_wrapping_menu_cursor_input(struct CursorState *cursor, s32 action_arg1, s32 action_arg2);

/* grow_window_extent.c */
void display_sound_selection_and_prepare_playback(struct Func80035AF8State *state);

/* init_cursor_color_object.c */
void init_cursor_color_object(void *object, void *model, s32 *data, s16 index, s16 table_index, s32 list);

/* init_cursor_display_object.c */
void init_cursor_display_object(void *object, void *display, s32 *data, s16 data_index, s16 table_offset, s32 list_head);

/* init_cursor_sprite_object.c */
void init_cursor_sprite_object(s32 node_addr, Rec_D_80081FDC *transform, s32 *script_data, s16 cursor_offset, s32 sprite_base, s32 owner);

/* init_menu_choice_object.c */
void init_menu_choice_object(struct S_func_800362D0_0 *object);

/* init_menu_choice_timed.c */
void init_menu_choice_timed(struct Object *object);

/* init_menu_choice_wide.c */
void init_menu_choice_wide(struct S_func_8003666C_0 *state);

/* init_menu_panel.c */
void init_menu_panel(struct S_8004A24C_0 *state, s32 config_id, s32 resource_id, s16 x, s16 y, s32 size);

/* init_window_object.c */
void func_80035614(struct S_80035614_0 *object);
void init_window_object(struct S_80035614_0 *object);

/* invoke_window_object_callback.c */
void invoke_window_object_callback(struct S_800355EC_0 *object, void *context, void *output);

/* mark_menu_slot_used.c */
void mark_menu_slot_used(struct S_func_800368D0_0 *state);

/* mark_state_when_flag_50_set.c */
void runtime_mark_state_when_flag_50_set(struct S_800362A0_0 *state);

/* mark_state_when_flag_51_set.c */
void runtime_mark_state_when_flag_51_set(struct S_800364BC_0 *state);

/* queue_unwindowed_texture_draw_mode.c */
void queue_unwindowed_texture_draw_mode(s32 ot_index);

/* runtime_advance_counter_and_callback.c */
void runtime_advance_counter_and_callback(struct S_800357D0_0 *state);

/* runtime_assign_code_callback.c */
void runtime_assign_code_101_callback(struct S_800357B0_0 *object);

/* runtime_decrease_state_by_a.c */
void runtime_decrease_state_by_a_0(struct S_8003571C_0 *object);

/* runtime_decrement_countdown_and_reset.c */
void runtime_decrement_countdown_and_reset(struct S_80036484_0 *state);

/* runtime_reset_state_and_advance_callback.c */
void runtime_reset_state_and_advance_callback(struct S_80035760_0 *state);

/* runtime_reset_state_on_trigger_bits.c */
void runtime_reset_state_on_trigger_bits(struct S_8003626C_0 *state);

/* scale_random_to_unsigned_halfword_limit.c */
u32 scale_random_to_unsigned_halfword_limit(s32 limit);

/* scroll_window_x.c */
void scroll_window_x(struct S_8003566C_0 *state);

/* scroll_window_y.c */
void scroll_window_y(struct S_80036110_0 *object);

/* set_user_name_win.c */
void set_user_name_win(s32 window_value);

/* set_window_handler.c */
void func_80035AAC(struct Rec_func_80036210_arg0 *object);
void set_window_handler(struct Rec_func_80036210_arg0 *object);

/* shrink_window_and_signal_linked_record.c */
void dispatch_window_fade_and_update_extents(struct Func800359FCState *state, struct Func800359FCEvent *event, void *callback_data);

/* shrink_window_extent.c */
void fade_and_shrink_window_on_value_change(struct Func80035C80Object *object);

/* unlink_cursor_when_finished.c */
s32 unlink_cursor_when_finished(struct Func37534State *state);

/* update_cursor_blink_colors.c */
void update_cursor_blink_colors(void *state, s32 mode, void *output);

/* update_cursor_callback.c */
void update_cursor_callback(s32 unused_0, s32 unused_1, s32 value);

/* update_menu_choice_timed.c */
void update_menu_choice_timed(struct Object *object);

/* update_two_column_cursor.c */
void handle_two_column_menu_input(struct Object *menu, void *confirm_arg1, void *confirm_arg2);

/* update_window_extents.c */
void update_window_extents(struct Func80037C7CState *state, s32 offset);

/* update_window_state.c */
void update_window_state(struct RuntimeObject *object, s32 handler_arg1, s32 handler_arg2, s32 state);

/* window_create_animated_content_panel.c */
struct S_8004A330_Entity *window_create_animated_content_panel(s32 style_flags, s16 start_x, s16 start_y, s16 target_x, s16 target_y, s16 width, s32 flags, s32 content_id);

/* window_wait_then_play_sound.c */
void activate_delayed_window_resource(struct Func80035BE0State *state);

/* Data declarations. */
extern void *current_window_object;

#endif
