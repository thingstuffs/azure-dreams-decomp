#include "common.h"

typedef void (*Func)(void *, s32);
typedef struct {
    u8 pad[0xC];
    s32 value;
} GlobalState;

extern Func D_800E2934[];
extern GlobalState *D_800E5910;

extern void func_800DC628(void *, s32);
extern void func_800DC6BC(void *);
extern void func_800DC6E8(void *, s32, void *);
extern s32 func_800DCA1C(void *, s32);

void func_800DC650(u8 *arg0) {
    u8 *ctx = arg0;
    u8 *base;
    u32 flags;
    s32 current;
    s32 target;
    s32 delta;
    register u32 call_flags ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    void *call_arg;
    s32 result;

    base = ctx + 0x3C;
    flags = *(u32 *)(ctx + 0x50);
    current = *(s16 *)(*(u8 **)(base + 8) + 0xE);
    target = *(s16 *)((u8 *)D_800E2934 + (flags & 2));
    delta = target - current;

    if (delta < 0) {
        current -= 0x80;
        if (delta < -0x80) {
            func_800DC6BC(arg0);
            return;
        }
        goto set_target;
    } else {
        current += 0x80;
        if (delta >= 0x81) {
            goto compare;
        }
    }

set_target:
    ASM_USE_NV(current);   /* MATCH pin: load-bearing for the whole function shape */
    current = target;
compare:
    if (current != target) {
        *(s32 *)(ctx + 0x58) = 1;
        func_800DC6E8(*(void **)(ctx + 0x3C), 0, ctx);
        return;
    }

    call_flags = *(u32 *)(ctx + 0x50);
    call_arg = *(void **)(ctx + 0x3C);
    call_flags = ((call_flags >> 1) ^ 1) % 2;
    ASM_KEEP(call_flags);   /* MATCH pin: retail schedule: same instructions, different order without it */
    result = func_800DCA1C(call_arg, call_flags);
    do {
        D_800E5910->value = result;
    } while (0);
    func_800DC628(base, current);
}

/* MECHANISM: A guarded a2 context role is kept only after computing the held base.
   A 0x20-byte frame holds ctx+0x3c in s1 and the signed current value in s0.
   Split flag reads give v1 at entry and the retail reload before func_800DCA1C.
   Explicit clamp updates and the +0x58 store expose the retail branch/jump delay slots. */
