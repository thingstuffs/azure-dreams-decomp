#ifndef ENGINE_MESSAGE_H
#define ENGINE_MESSAGE_H
/* Prototypes of the functions defined in src/engine/message/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "engine/object/runtime_linked_node.h"
#include "sdk/libgpu_types.h"
#include "records/Rec_func_800384A8_arg0.h"

typedef struct ScriptController ScriptController;
typedef struct MessageWindow MessageWindow;
typedef s32 (*MessageServiceHandler)(s32, s32, s32, s32);
struct MessageVoiceState;
s32 check_state_or_global_flags(struct MessageVoiceState *state);

typedef void (*MessageWindowHandler)(MessageWindow *);

typedef struct ScriptReturnStack {
    u8 *addresses[16];
    u8 **next;
} ScriptReturnStack;

struct MessageWindow {
    RECT texture_rect;
    s16 x_offset;
    s16 scroll_offset;
    s16 width;
    s16 height;
    MessageWindowHandler message_handler;
    u8 pad14[4];
    s16 countdown;
    u8 pad1A[2];
    u8 *cursor;
    s16 column;
    s16 row;
    u8 column_count;
    u8 row_count;
    u8 pad26[2];
    s8 text_speed;
    u8 pad29;
    u8 spacing;
    u8 pad2B[3];
    u8 text_advance_mode;
    u8 entry_index;
    u8 pad30[2];
    s8 service_index;
    s8 service_entry;
    u32 service_value;
    u8 pad38[4];
    ScriptReturnStack returns;
    ScriptController *controller;
    u8 pad84;
    s8 active;
    u8 field86;
    s8 skip_disabled;
    u8 pad88;
    s8 motion_timer;
};

struct ScriptController {
    u8 reset_requested;
    u8 camera_target_slot;
    u8 mode;
    s8 text_speed;
    s8 previous_text_speed;
    u8 pad05[3];
    RuntimeLinkedNode object_list;
    u8 decimal_text[21]; /* Ten fullwidth digits and the terminator. */
    u8 pad29[0x0B];
    u8 *pending_script;
    u8 *script_start;
    u8 cd_cue_param;
    u8 field3D;
    u8 pad3E[2];
    MessageServiceHandler *service_handlers;
    void **variable_addresses;
    s32 variables[16];
    u8 *default_script;
    MessageWindow window;
};

typedef struct MessageWindowLinks {
    MessageWindow *window;
    ScriptController *controller;
} MessageWindowLinks;

struct S_80038394_0;
struct S_80038478_0;
struct S_80038588_0;
struct S_800385E8_0;
struct S_80038648_0;
struct S_80038708_0;
struct S_800389B4_0;
struct S_80042BDC;

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
void choose_message_wait_handler(MessageWindow *window);

/* decrement_countdown_and_switch.c */
void decrement_countdown_and_switch(MessageWindow *window);

/* decrement_countdown_and_switch_b.c */
void decrement_countdown_and_switch_b(MessageWindow *window);

/* end_status_effect_message.c */
void end_status_effect_message(struct S_80042BDC *ent, s16 action);

/* entry_ms_mot_accpt_ow.c */
s32 accept_message_motion_request(s32 entry_value, s32 first_value, s32 second_value, s32 packed_index);

/* entry_sd_call.c */
s32 play_message_confirmation_sound(s32 mode);

/* finish_message_when_idle.c */
void finish_message_when_idle(MessageWindow *window);

/* init_message_countdown.c */
void start_message_countdown(MessageWindow *window);

/* init_message_window.c */
void init_message_window(ScriptController *controller, u8 mode);

/* mes_skip_disable_set.c */
void mes_skip_disable_set(s8 skip_disabled);

/* ms_mot_accpt_ow.c */
void *ms_mot_accpt_ow(u8 object_index);

/* play_message_advance_sound.c */
void play_message_advance_sound(Rec_func_800384A8_arg0 *state);

/* process_message_control_bytes.c */
void process_message_control_bytes(MessageWindow *window);

/* render_message_glyphs.c */
void render_message_glyphs(MessageWindow *window);

/* run_message_opcode_handler.c */
void run_message_opcode_handler(MessageWindow *window);

/* run_message_table_handler.c */
void run_message_table_handler(MessageWindow *window);

/* run_indexed_handler_and_set_next.c */
void run_indexed_handler_and_set_next(struct S_80038708_0 *record);

/* scroll_message_rows.c */
void scroll_message_rows(MessageWindow *window);

/* select_message_wait_handler.c */
MessageWindowHandler select_message_wait_handler(MessageWindow *window);

/* sync_message_window_data.c */
void sync_message_window_data(MessageWindow *window);

/* sync_message_window_state.c */
void sync_message_window_state(MessageWindowLinks *links);

/* update_message_window.c */
void update_message_window(MessageWindow *window);

/* update_text_row_scale.c */
void update_text_row_scale(ScriptController *controller, u8 unused_scale);

/* wait_message_countdown.c */
void wait_message_countdown(MessageWindow *window);

/* wait_message_entry_ready.c */
void wait_message_entry_ready(MessageWindow *window);

/* wait_message_motion_accept.c */
void wait_message_motion_accept(MessageWindow *window);

/* wait_message_resident_bit.c */
void wait_message_resident_bit(struct S_80038394_0 *object);

/* wait_message_voice_busy.c */
void wait_message_voice_busy(Rec_func_800384A8_arg0 *state);

/* wait_message_voice_idle.c */
void wait_message_voice_idle(Rec_func_800384A8_arg0 *object);

/* Data declarations. */
extern MessageWindow *current_message_window_state;

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
void read_message_byte(MessageWindow *window);

#endif
