#include "common.h"

typedef struct {
    s16 state;
    u16 count;
    s32 value0;
    s32 value1;
    s32 value2;
    s32 step0;
    s32 step1;
    s32 step2;
} FuncState;

typedef struct {
    s32 pad0[5];
    u16 flags;
    u16 pad1[3];
    u16 count;
    u16 value;
} FuncOutput;

extern s32 D_800814A0[3];

extern s32 func_800644B8(u32);
extern void func_800C77D0(void *, void *, s32, s32);
extern void func_800478B8(void *);
extern void func_80047784(void *, s32, s32);

void func_80175978(FuncState *arg0, void *arg1, FuncOutput *arg2) {
    u16 count;
    void *call_arg0;

    count = arg0->count + 1;
    arg0->count = count;
    if (arg0->state != 0) {
        if (arg0->state == 1)
            goto special_case;
        call_arg0 = (void *)((s8 *)arg0 - 0x20);
        goto common_call;
    }

    arg2->value = arg2->value + 0x40;
    arg2->count = arg2->value;
    arg0->value0 = arg0->value0 + arg0->step0;
    ((s32 *)arg1)[0] = arg0->value0;
    arg0->value1 = arg0->value1 + arg0->step1;
    ((s32 *)arg1)[1] = arg0->value1;
    arg0->value2 = arg0->value2 + arg0->step2;
    ((s32 *)arg1)[2] = arg0->value2 - ((func_800644B8((s16)arg0->count << 6) >> 4) * 0xC000);
    if ((s16)arg0->count >= 0x20) {
        arg0->count = 0;
        arg0->state = arg0->state + 1;
    }
    goto state0_tail;

special_case:
    if ((s16)count < 4) {
        goto state0_tail;
    }
    *((u16 *)arg0 - 1) |= 0x8000;
    D_800814A0[0] |= 0x8000;
    goto done;

state0_tail:
    call_arg0 = (void *)((s8 *)arg0 - 0x20);

common_call:
    func_800C77D0(call_arg0, arg1, 8, 0x300);
    func_800478B8(arg2);
    if (arg2->flags & 0x6000) {
        func_80047784(arg2, 0x47, 0);
    }

done:
    return;
}
