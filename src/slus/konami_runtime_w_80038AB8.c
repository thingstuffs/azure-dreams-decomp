#include "common.h"

#include "common.h"
#include "engine/audio.h"
#include "engine/graphics.h"
#include "engine/message.h"
#include "engine/object.h"
#include "engine/script.h"
#include "engine/script/vm.h"
#include "engine/window.h"
#include "slus.h"

/* The window action slot holds handlers of several signatures (the dispatcher
 * itself, the script terminator, the wait handlers from func_800381D0). */
typedef void (*ActionFunc)();

typedef struct RuntimeContext {
    u8 pad0[0x10];
    ActionFunc action;
    u8 pad14[8];
    s8 *cursor;
    u8 pad20[0xE];
    u8 state;
    u8 pad2F[0x56];
    s8 active;
} RuntimeContext;

struct S_func_80038CB8_0;
/* Event-script byte format. The cursor at +0x1C walks a byte stream:
 * - 0x01-0x58: opcode; script_opcode_handlers[op] (enum ScriptOpcode) reads its
 *   operands inline. 16-bit and 32-bit operands are little-endian and unaligned;
 *   addresses are absolute RAM addresses.
 * - A byte that is not positive as s8 (0x00, 0x80-0xFF) stops dispatch and goes
 *   to the message window: Shift-JIS lead bytes start two-byte glyphs;
 *   0xFD n prints variable n as a number, 0xFE n inserts message string n and
 *   0xFF + addr32 inserts the string that addr32 points to. Each insertion pushes
 *   a return address that a 0x00 byte pops (the text return).
 * - SCRIPT_OP_JUMP_BY_CHOICE is followed by an inline table of addr32 entries,
 *   one per option of the preceding choice menu (0x19, 0x2A or 0x2C).
 * - SCRIPT_OP_PAGE_BREAK waits for a button, then the byte after it is read as
 *   the wait mode (0 silent, 1 sound 0xB4, otherwise sound 0x74 and wait idle).
 * The table below has one slot per opcode (resident data at 0x8006AA90). Six
 * unused slots share script_nop; slot 0x58 holds dispatch_town_transition,
 * which is also called directly. */
ScriptOpcodeHandler script_opcode_handlers[SCRIPT_OP_COUNT] = {
    [SCRIPT_OP_NOP_00]                      = script_nop,
    [SCRIPT_OP_END_MESSAGE]                 = script_end_message,
    [SCRIPT_OP_NOP_02]                      = script_nop_02,
    [SCRIPT_OP_NOP_03]                      = script_nop_03,
    [SCRIPT_OP_NOP_04]                      = script_nop_04,
    [SCRIPT_OP_SET_BLOCK_BYTE_3D]           = script_set_block_byte_3d,
    [SCRIPT_OP_WAIT_VOICE_THEN_ADVANCE]     = script_wait_voice_then_advance,
    [SCRIPT_OP_NOP_07]                      = script_nop,
    [SCRIPT_OP_CLEAR_TEXT_WINDOW]           = script_clear_text_window,
    [SCRIPT_OP_SET_TEXT_SPEED]              = script_set_text_speed,
    [SCRIPT_OP_NEW_LINE]                    = script_new_line,
    [SCRIPT_OP_INSTANT_TEXT]                = script_instant_text,
    [SCRIPT_OP_SET_FLAG]                    = (ScriptOpcodeHandler)script_set_flag,
    [SCRIPT_OP_CLEAR_FLAG]                  = script_clear_flag,
    [SCRIPT_OP_NOP_0E]                      = script_nop_0e,
    [SCRIPT_OP_SET_ACTOR_MOTION]            = script_set_actor_motion,
    [SCRIPT_OP_NOP_10]                      = script_nop_10,
    [SCRIPT_OP_WAIT_BUTTON]                 = script_wait_button,
    [SCRIPT_OP_WAIT_FRAMES]                 = script_wait_frames,
    [SCRIPT_OP_WAIT_FLAG_SET]               = script_wait_flag_set,
    [SCRIPT_OP_NOP_14]                      = script_nop_14,
    [SCRIPT_OP_CALL]                        = script_call,
    [SCRIPT_OP_RETURN]                      = script_return,
    [SCRIPT_OP_JUMP]                        = script_jump,
    [SCRIPT_OP_JUMP_IF_FLAG_SET]            = (ScriptOpcodeHandler)script_jump_if_flag_set,
    [SCRIPT_OP_CHOICE_MENU]                 = script_choice_menu,
    [SCRIPT_OP_JUMP_BY_CHOICE]              = script_jump_by_choice,
    [SCRIPT_OP_NOP_1B]                      = script_nop_1b,
    [SCRIPT_OP_SET_SOUND_ENTRY_BYTE]        = script_set_sound_entry_byte,
    [SCRIPT_OP_PLAY_VOICE_CUE]              = script_play_voice_cue,
    [SCRIPT_OP_SOUND_COMMAND]               = script_sound_command,
    [SCRIPT_OP_NOP_1F]                      = script_nop_1f,
    [SCRIPT_OP_NOP_20]                      = script_nop_20,
    [SCRIPT_OP_NOP_21]                      = script_nop_21,
    [SCRIPT_OP_NOP_22]                      = script_nop_22,
    [SCRIPT_OP_PARK]                        = script_park,
    [SCRIPT_OP_WAIT_ACTOR_READY]            = script_wait_actor_ready,
    [SCRIPT_OP_POLL_SERVICE]                = script_poll_service,
    [SCRIPT_OP_CALL_INDEXED_HANDLER]        = script_call_indexed_handler,
    [SCRIPT_OP_POLL_GROUP_HANDLER]          = script_poll_group_handler,
    [SCRIPT_OP_NOP_28]                      = script_nop,
    [SCRIPT_OP_NOP_29]                      = script_nop,
    [SCRIPT_OP_TIMED_CHOICE_MENU]           = script_timed_choice_menu,
    [SCRIPT_OP_JUMP_IF_FLAG_CLEAR]          = script_jump_if_flag_clear,
    [SCRIPT_OP_WIDE_CHOICE_MENU]            = script_wide_choice_menu,
    [SCRIPT_OP_NOP_2D]                      = script_nop_2d,
    [SCRIPT_OP_CALL_SERVICE]                = script_call_service,
    [SCRIPT_OP_CALL_SERVICE_FROM_TABLE]     = script_call_service_from_table,
    [SCRIPT_OP_YIELD]                       = script_yield,
    [SCRIPT_OP_CLEAR_VARIABLE]              = script_clear_variable,
    [SCRIPT_OP_FILL_VARIABLES]              = script_fill_variables,
    [SCRIPT_OP_COPY_VARIABLE_A]             = script_copy_variable_a,
    [SCRIPT_OP_SET_VARIABLE_A]              = script_set_variable_a,
    [SCRIPT_OP_LOAD_SYSTEM_VARIABLE]        = script_load_system_variable,
    [SCRIPT_OP_LOAD_TABLE_WORD_A]           = script_load_table_word_a,
    [SCRIPT_OP_COPY_VARIABLE_REVERSED]      = script_copy_variable_reversed,
    [SCRIPT_OP_SKIP_BYTE]                   = script_skip_byte,
    [SCRIPT_OP_STORE_SYSTEM_VARIABLE]       = script_store_system_variable,
    [SCRIPT_OP_STORE_TABLE_WORD]            = script_store_table_word,
    [SCRIPT_OP_ADD]                         = script_add,
    [SCRIPT_OP_SUBTRACT]                    = script_subtract,
    [SCRIPT_OP_COMPARE]                     = script_compare,
    [SCRIPT_OP_JUMP_IF_ZERO]                = script_jump_if_zero,
    [SCRIPT_OP_JUMP_IF_NONZERO]             = script_jump_if_nonzero,
    [SCRIPT_OP_JUMP_IF_NONPOSITIVE]         = script_jump_if_nonpositive,
    [SCRIPT_OP_JUMP_IF_NEGATIVE]            = script_jump_if_negative,
    [SCRIPT_OP_JUMP_IF_NONNEGATIVE]         = script_jump_if_nonnegative,
    [SCRIPT_OP_JUMP_IF_POSITIVE]            = script_jump_if_positive,
    [SCRIPT_OP_COPY_VARIABLE_B]             = script_copy_variable_b,
    [SCRIPT_OP_SET_VARIABLE_B]              = script_set_variable_b,
    [SCRIPT_OP_LOAD_TABLE_WORD_B]           = script_load_table_word_b,
    [SCRIPT_OP_LOAD_TABLE_WORD_BY_VARIABLE] = script_load_table_word_by_variable,
    [SCRIPT_OP_JUMP_TO_VARIABLE]            = script_jump_to_variable,
    [SCRIPT_OP_MULTIPLY]                    = script_multiply,
    [SCRIPT_OP_DIVIDE]                      = (ScriptOpcodeHandler)script_divide,
    [SCRIPT_OP_CALL_VARIABLE]               = (ScriptOpcodeHandler)script_call_variable,
    [SCRIPT_OP_CALL_NATIVE]                 = script_call_native,
    [SCRIPT_OP_LOAD_INDIRECT]               = script_load_indirect,
    [SCRIPT_OP_STORE_INDIRECT]              = script_store_indirect,
    [SCRIPT_OP_LOAD_INDIRECT_BY_VARIABLE]   = script_load_indirect_by_variable,
    [SCRIPT_OP_STORE_INDIRECT_BY_VARIABLE]  = script_store_indirect_by_variable,
    [SCRIPT_OP_NOP_51]                      = script_nop,
    [SCRIPT_OP_NOP_52]                      = script_nop,
    [SCRIPT_OP_SET_SOUND_ENTRY_BYTES]       = script_set_sound_entry_bytes,
    [SCRIPT_OP_SET_LOOP_COUNTER]            = script_set_loop_counter,
    [SCRIPT_OP_WAIT_LOOP_COUNTER]           = script_wait_loop_counter,
    [SCRIPT_OP_WAIT_SOUND_IDLE]             = script_wait_sound_idle,
    [SCRIPT_OP_PAGE_BREAK]                  = script_page_break,
    [SCRIPT_OP_TOWN_TRANSITION]             = dispatch_town_transition,
};

/* Dispatch script opcodes, advance active text, and report whether processing can continue. */
s32 interpret_script_opcodes_until_action_changes(RuntimeContext *context, u8 *owner)
{
    s8 *cursor;
    u8 opcode;
    ScriptOpcodeHandler *opcode_handlers;
    ActionFunc dispatch_action;

    if (*context->cursor <= 0) {
        if (context->active != 0) {
            func_80038CB8((struct S_func_80038CB8_0 *)context);
            if ((context->state == 2) &&
                (is_message_byte_in_lookup_set(*context->cursor) != 0)) {
                return 1;
            }
            context->state = 0;
            goto return_zero;
        }
        goto fallback;
    }

    opcode_handlers = script_opcode_handlers;
    dispatch_action = func_80038A10;

    do {
        cursor = context->cursor;
        opcode = (u8)*cursor;
        context->cursor = cursor + 1;
        opcode_handlers[opcode](context);
    } while (*context->cursor > 0 && context->action == dispatch_action);

    if (context->action == noop_script_terminator_action) {
        context->action = 0;
        if (context->active == 0) {
fallback:
            if (func_80034FD0(owner) == 0) {
                dispatch_sound_word_unless_disabled(0xB4);
                func_80034EF8(owner, owner[2]);
                func_80034F58(owner);
                return 0;
            }
            return 0;
        }
        context->cursor = context->cursor + 1;
        context->action = func_800381D0(context);
    }

    if (context->state == 2) {
        return 1;
    }
return_zero:
    return 0;
}
