#ifndef ENGINE_SCRIPT_H
#define ENGINE_SCRIPT_H
/* Prototypes of the functions defined in src/engine/script/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"

/* Event-script reader projection used by operand decoders and message-byte
 * dispatch. The cursor advances at +0x1C; +0x80 is the linked byte buffer or
 * VM value-table base. Cursor-only users make no claim about the tail.
 * These handlers use pointers, with no aggregate copies or reader arrays. */
typedef struct ScriptReader {
    /* 0x00 */ u8 pad_00[0x1C];
    /* 0x1C */ u8 *cursor;
    /* 0x20 */ u8 pad_20[0x60];
    /* 0x80 */ u8 *data;
} ScriptReader;

struct Func80039578State;
struct Func800395B0State;
struct Func80039730State;
struct Func800398BCOwner;
struct Func80039C44State;
struct Func80039D10State;
struct Func80039FC0State;
struct Func8003A7BCState;
struct Func8003A7FCState;
struct S_800390D0_0;
struct S_80039568_0;
struct S_80039A08_0;
struct S_80039B84_0;
struct State;

/* call_script.c */
void call_script(s32 value);
void func_80035208(s32 value);

/* flag_script_list_nonempty.c */
void flag_script_list_nonempty(void);

/* is_list_nonempty.c */
s32 func_80034FD0(void *record);
s32 is_list_nonempty(void *record);

/* is_script_list_nonempty.c */
void is_script_list_nonempty(void);

/* opcode_01_play_sound_when_idle.c */
void handle_vm_opcode_01(struct S_800390D0_0 *state);

/* opcode_06_wait_status.c */
void handle_vm_opcode_06(struct S_80039A08_0 *state);

/* opcode_10_next_text_row.c */
void handle_vm_opcode_10(Rec_func_800381D0_arg0 *record);

/* opcode_15_start_motion.c */
void handle_vm_opcode_15(struct State *state);

/* opcode_17_install_action.c */
void vm_op_17_install_action(struct S_80039568_0 *script_ctx);

/* opcode_18_wait_ticks.c */
void handle_vm_opcode_18(struct Func80039578State *state);

/* opcode_19_wait_resident_bit.c */
void handle_vm_opcode_19(struct Func800395B0State *state);

/* opcode_25_set_state_bytes.c */
void handle_vm_opcode_25(struct Func80039730State *state);

/* opcode_29_dispatch_command.c */
void handle_vm_opcode_29(struct Func800398BCOwner *owner);

/* opcode_35_install_action.c */
void vm_op_35_install_action(struct S_80039B84_0 *script);

/* opcode_42_set_state_bytes_clear_b.c */
void handle_vm_opcode_42(struct Func80039C44State *state);

/* opcode_44_set_state_bytes_set_handler.c */
void handle_vm_opcode_44(struct Func80039D10State *state);

/* opcode_52_set_immediate.c */
void vm_op_52_set_immediate_value(struct Func80039FC0State *state);

/* opcode_68_copy_value.c */
void vm_op_68_copy_value(struct Func8003A7BCState *state);

/* opcode_69_set_immediate.c */
void vm_op_69_set_immediate_value(struct Func8003A7FCState *state);

/* remove_all_controller_nodes.c */
void remove_all_controller_nodes(void *controller);

/* service_script_controller.c */
void func_800352FC(void);
void service_script_controller(void);

/* set_flag_if_list_nonempty.c */
void set_flag_if_list_nonempty(s8 *result_flag);

/* set_script_address.c */
void set_script_address(s32 script_addr);

/* set_script_record_buffer.c */
void func_8003528C(s32 value);
void set_script_record_buffer(s32 value);

/* set_script_record_byte.c */
void set_script_record_byte(s32 value);

/* start_script.c */
void start_script(s32 script_addr);

#endif
