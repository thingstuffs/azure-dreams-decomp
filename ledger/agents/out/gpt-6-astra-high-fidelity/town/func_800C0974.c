#include "common.h"

typedef struct S0 {
    char pad0[0x68];
    s16 state;   /* 0x68 */
    char pad6A[0xA0 - 0x6A];
    s32 fieldA0; /* 0xA0 */
    s32 fieldA4; /* 0xA4 */
    s32 fieldA8; /* 0xA8 */
} S0;

typedef struct S1 {
    char pad0[0x14];
    u16 field14; /* 0x14 */
} S1;

extern void func_800478B8(S1 *);
extern s32 func_800352FC(void);
extern s32 func_800C2AB4(S0 *);
extern void func_8003DB94(S1 *, s32, s32);

/* Pre-existing rodata jump table in the retail overlay blob. */
extern void *D_80089670[];

void func_800BE0D4(S0 *self, s32 arg1, S1 *arg2) {
    S0 *obj = self;
    S1 *dst = arg2;
    s32 state;
    s32 callValue;
    static void *const keepalive[5] = {
        &&L0, &&L1, &&L2, &&L3, &&L4
    };

    func_800478B8(dst);
    state = obj->state;
    if ((u32)state < 5) {
        goto *D_80089670[state];
    }
    return;

L0:
    if (func_800352FC() && func_800C2AB4(obj)) {
        callValue = obj->fieldA4;
        goto Lcall;
    }
L0After:
    return;
L1:
    if (dst->field14 & 0x6000) {
        callValue = obj->fieldA8;
        goto Lcall;
    }
L1After:
    return;
L2:
    if (func_800352FC() && func_800C2AB4(obj)) {
        return;
    }
    goto Linc;
L3:
    if (!(func_800352FC() && func_800C2AB4(obj))) {
        return;
    }
    callValue = obj->fieldA0;
Lcall:
    func_8003DB94(dst, callValue, 0);
Linc:
    obj->state = (u16)obj->state + 1;
    return;
L4:
    if (func_800352FC()) {
        if (func_800C2AB4(obj)) {
            return;
        }
    }
    obj->state = 0;
}
