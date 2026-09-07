#include "common.h"

#include "common.h"

typedef struct {
    u8 pad0[8];
    u32 field8;
    u8 padC[4];
} Func80038128Global;

typedef struct {
    u8 pad0[0x10];
    void (*func10)(void *);
    u8 pad14[4];
    u16 half18;
    u8 pad1A[0x14];
    u8 field2E;
    u8 pad2F[0x58];
    s8 field87;
} Func80038128State;

extern Func80038128Global D_80083160;
extern void func_80038A10(void *arg0);

void func_80038128(Func80038128State *arg0) {
    Func80038128Global *global = &D_80083160;

    if (arg0->field87 == 0) {
        if ((global->field8 & 0x20) != 0) {
            if (arg0->field2E == 0) {
                arg0->field2E = 1;
            }
            arg0->half18 = 0;
            arg0->func10 = func_80038A10;
            return;
        }
    }

    arg0->half18 -= 1;
    if ((s16)arg0->half18 <= 0) {
        arg0->func10 = func_80038A10;
    }
}
