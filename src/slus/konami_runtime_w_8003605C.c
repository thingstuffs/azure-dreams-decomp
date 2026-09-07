#include "common.h"

#include "common.h"

typedef struct RuntimeObject {
    void *sub;
    u8 pad04[0x40];
    u8 *base;
    u8 active;
    u8 pad49;
    s16 index;
    u8 state;
    u8 state2;
    u8 pad4E[0x1A];
    void (*handler)(struct RuntimeObject *, s32, s32, s32);
} RuntimeObject;

extern void func_80033C84(void *);
extern void func_80035090(void *);
extern void func_80036900(RuntimeObject *);
extern void func_8003FFF0(void *);
extern void func_80044A50(void *);

void func_8003605C(RuntimeObject *arg0, s32 arg1, s32 arg2, s32 state)
{
    u8 *entry;
    s32 unset = 0xFF;

    if (arg0->active != 0) {
        entry = arg0->base;
        entry += arg0->index;
        state = entry[0x4C];

        if (state == unset) {
            entry[0x50] = 1;
            func_80033C84(arg0->sub);
            func_80035090((u8 *)arg0 + 0x54);
            arg0 = (RuntimeObject *)((u8 *)arg0 - 0x20);
            func_80044A50(arg0);
            func_8003FFF0(arg0);
            return;
        }

        if (state == 0xFE) {
            arg0->state = unset;
            arg0->state2 = unset;
            arg0->handler = func_80036900;
        }
    }

    arg0->handler(arg0, arg1, arg2, state);
}
