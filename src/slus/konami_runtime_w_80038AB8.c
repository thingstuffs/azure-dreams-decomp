#include "common.h"

#include "common.h"
#include "engine/audio.h"
#include "engine/graphics.h"
#include "engine/message.h"
#include "engine/script.h"
#include "engine/window.h"
#include "slus.h"

typedef s32 (*ActionFunc)(void *);

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
extern s32 noop_script_terminator_action(void *);
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
 * The table is resident data at 0x8006AA90. Slot 0x58 holds
 * dispatch_town_transition, which is also called directly. */
extern ActionFunc script_opcode_handlers[SCRIPT_OP_COUNT];

/* Dispatch script opcodes, advance active text, and report whether processing can continue. */
s32 interpret_script_opcodes_until_action_changes(RuntimeContext *context, u8 *owner)
{
    s8 *cursor;
    u8 opcode;
    ActionFunc *opcode_handlers;
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
