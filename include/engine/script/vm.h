#ifndef ENGINE_SCRIPT_VM_H
#define ENGINE_SCRIPT_VM_H
struct ScriptReader;
/* Prototypes of the functions defined in src/engine/script/vm/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "sdk/libgpu_types.h"
#include "shared/runtime_dispatch.h"

struct FadeManagerBody;
struct ObjectPosition;
struct SpriteFrameState;
struct MessageWindow;
struct ScriptReader;
struct Func80039D48Reader;
struct Func80039E1CReader;
struct Func80039EF4State;
struct RuntimeState;
struct S_80039760_0;
struct S_80039A88_0;
struct S_80039ED0_0;
typedef struct MessageWindowImage {
    u8 pad00[4];
    RECT rect;
} MessageWindowImage;

/* Script addresses occupy one unsigned 32-bit word in the bytecode and variable bank. */
static inline u8 *script_address_from_word(u32 address) {
    return (u8 *)(unsigned long)address;
}

/* Absolute branch operands are four little-endian bytes, at any alignment. */
static inline u8 *read_script_address(const u8 *operand) {
    return script_address_from_word(operand[0] + (operand[1] << 8) + (operand[2] << 16) +
                                    ((u32)operand[3] << 24));
}

/* command.c */
void copy_window_rect(RECT *dest, const MessageWindowImage *image);

/* widen_script_state_pair.c */
void widen_script_state_pair(void);

/* store_script_state_pair.c */
void store_script_state_pair(s16 column, s16 row);

/* vm_op_add_values.c */
void script_add(struct MessageWindow *window);

/* vm_op_call_absolute.c */
void script_call(struct MessageWindow *window);

/* vm_op_call_absolute_function.c */
void script_call_native(struct Func80039D48Reader *reader);

/* vm_op_call_function_table.c */
void script_call_service(struct MessageWindow *window);

/* vm_op_call_referenced_function_table.c */
void script_call_service_from_table(struct Func80039E1CReader *reader);

/* vm_op_call_sound_command.c */
void script_sound_command(struct ScriptReader *state);

/* vm_op_call_value.c */
void script_call_variable(struct MessageWindow *window);

/* vm_op_clear_action.c */
void script_yield(struct S_80039ED0_0 *script);

/* vm_op_clear_flag_bit.c */
void script_clear_flag(struct ScriptReader *state);

/* vm_op_clear_image.c */
void script_clear_text_window(struct ScriptReader *vm_state);

/* vm_op_clear_value.c */
void script_clear_variable(struct MessageWindow *window);

/* vm_op_copy_value_source_first.c */
void script_copy_variable_reversed(struct MessageWindow *window);

/* vm_op_divide_values.c */
s32 script_divide(struct MessageWindow *window);

/* vm_op_fill_sixteen_values.c */
void script_fill_variables(struct MessageWindow *window);

/* vm_op_install_terminator_action.c */
void script_page_break(struct MessageWindow *window);

/* vm_op_jump_absolute.c */
void script_jump(struct MessageWindow *window);

/* vm_op_jump_by_byte_index.c */
void script_jump_by_choice(struct S_80039760_0 *vm);

/* vm_op_jump_if_flag_bit_clear.c */
void script_jump_if_flag_clear(struct ScriptReader *state);

/* vm_op_jump_if_flag_bit_set.c */
u32 script_jump_if_flag_set(struct ScriptReader *state);

/* vm_op_jump_if_negative.c */
void script_jump_if_negative(struct MessageWindow *window);

/* vm_op_jump_if_nonnegative.c */
void script_jump_if_nonnegative(struct MessageWindow *window);

/* vm_op_jump_if_nonpositive.c */
void script_jump_if_nonpositive(struct MessageWindow *window);

/* vm_op_jump_if_nonzero.c */
void script_jump_if_nonzero(struct MessageWindow *window);

/* vm_op_jump_if_positive.c */
void script_jump_if_positive(struct MessageWindow *window);

/* vm_op_jump_if_zero.c */
void script_jump_if_zero(struct MessageWindow *window);

/* vm_op_jump_to_value.c */
void script_jump_to_variable(struct MessageWindow *window);

/* vm_op_load_immediate_indexed_pointer.c */
void script_load_indirect(struct ScriptReader *state);

/* vm_op_load_table_pointer_value.c */
void script_load_system_variable(struct MessageWindow *window);

/* vm_op_load_value_indexed_pointer.c */
void script_load_indirect_by_variable(struct ScriptReader *state);

/* vm_op_load_value_indexed_word.c */
void script_load_table_word_by_variable(struct ScriptReader *state);

/* vm_op_multiply_values.c */
void script_multiply(struct MessageWindow *window);

/* vm_op_noop.c */
void noop_scene_setup(void);
void noop_after_window_shrink(void);
void noop_after_menu_slot_release(void);
void noop_after_cursor_extent_completion(void);
void noop_runtime_record_idle(struct MessageWindow *window);
void noop_installed_script_action(void);
void script_nop_02(void);
void script_nop_03(void);
void script_nop_04(void);
void script_nop(void);
void script_nop_0e(void);
void script_nop_10(void);
void script_nop_14(void);
void script_nop_1b(void);
void noop_script_terminator_action(struct MessageWindow *window);
void script_nop_1f(void);
void script_nop_20(void);
void script_nop_21(void);
void script_nop_22(void);
void script_nop_2d(void);
void noop_scene_setup_a(void);
void noop_scene_setup_b(void);
void func_8003B644(void);
void noop_scene_resource_setup(void);
void func_8003C064(void);
void noop_after_fade_ramp_completion(struct FadeManagerBody *manager, struct ObjectPosition *position, struct SpriteFrameState *sprite);

/* vm_op_repeat_while_counter_nonnegative.c */
void script_wait_loop_counter(struct Func80039EF4State *vm);

/* vm_op_retry_while_status_nonzero.c */
void script_wait_sound_idle(struct S_80039A88_0 *state);

/* vm_op_return.c */
void script_return(struct MessageWindow *window);

/* vm_op_set_context_byte.c */
void script_set_text_speed(struct MessageWindow *window);

/* vm_op_set_difference_result.c */
void script_compare(struct MessageWindow *window);

/* vm_op_set_entry_byte.c */
void script_set_sound_entry_byte(struct ScriptReader *parser);

/* vm_op_set_entry_byte_pair.c */
void script_set_sound_entry_bytes(struct ScriptReader *parser);

/* vm_op_set_flag_bit.c */
s32 script_set_flag(struct ScriptReader *state);

/* vm_op_set_loop_counter.c */
void script_set_loop_counter(struct RuntimeState *state);

/* vm_op_set_owner_byte.c */
void script_store_block_byte(struct MessageWindow *window);

/* vm_op_set_state_two.c */
void script_instant_text(struct MessageWindow *window);

/* vm_op_skip_byte.c */
void script_skip_byte(ScriptCounterView *script_ctx);

/* vm_op_store_immediate_indexed_word.c */
void script_store_table_word(struct ScriptReader *state);

/* vm_op_store_table_pointer_value.c */
void script_store_system_variable(struct MessageWindow *window);

/* vm_op_subtract_values.c */
void script_subtract(struct MessageWindow *window);

#endif
