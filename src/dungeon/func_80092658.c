#include "common.h"

typedef struct {
    u8 pad0[8];
    s32 flags;
} D83160;

typedef struct {
    u8 pad0[0x1c];
    s32 flags;
    u8 pad20[0x3c];
    s32 value;
} Resource;

typedef struct {
    u8 pad0[0x8c];
    u8 *callback;
    u8 pad90[6];
    u16 counter;
    u8 pad98[3];
    u8 state;
    u8 pad9c[6];
    u16 flags;
} Object;

extern D83160 D_80083160;
extern u16 D_80083460[];
extern u8 D_80096384[];
extern u8 D_80097C78;
extern s32 func_80042900(void *, s32);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern s32 func_800A5C70(Resource *);

void func_80097DB8(Object *arg0, s32 arg1, s32 arg2, Resource *arg3) {
    s32 state;
    /* MATCH: Keep the guard result in v0 across argument setup. */
    s32 guard;
    D83160 *ctx;
    /* MATCH: Keep the shared flag table in its retail saved register. */
    register u16 *flags ASM_REG("$17");
    /* MATCH: Keep the incoming resource in a3 for the pass-through call. */
    Resource *resource = arg3;
    /* MATCH: Set a0 in both guard delay slots without a redundant call-slot move. */
    Resource *callResource;

    state = arg0->state;
    ctx = &D_80083160;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    arg0->callback = &D_80097C78;
    arg0->state += 1;
    goto done;

state_one:
    /* MATCH: Prevent propagation of the a3 copy into the a0 argument setup. */
    ASM_KEEP_NV(resource);
    if ((D_80083460[1] & 4) == 0 && (arg0->flags & 0x10) != 0) {
        guard = ctx->flags & 0x20;
        callResource = arg3;
        if (guard != 0) {
            guard = func_800A5C70(callResource);
            callResource = arg3;
            if (guard != 0) {
                flags = D_80083460;
                flags[1] |= 0x80;
            }
        }
        if ((func_80042900(callResource, 1) << 16) == 0) {
            arg0->callback = 0;
            D_80083460[5] += 1;
            arg0->state += 1;
        } else {
            func_80099F70(arg3->value);
            func_80099F04(arg3->value);
            D_80083460[1] |= 0x812;
        }
    }
    goto done;

state_two:
    arg3->flags &= ~0x200;
    func_80099F70(arg3->value);
    func_80099F04(arg3->value);
    D_80083460[1] |= 0x812;
    arg0->callback = D_80096384;
    D_80083460[5] -= 1;
    goto done;

done:
    arg0->counter += 1;
}
