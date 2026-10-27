#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H
/* Prototypes of the functions defined in src/engine/camera/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_8004D45C_Src;
struct S_8004D75C;

/* advance_three_component_interpolation.c */
void initialize_three_component_interpolation(void *state_data, u16 *target, s32 duration, u16 *values);

/* copy_camera_rotation.c */
void copy_camera_rotation(void);

/* lookup_byte_by_key.c */
s32 map_fullwidth_character_to_glyph_byte(s32 char_code);

/* move_view_record.c */
void move_view_record(struct S_8004D75C *dst, struct S_8004D75C *src);

/* queue_view_slot.c */
void queue_view_slot(int slot_selector);

/* restore_view_slot.c */
void restore_view_slot(void *record_selector);

/* run_view_callbacks.c */
void run_view_callbacks(void);

/* run_view_slot_callback.c */
void run_view_slot_callback(void (**callback_slot)(void *), s32 *poll_enabled, void *poll_context);

/* set_camera_targets.c */
void set_camera_targets(void *target_position, void *target_rotation, u16 transition_param);

/* set_camera_targets_packed.c */
s32 set_camera_targets_packed(struct S_8004D45C_Src *source, void *forwarded_ptr, u32 value, s32 forwarded_value);

/* state_defaults.c */
void reset_camera_transition_fields(void);

/* update_shoulder_button_angle.c */
int func_8003D92C(void);
int update_shoulder_button_angle(void);

/* Data declarations. */
extern s32 camera_default_origin_tail;
extern s32 camera_default_origin_xy;
extern s32 camera_default_rotation_tail;
extern s32 camera_default_rotation_xy;
extern short camera_shoulder_hold_ticks;
extern short camera_shoulder_repeat_latch;

#endif
