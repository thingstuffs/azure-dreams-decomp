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

struct S_800389B4_0;

/* Voice-wait handlers share the action, byte cursor, linked data and signed
 * gate at these offsets. This is an access prefix, not an allocation extent. */
typedef struct MessageVoiceState {
    u8 pad_00[0x10];
    void (*action)(struct S_800389B4_0 *);
    u8 pad_14[0x8];
    u8 *cursor;
    u8 pad_20[0x60];
    u8 *data;
    u8 pad_84[0x3];
    s8 gate;
} MessageVoiceState;

/* Event-script opcodes: the slot of each handler in script_opcode_handlers,
 * the resident table that interpret_script_opcodes_until_action_changes
 * dispatches (byte format described there). "vN" is variable N, a word at
 * VM block +0x48 + 4*N; operands are listed in script order. Four opcodes
 * duplicate others: 0x44 = 0x33, 0x45 = 0x34, 0x46 = 0x36, and 0x37 is 0x33
 * with its two operands swapped. */
enum ScriptOpcode {
    SCRIPT_OP_NOP_00 = 0x00,                /* script_nop; byte 0x00 itself is the text return, never dispatched */
    SCRIPT_OP_END_MESSAGE = 0x01,           /* script_end_message */
    SCRIPT_OP_NOP_02 = 0x02,                /* script_nop_02 */
    SCRIPT_OP_NOP_03 = 0x03,                /* script_nop_03 */
    SCRIPT_OP_NOP_04 = 0x04,                /* script_nop_04 */
    SCRIPT_OP_SET_BLOCK_BYTE_3D = 0x05,     /* script_set_block_byte_3d: u8 */
    SCRIPT_OP_WAIT_VOICE_THEN_ADVANCE = 0x06, /* script_wait_voice_then_advance */
    SCRIPT_OP_NOP_07 = 0x07,                /* script_nop */
    SCRIPT_OP_CLEAR_TEXT_WINDOW = 0x08,     /* script_clear_text_window */
    SCRIPT_OP_SET_TEXT_SPEED = 0x09,        /* script_set_text_speed: u8 glyph delay */
    SCRIPT_OP_NEW_LINE = 0x0A,              /* script_new_line */
    SCRIPT_OP_INSTANT_TEXT = 0x0B,          /* script_instant_text */
    SCRIPT_OP_SET_FLAG = 0x0C,              /* script_set_flag: flag16 */
    SCRIPT_OP_CLEAR_FLAG = 0x0D,            /* script_clear_flag: flag16 */
    SCRIPT_OP_NOP_0E = 0x0E,                /* script_nop_0e */
    SCRIPT_OP_SET_ACTOR_MOTION = 0x0F,      /* script_set_actor_motion: u8 actor, u8 motion (no motion byte for actor 0) */
    SCRIPT_OP_NOP_10 = 0x10,                /* script_nop_10 */
    SCRIPT_OP_WAIT_BUTTON = 0x11,           /* script_wait_button */
    SCRIPT_OP_WAIT_FRAMES = 0x12,           /* script_wait_frames: u16 */
    SCRIPT_OP_WAIT_FLAG_SET = 0x13,         /* script_wait_flag_set: flag16 */
    SCRIPT_OP_NOP_14 = 0x14,                /* script_nop_14 */
    SCRIPT_OP_CALL = 0x15,                  /* script_call: addr32 */
    SCRIPT_OP_RETURN = 0x16,                /* script_return */
    SCRIPT_OP_JUMP = 0x17,                  /* script_jump: addr32 */
    SCRIPT_OP_JUMP_IF_FLAG_SET = 0x18,      /* script_jump_if_flag_set: flag16, addr32 */
    SCRIPT_OP_CHOICE_MENU = 0x19,           /* script_choice_menu: u8 option count; answer at +0x27 */
    SCRIPT_OP_JUMP_BY_CHOICE = 0x1A,        /* script_jump_by_choice: one inline addr32 per option */
    SCRIPT_OP_NOP_1B = 0x1B,                /* script_nop_1b */
    SCRIPT_OP_SET_SOUND_ENTRY_BYTE = 0x1C,  /* script_set_sound_entry_byte: u8 key, u8 value */
    SCRIPT_OP_PLAY_VOICE_CUE = 0x1D,        /* script_play_voice_cue: imm32, imm32 */
    SCRIPT_OP_SOUND_COMMAND = 0x1E,         /* script_sound_command: u16 SD_Call command */
    SCRIPT_OP_NOP_1F = 0x1F,                /* script_nop_1f */
    SCRIPT_OP_NOP_20 = 0x20,                /* script_nop_20 */
    SCRIPT_OP_NOP_21 = 0x21,                /* script_nop_21 */
    SCRIPT_OP_NOP_22 = 0x22,                /* script_nop_22 */
    SCRIPT_OP_PARK = 0x23,                  /* script_park */
    SCRIPT_OP_WAIT_ACTOR_READY = 0x24,      /* script_wait_actor_ready: u8 actor */
    SCRIPT_OP_POLL_SERVICE = 0x25,          /* script_poll_service: u8 call number (read back signed) */
    SCRIPT_OP_CALL_INDEXED_HANDLER = 0x26,  /* script_call_indexed_handler: u8 */
    SCRIPT_OP_POLL_GROUP_HANDLER = 0x27,    /* script_poll_group_handler: u8 group, u8 entry */
    SCRIPT_OP_NOP_28 = 0x28,                /* script_nop */
    SCRIPT_OP_NOP_29 = 0x29,                /* script_nop */
    SCRIPT_OP_TIMED_CHOICE_MENU = 0x2A,     /* script_timed_choice_menu: u8 option count */
    SCRIPT_OP_JUMP_IF_FLAG_CLEAR = 0x2B,    /* script_jump_if_flag_clear: flag16, addr32 */
    SCRIPT_OP_WIDE_CHOICE_MENU = 0x2C,      /* script_wide_choice_menu: u8 option count */
    SCRIPT_OP_NOP_2D = 0x2D,                /* script_nop_2d */
    SCRIPT_OP_CALL_SERVICE = 0x2E,          /* script_call_service: u8 call number; v0..v3 in, v15 out */
    SCRIPT_OP_CALL_SERVICE_FROM_TABLE = 0x2F, /* script_call_service_from_table: u8, addr32 of the table pointer */
    SCRIPT_OP_YIELD = 0x30,                 /* script_yield */
    SCRIPT_OP_CLEAR_VARIABLE = 0x31,        /* script_clear_variable: var */
    SCRIPT_OP_FILL_VARIABLES = 0x32,        /* script_fill_variables: u8 into v0..v15 */
    SCRIPT_OP_COPY_VARIABLE_A = 0x33,       /* script_copy_variable_a: dst, src */
    SCRIPT_OP_SET_VARIABLE_A = 0x34,        /* script_set_variable_a: var, imm32 */
    SCRIPT_OP_LOAD_SYSTEM_VARIABLE = 0x35,  /* script_load_system_variable: var, u8 S_ARG_* */
    SCRIPT_OP_LOAD_TABLE_WORD_A = 0x36,     /* script_load_table_word_a: var, u8 index, addr32 */
    SCRIPT_OP_COPY_VARIABLE_REVERSED = 0x37, /* script_copy_variable_reversed: src, dst */
    SCRIPT_OP_SKIP_BYTE = 0x38,             /* script_skip_byte: u8 ignored */
    SCRIPT_OP_STORE_SYSTEM_VARIABLE = 0x39, /* script_store_system_variable: var, u8 S_ARG_* */
    SCRIPT_OP_STORE_TABLE_WORD = 0x3A,      /* script_store_table_word: var, u8 index, addr32 */
    SCRIPT_OP_ADD = 0x3B,                   /* script_add: dst, src */
    SCRIPT_OP_SUBTRACT = 0x3C,              /* script_subtract: dst, src */
    SCRIPT_OP_COMPARE = 0x3D,               /* script_compare: a, b; v15 = a - b */
    SCRIPT_OP_JUMP_IF_ZERO = 0x3E,          /* script_jump_if_zero: var, addr32 */
    SCRIPT_OP_JUMP_IF_NONZERO = 0x3F,       /* script_jump_if_nonzero: var, addr32 */
    SCRIPT_OP_JUMP_IF_NONPOSITIVE = 0x40,   /* script_jump_if_nonpositive: var, addr32 (<= 0) */
    SCRIPT_OP_JUMP_IF_NEGATIVE = 0x41,      /* script_jump_if_negative: var, addr32 (< 0) */
    SCRIPT_OP_JUMP_IF_NONNEGATIVE = 0x42,   /* script_jump_if_nonnegative: var, addr32 (>= 0) */
    SCRIPT_OP_JUMP_IF_POSITIVE = 0x43,      /* script_jump_if_positive: var, addr32 (> 0) */
    SCRIPT_OP_COPY_VARIABLE_B = 0x44,       /* script_copy_variable_b: dst, src */
    SCRIPT_OP_SET_VARIABLE_B = 0x45,        /* script_set_variable_b: var, imm32 */
    SCRIPT_OP_LOAD_TABLE_WORD_B = 0x46,     /* script_load_table_word_b: var, u8 index, addr32 */
    SCRIPT_OP_LOAD_TABLE_WORD_BY_VARIABLE = 0x47, /* script_load_table_word_by_variable: var, index var, addr32 */
    SCRIPT_OP_JUMP_TO_VARIABLE = 0x48,      /* script_jump_to_variable: var */
    SCRIPT_OP_MULTIPLY = 0x49,              /* script_multiply: dst, src */
    SCRIPT_OP_DIVIDE = 0x4A,                /* script_divide: dst, src */
    SCRIPT_OP_CALL_VARIABLE = 0x4B,         /* script_call_variable: var */
    SCRIPT_OP_CALL_NATIVE = 0x4C,           /* script_call_native: func32; v0..v3 in, v15 out */
    SCRIPT_OP_LOAD_INDIRECT = 0x4D,         /* script_load_indirect: var, u8 index, addr32 of a pointer table */
    SCRIPT_OP_STORE_INDIRECT = 0x4E,        /* script_store_indirect: as 0x4D, but stores through one byte (see source) */
    SCRIPT_OP_LOAD_INDIRECT_BY_VARIABLE = 0x4F, /* script_load_indirect_by_variable: var, index var, addr32 */
    SCRIPT_OP_STORE_INDIRECT_BY_VARIABLE = 0x50, /* script_store_indirect_by_variable: as 0x4F, one byte (see source) */
    SCRIPT_OP_NOP_51 = 0x51,                /* script_nop */
    SCRIPT_OP_NOP_52 = 0x52,                /* script_nop */
    SCRIPT_OP_SET_SOUND_ENTRY_BYTES = 0x53, /* script_set_sound_entry_bytes: u8 key, u8 value */
    SCRIPT_OP_SET_LOOP_COUNTER = 0x54,      /* script_set_loop_counter: u8 */
    SCRIPT_OP_WAIT_LOOP_COUNTER = 0x55,     /* script_wait_loop_counter */
    SCRIPT_OP_WAIT_SOUND_IDLE = 0x56,       /* script_wait_sound_idle */
    SCRIPT_OP_PAGE_BREAK = 0x57,            /* script_page_break: u8 wait mode, read after the button */
    SCRIPT_OP_TOWN_TRANSITION = 0x58,       /* dispatch_town_transition: also called directly; likely the word after the real table */
    SCRIPT_OP_COUNT                         /* 89 table slots */
};

/* One script_opcode_handlers slot. The handlers read different views of the
 * script context, so the slot leaves their parameters unspecified. */
typedef void (*ScriptOpcodeHandler)();

/* Defined with its interpreter in src/slus/konami_runtime_w_80038AB8.c. */
extern ScriptOpcodeHandler script_opcode_handlers[SCRIPT_OP_COUNT];

struct Func80039578State;
struct Func800395B0State;
struct Func80039730State;
struct Func80039B94State;
struct Func80039BBCState;
struct Func80039BE4State;
struct Func80039C0CState;
struct Func80039C44State;
struct Func80039D10State;
struct Func80039F80State;
struct Func80039FC0State;
struct Func8003A060State;
struct Func8003A7BCState;
struct Func8003A7FCState;
struct Func8003A858State;
struct S_800390D0_0;
struct S_80039568_0;
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
void script_end_message(struct S_800390D0_0 *state);

/* opcode_06_wait_status.c */
void script_wait_voice_then_advance(MessageVoiceState *state);

/* opcode_10_next_text_row.c */
void script_new_line(Rec_func_800381D0_arg0 *record);

/* opcode_15_start_motion.c */
void script_set_actor_motion(struct State *state);

/* opcode_17_install_action.c */
void script_wait_button(struct S_80039568_0 *script_ctx);

/* opcode_18_wait_ticks.c */
void script_wait_frames(struct Func80039578State *state);

/* opcode_19_wait_resident_bit.c */
void script_wait_flag_set(struct Func800395B0State *state);

/* opcode_25_set_state_bytes.c */
void script_choice_menu(struct Func80039730State *state);

/* opcode_29_dispatch_command.c */
void script_play_voice_cue(MessageVoiceState *owner);

/* opcode_35_install_action.c */
void script_park(struct S_80039B84_0 *script);

/* opcode_36_read_entry_byte.c */
void script_wait_actor_ready(struct Func80039B94State *state);

/* opcode_37_read_handler_arg.c */
void script_poll_service(struct Func80039BBCState *state);

/* opcode_38_select_indexed_handler.c */
void script_call_indexed_handler(struct Func80039BE4State *state);

/* opcode_39_read_handler_pair.c */
void script_poll_group_handler(struct Func80039C0CState *state);

/* opcode_42_set_state_bytes_clear_b.c */
void script_timed_choice_menu(struct Func80039C44State *state);

/* opcode_44_set_state_bytes_set_handler.c */
void script_wide_choice_menu(struct Func80039D10State *state);

/* opcode_51_copy_value.c */
void script_copy_variable_a(struct Func80039F80State *reader);

/* opcode_52_set_immediate.c */
void script_set_variable_a(struct Func80039FC0State *state);

/* opcode_54_load_indexed_word.c */
void script_load_table_word_a(struct Func8003A060State *state);

/* opcode_68_copy_value.c */
void script_copy_variable_b(struct Func8003A7BCState *state);

/* opcode_69_set_immediate.c */
void script_set_variable_b(struct Func8003A7FCState *state);

/* opcode_70_load_indexed_word.c */
void script_load_table_word_b(struct Func8003A858State *state);

/* opcode_78_store_word_indirect_immediate.c */
void script_store_indirect(ScriptReader *state);

/* opcode_80_store_word_indirect_indexed.c */
void script_store_indirect_by_variable(ScriptReader *state);

/* remove_all_controller_nodes.c */
void remove_all_controller_nodes(void *controller);

/* service_script_controller.c */
s32 func_800352FC(void);
s32 service_script_controller(void);

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
