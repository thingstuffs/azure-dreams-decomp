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

void func_800969B8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 action = 0x33;
    register s32 saved_arg ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 out_arg;
    s32 call_result;

    *((s8 *)arg0 + 0x9A) = action;
    *((s8 *)arg0 + 0x9B) = 0;
    *(s32 *)((s8 *)arg0 + 0x8C) = 0;
    ASM_KEEP(action);   /* MATCH pin: retail schedule: same instructions, different order without it */
    saved_arg = arg3;

    if (D_80013714.flags & 2) {
        goto apply_flag;
    }
    out_arg = saved_arg;
    if (!(D_80083168[0] & 0x20)) {
        goto done;
    }
    ASM_KEEP(out_arg);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    call_result = func_800A5C70(out_arg);
    out_arg = saved_arg;
    if (!call_result) {
        goto done;
    }

apply_flag:
    D_80083460.unk2 |= 0x80;
    ASM_KEEP(saved_arg);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    out_arg = saved_arg;

done:
    func_8009F644(out_arg, 0x10, 0, 0);
}
