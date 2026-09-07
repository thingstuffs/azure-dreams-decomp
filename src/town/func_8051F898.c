#include "common.h"

typedef s32 (*Callback1)(s32);
typedef s32 (*Callback2)(s32, void *);

extern s8 D_80016000[];

s32 func_80017098(void) {
    s8 *base;
    void *call_state;
    void *final_state;
    s32 value;
    s32 current;

    base = D_80016000;
    (*(Callback1 *)((s8 *)*(void **)((s8 *)*(void **)base + 0x20) + 0x258))(15);

    {
        void *object;
        void *methods;

        object = *(void **)base;
        do { methods = *(void * volatile *)((s8 *)object + 0x20); } while (0);
        call_state = *(void * volatile *)((s8 *)object + 0x1C);
        value = *(s32 *)((s8 *)call_state + 4);
        (*(Callback2 *)((s8 *)methods + 0x248))(1, call_state);
    }

    (*(Callback1 *)((s8 *)*(void **)((s8 *)*(void **)base + 0x20) + 0x244))(1);

    final_state = *(void **)((s8 *)*(void **)base + 0x1C);
    if (*(s32 *)final_state != 3) {
        return 0;
    }

    current = *(s32 *)((s8 *)final_state + 4);
    value -= 0x40;
    if ((value < current) && (current < value + 0x80)) {
        *(s32 *)((s8 *)final_state + 4) = value;
        return 1;
    }
    return 0;
}
