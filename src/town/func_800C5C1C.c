#include "common.h"

extern s32 func_80033D38(void);
extern void func_800C3780(void *arg0, void *arg1, void *arg2);
extern void func_800C37C4(void *arg0, void *arg1, void *arg2);

typedef void (*FuncPtr)(void *, void *, void *);

void func_800C337C(void *arg0, void *arg1, void *arg2) {
    u8 *obj = (u8 *) arg0;
    u8 state;

    if (func_80033D38() != 0) {
        obj[0x15] = 1;
    }
    state = obj[0x94];
    if (state == 0) {
        *(u16 *)(obj + 0x72) = *(u16 *)(obj + 0x6E);
        func_800C3780(arg0, arg1, arg2);
        return;
    }
    if (state == 1) {
        func_800C37C4(arg0, arg1, arg2);
        return;
    }
    (*(FuncPtr *)((((volatile u8 *) obj)[0x94] * 4) + *(s32 *)(obj + 0x58) - 8))(arg0, arg1, arg2);
}
