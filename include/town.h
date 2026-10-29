#ifndef TOWN_H
#define TOWN_H

#include "common.h"


/* func_806D6800.c */
s32 town_table_contains_first_byte_d(s32 target_value);

/* Callback entry points. */
void fade_effect_and_mark_cleanup(void *record, s32 unused, void *effect);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void *set_item_w0(s8 item_byte_0, s8 item_byte_1, s8 item_byte_2, s8 item_byte_3);

#include "records/Rec_func_80094268_arg0.h"
void init_flagged_entity_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_threshold_countdown_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void init_timed_dispatch_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);
void initialize_action_object(s32 **record, void *ptr, void *ptr2);
void initialize_action_object_type_six(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);
void initialize_action_object_with_counter(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value);
s32 input_angle_with_offset(s32 unused, s32 angle_offset);

void init_sound_threshold_action(s32 **record, s32 unused, s32 setup_value);

void init_linked_position_action(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value);

void init_height_interpolation_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context);

void forward_context_request_to_handler_b(void *context, s32 request);
void forward_context_request_to_handler_c(void *context, s32 request);
s32 forward_context_request_to_handler_d(void *context, s32 request);
void forward_context_request_to_handler_e(void *context, s32 request);
void forward_context_request_to_handler_f(void *context, s32 request);
void forward_context_request_to_handler_g(void *context, s32 request);
void set_scene_entry_flag_k(void);

#endif
