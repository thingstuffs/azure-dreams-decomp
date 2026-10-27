#ifndef ENGINE_MESSAGE_H
#define ENGINE_MESSAGE_H
/* Prototypes of the functions defined in src/engine/message/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"
#include "records/Rec_func_800384A8_arg0.h"

struct MessageVoiceState;
s32 check_state_or_global_flags(struct MessageVoiceState *state);

struct AnimObject;
struct Func80037F70Outer;
struct Func8003800CState;
struct Func80038A10State;
struct Object;
struct RuntimeContext;
struct S_800381A4_0;
struct S_80038288_0;
struct S_8003832C_0;
struct S_80038368_0;
struct S_80038394_0;
struct S_80038478_0;
struct S_80038588_0;
struct S_800385E8_0;
struct S_80038648_0;
struct S_80038708_0;
struct S_800389B4_0;
struct S_80042BDC;
struct S_func_80038CB8_0;

/* advance_message_on_confirm_flag.c */
void advance_message_on_confirm_flag(struct S_80038588_0 *object);

/* advance_message_on_flag.c */
void advance_message_on_flag(struct S_80038478_0 *object);

/* advance_message_on_input_flag.c */
void advance_message_on_input_flag(struct S_800385E8_0 *object);

/* advance_message_on_ready_flag.c */
void advance_message_on_ready_flag(struct S_80038648_0 *object);

/* advance_message_when_voice_idle.c */
void advance_message_when_voice_idle(struct S_800389B4_0 *context);

/* choose_message_wait_handler.c */
void choose_message_wait_handler(struct S_80038288_0 *context);

/* decrement_countdown_and_switch.c */
void decrement_countdown_and_switch(struct S_800381A4_0 *state);

/* decrement_countdown_and_switch_b.c */
void decrement_countdown_and_switch_b(struct S_80038368_0 *state);

/* end_status_effect_message.c */
void end_status_effect_message(struct S_80042BDC *ent, s16 action);
void func_80042BDC(struct S_80042BDC *ent, s16 action);

/* entry_ms_mot_accpt_ow.c */
s32 accept_message_motion_request(s32 entry_value, s32 first_value, s32 second_value, s32 packed_index);

/* entry_sd_call.c */
s32 play_message_confirmation_sound(s32 mode);

/* finish_message_when_idle.c */
void finish_message_when_idle(struct S_8003832C_0 *handler_arg);

/* init_message_countdown.c */
void consume_message_byte_and_start_countdown(struct S_8003832C_0 *context);

/* mes_skip_disable_set.c */
void mes_skip_disable_set(s8 skip_disabled);

/* ms_mot_accpt_ow.c */
void *ms_mot_accpt_ow(u8 object_index);

/* play_message_advance_sound.c */
void play_message_advance_sound(Rec_func_800384A8_arg0 *state);

/* process_message_control_bytes.c */
void process_message_control_bytes(struct RuntimeContext *ctx);

/* render_message_glyphs.c */
void func_80038CB8(struct S_func_80038CB8_0 *text);
void render_message_glyphs(struct S_func_80038CB8_0 *text);

/* run_indexed_handler_and_set_next.c */
void run_indexed_handler_and_set_next(struct S_80038708_0 *record);

/* scroll_message_rows.c */
void scroll_message_rows(struct AnimObject *anim);

/* select_message_wait_handler.c */
s32 *func_800381D0(Rec_func_800381D0_arg0 *context);
s32 *select_message_wait_handler(Rec_func_800381D0_arg0 *context);

/* sync_message_window_data.c */
void sync_message_window_data(struct Func8003800CState *state);

/* sync_message_window_state.c */
void sync_message_window_state(struct Func80037F70Outer *context);

/* update_message_window.c */
void func_80038A10(struct Func80038A10State *input_state);
void update_message_window(struct Func80038A10State *input_state);

/* update_text_row_scale.c */
void update_text_row_scale(u8 *entity);

/* wait_message_entry_ready.c */
void wait_message_entry_ready(struct Object *object);

/* wait_message_resident_bit.c */
void wait_message_resident_bit(struct S_80038394_0 *object);

/* wait_message_voice_busy.c */
void wait_message_voice_busy(Rec_func_800384A8_arg0 *state);

/* wait_message_voice_idle.c */
void wait_message_voice_idle(Rec_func_800384A8_arg0 *object);

/* Data declarations. */
extern struct Func80038A10State *current_message_window_state;

#endif
