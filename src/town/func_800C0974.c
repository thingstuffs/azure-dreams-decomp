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
extern void func_800BE1BC(S1 *, s32); /* j-only sibcall dispatcher */
extern void func_800BE1FC(void);      /* j-only sibcall dispatcher */

/* Pre-existing rodata jump table in the retail overlay blob. */
extern void *D_80089670[];

void func_800BE0D4(S0 *self, s32 arg1, S1 *arg2) {
    S0 *obj = self;
    S1 *dst = arg2;
    s32 state;
    static void *const keepalive[7] = {
        &&L0, &&L1, &&L2, &&L3, &&L4, &&L0After, &&L1After
    };

    func_800478B8(dst);
    state = obj->state;
    if ((u32)state < 5) {
        goto *D_80089670[state];
    }
    return;

L0:
    if (func_800352FC() && func_800C2AB4(obj)) {
        S1 *callArg = dst;
        ASM_KEEP(callArg);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800BE1BC(callArg, obj->fieldA4);
    }
L0After:
    return;
L1:
    if (dst->field14 & 0x6000) {
        S1 *callArg = dst;
        ASM_KEEP(callArg);   /* MATCH pin: retail delay-slot contents depend on it */
        func_800BE1BC(callArg, obj->fieldA8);
    }
L1After:
    return;
L2:
    if (func_800352FC() && func_800C2AB4(obj)) {
        func_800BE1FC();
        return;
    }
    goto Linc;
L3:
    if (!(func_800352FC() && func_800C2AB4(obj))) {
        return;
    }
    func_8003DB94(dst, obj->fieldA0, 0);
Linc:
    obj->state = (u16)obj->state + 1;
    func_800BE1FC();
    return;
L4:
    if (func_800352FC()) {
        if (func_800C2AB4(obj)) {
            return;
        }
    }
    obj->state = 0;
}
