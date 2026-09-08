#include "common.h"

#include "common.h"

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

extern void func_80034EF8(void *, u8);
extern void func_80034F58(void *);
extern s32 func_80034FD0(void *);
extern ActionFunc func_800381D0(void *);
extern s32 func_80038A10(void *);
extern s32 func_80038C40(s8);
extern void func_80038CB8(void *, s32, s32, s32);
extern s32 func_80039AE8(void *);
extern s32 func_8003ADB4(s32);
extern ActionFunc D_8006AA90[];

/* Dispatch script opcodes, advance active text, and report whether processing can continue. */
s32 func_80038AB8(RuntimeContext *context, u8 *owner, s32 update_arg2, s32 update_arg3)
{
    s8 *cursor;
    u8 opcode;
    ActionFunc *opcode_handlers;
    ActionFunc dispatch_action;

    if (*context->cursor <= 0) {
        if (context->active != 0) {
            func_80038CB8(context, (s32)owner, update_arg2, update_arg3);
            if ((context->state != 2) ||
                (func_80038C40(*context->cursor) == 0)) {
                context->state = 0;
                goto return_zero;
            }
            return 1;
        }
        goto fallback;
    }

    opcode_handlers = D_8006AA90;
    dispatch_action = func_80038A10;

dispatch:
    cursor = context->cursor;
    opcode = (u8)*cursor;
    context->cursor = cursor + 1;
    opcode_handlers[opcode](context);
    if (*context->cursor > 0) {
        if (context->action == dispatch_action) {
            goto dispatch;
        }
    }

    if (context->action == func_80039AE8) {
        context->action = 0;
        if (context->active == 0) {
fallback:
            if (func_80034FD0(owner) == 0) {
                func_8003ADB4(0xB4);
                func_80034EF8(owner, owner[2]);
                func_80034F58(owner);
                return 0;
            }
            return 0;
        }
        context->cursor = context->cursor + 1;
        context->action = func_800381D0(context);
        goto check_state;
    }

check_state:
    if (context->state == 2) {
        return 1;
    }
return_zero:
    return 0;
}
