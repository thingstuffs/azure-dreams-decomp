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

s32 func_80038AB8(RuntimeContext *arg0, u8 *arg1, s32 arg2, s32 arg3)
{
    s8 *cursor;
    u8 opcode;
    ActionFunc *table;
    ActionFunc sentinel;

    if (*arg0->cursor <= 0) {
        if (arg0->active != 0) {
            func_80038CB8(arg0, (s32)arg1, arg2, arg3);
            if ((arg0->state != 2) ||
                (func_80038C40(*arg0->cursor) == 0)) {
                arg0->state = 0;
                goto return_zero;
            }
            return 1;
        }
        goto fallback;
    }

    table = D_8006AA90;
    sentinel = func_80038A10;

dispatch:
    cursor = arg0->cursor;
    opcode = (u8)*cursor;
    arg0->cursor = cursor + 1;
    table[opcode](arg0);
    if (*arg0->cursor > 0) {
        if (arg0->action == sentinel) {
            goto dispatch;
        }
    }

    if (arg0->action == func_80039AE8) {
        arg0->action = 0;
        if (arg0->active == 0) {
fallback:
            if (func_80034FD0(arg1) == 0) {
                func_8003ADB4(0xB4);
                func_80034EF8(arg1, arg1[2]);
                func_80034F58(arg1);
                return 0;
            }
            return 0;
        }
        arg0->cursor = arg0->cursor + 1;
        arg0->action = func_800381D0(arg0);
        goto check_state;
    }

check_state:
    if (arg0->state == 2) {
        return 1;
    }
return_zero:
    return 0;
}
