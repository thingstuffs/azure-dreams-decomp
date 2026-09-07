#include "common.h"

typedef struct {
    u8 pad0[2];
    s16 field2;
} Object;

typedef struct {
    u8 pad0[0xC];
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF[0xD];
    u16 field1C;
    u16 field1E;
} Effect;

extern s32 D_800814A0[3];

void func_800B8E18(Object *arg0, s32 unused, Effect *arg2) {
    u16 value;
    u8 timer;
    s32 *global = D_800814A0;

    value = arg2->field1E;
    value = value - ((value * arg0->field2) / 24);
    arg2->field1E = value;
    arg2->field1C = value;
    timer = arg2->fieldE - (arg0->field2 * 8);
    arg2->fieldE = timer;
    arg2->fieldD = timer;
    arg2->fieldC = timer;
    if (!(timer & 0xFF)) {
        *(u16 *)((u8 *)arg0 - 2) = (u16)(*(u16 *)((u8 *)arg0 - 2) | 0x8000);
        global[0] = global[0] | 0x8000;
    }
}

/* MECHANISM: Frameless leaf; the three-argument ABI naturally keeps arg0 in a1 and arg2 in a2.
   A short-lived D_800814A0 base moves its page load into the conditional branch delay slot.
   gcc 2.7.2-cdk-G0 folds the low offset into lw, eliminating the extra address word. */
