#include "common.h"

typedef struct S_80013714 {
    u16 flags;
    u8 pad[8];
} S_80013714;

typedef struct D_80083460_S {
    u8 pad0[2];
    u16 unk2;
    u8 pad[8];
} D_80083460_S;

extern S_80013714 D_80013714;
extern s32 D_80083168[4];
extern D_80083460_S D_80083460;

extern s32 func_800A5C70(s32 arg0);
extern void func_8009F644(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* Sets the object action to 0x33, conditionally sets a global flag, and dispatches the target. */
void func_800969B8(void *object, s32 unused_1, s32 unused_2, s32 target) {
    s32 action = 0x33;
    register s32 saved_target ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 dispatch_target;
    s32 target_check;

    *((s8 *)object + 0x9A) = action;
    *((s8 *)object + 0x9B) = 0;
    *(s32 *)((s8 *)object + 0x8C) = 0;
    ASM_KEEP(action);   /* MATCH pin: retail schedule: same instructions, different order without it */
    saved_target = target;

    if (D_80013714.flags & 2) {
        goto apply_flag;
    }
    dispatch_target = saved_target;
    if (!(D_80083168[0] & 0x20)) {
        goto done;
    }
    ASM_KEEP(dispatch_target);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    target_check = func_800A5C70(dispatch_target);
    dispatch_target = saved_target;
    if (!target_check) {
        goto done;
    }

apply_flag:
    D_80083460.unk2 |= 0x80;
    ASM_KEEP(saved_target);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    dispatch_target = saved_target;

done:
    func_8009F644(dispatch_target, 0x10, 0, 0);
}
