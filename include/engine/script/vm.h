#ifndef ENGINE_SCRIPT_VM_H
#define ENGINE_SCRIPT_VM_H
/* Prototypes of the functions defined in src/engine/script/vm/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/runtime_dispatch.h"

struct Decoder;
struct Func800391ECState;
struct Func80039694State;
struct Func80039C74State;
struct Func80039D48Reader;
struct Func80039DBCReader;
struct Func80039E1CReader;
struct Func8003A29CState;
struct Func8003A4B4State;
struct Func8003A500State;
struct Func8003A54CState;
struct Func8003A5B4State;
struct Func8003A61CState;
struct Func8003A684State;
struct Func8003A6ECState;
struct Func8003A754State;
struct Func8003A9B8State;
struct Func8003AA84State;
struct RuntimeState;
struct S_80039208_0;
struct S_800395F0_0;
struct S_80039640_0;
struct S_8003965C_0;
struct S_80039760_0;
struct S_800399EC_0;
struct S_80039A88_0;
struct S_80039ACC_0;
struct S_80039ED0_0;
struct S_80039F28_0;
struct S_8003AB14_0;
struct S_8003AB14_1;

/* command.c */
void copy_four_halfword_coordinates(struct S_8003AB14_0 *dest, struct S_8003AB14_1 *source);

/* runtime_copy_state_pair_to_words.c */
void runtime_copy_state_pair_to_words(void);

/* runtime_store_signed_state_pair.c */
void runtime_store_signed_state_pair(s16 value_ac, s16 value_ae);

/* vm_op_add_values.c */
void vm_op_59_add_values(struct RuntimeState *state);

/* vm_op_call_absolute.c */
void vm_op_21_call_absolute(struct S_800395F0_0 *script);

/* vm_op_call_absolute_function.c */
void vm_op_76_call_absolute_function(struct Func80039D48Reader *reader);

/* vm_op_call_function_table.c */
void vm_op_46_call_function_table(struct Func80039DBCReader *state);

/* vm_op_call_referenced_function_table.c */
void vm_op_47_call_referenced_function_table(struct Func80039E1CReader *reader);

/* vm_op_call_value.c */
u8 *vm_op_75_call_value(struct Func8003AA84State *state);

/* vm_op_clear_action.c */
void vm_op_48_clear_action(struct S_80039ED0_0 *script);

/* vm_op_clear_image.c */
void vm_op_08_clear_image(void *vm_state);

/* vm_op_clear_value.c */
void vm_op_49_clear_value(struct S_80039F28_0 *vm);

/* vm_op_fill_sixteen_values.c */
void vm_op_50_fill_sixteen_values(void *vm);

/* vm_op_install_terminator_action.c */
void vm_op_87_install_terminator_action(struct S_80039ACC_0 *script);

/* vm_op_jump_absolute.c */
void vm_op_23_jump_absolute(struct S_8003965C_0 *vm);

/* vm_op_jump_by_byte_index.c */
void vm_op_26_jump_by_byte_index(struct S_80039760_0 *vm);

/* vm_op_jump_if_flag_bit_clear.c */
void vm_op_43_jump_if_flag_bit_clear(struct Func80039C74State *state);

/* vm_op_jump_if_flag_bit_set.c */
u32 vm_op_24_jump_if_flag_bit_set(struct Func80039694State *state);

/* vm_op_jump_if_negative.c */
void vm_op_65_jump_if_negative(struct Func8003A684State *state);

/* vm_op_jump_if_nonnegative.c */
void vm_op_66_jump_if_nonnegative(struct Func8003A6ECState *state);

/* vm_op_jump_if_nonpositive.c */
void vm_op_64_jump_if_nonpositive(struct Func8003A61CState *state);

/* vm_op_jump_if_nonzero.c */
void vm_op_63_jump_if_nonzero(struct Func8003A5B4State *state);

/* vm_op_jump_if_positive.c */
void vm_op_67_jump_if_positive(struct Func8003A754State *state);

/* vm_op_jump_if_zero.c */
void vm_op_62_jump_if_zero(struct Func8003A54CState *state);

/* vm_op_jump_to_value.c */
void vm_op_72_jump_to_value(struct Func8003A9B8State *vm);

/* vm_op_load_value_indexed_pointer.c */
void vm_op_79_load_value_indexed_pointer(struct RuntimeState *state);

/* vm_op_multiply_values.c */
void vm_op_73_multiply_values(struct Decoder *script);

/* vm_op_noop.c */
void noop_scene_setup(void);
void noop_after_window_shrink(void);
void noop_after_menu_slot_release(void);
void noop_after_cursor_extent_completion(void);
void noop_runtime_record_idle(void);
void noop_installed_script_action(void);
void vm_op_02_noop(void);
void vm_op_03_noop(void);
void vm_op_04_noop(void);
void vm_shared_noop(void);
void vm_op_14_noop(void);
void vm_op_16_noop(void);
void vm_op_20_noop(void);
void vm_op_27_noop(void);
void noop_script_terminator_action(void);
void vm_op_31_noop(void);
void vm_op_32_noop(void);
void vm_op_33_noop(void);
void vm_op_34_noop(void);
void vm_op_45_noop(void);
void noop_scene_setup_a(void);
void noop_scene_setup_b(void);
void func_8003B644(void);
void noop_scene_resource_setup(void);
void func_8003C064(void);
void noop_after_fade_ramp_completion(void);

/* vm_op_retry_while_status_nonzero.c */
void vm_op_86_retry_while_status_nonzero(struct S_80039A88_0 *state);

/* vm_op_return.c */
void vm_op_22_return(struct S_80039640_0 *state);

/* vm_op_set_context_byte.c */
void vm_op_09_set_context_byte(struct Func800391ECState *state);

/* vm_op_set_difference_result.c */
void vm_op_61_set_difference_result(struct Func8003A500State *state);

/* vm_op_set_loop_counter.c */
void vm_op_84_set_loop_counter(struct RuntimeState *state);

/* vm_op_set_owner_byte.c */
void vm_op_05_set_owner_byte(struct S_800399EC_0 *script_ctx);

/* vm_op_set_state_two.c */
void vm_op_11_set_state_two(struct S_80039208_0 *script_ctx);

/* vm_op_skip_byte.c */
void vm_op_56_skip_byte(ScriptCounterView *script_ctx);

/* vm_op_store_immediate_indexed_word.c */
void vm_op_58_store_immediate_indexed_word(struct RuntimeState *state);

/* vm_op_store_table_pointer_value.c */
void vm_op_57_store_table_pointer_value(struct Func8003A29CState *state);

/* vm_op_subtract_values.c */
void vm_op_60_subtract_values(struct Func8003A4B4State *state);

#endif
