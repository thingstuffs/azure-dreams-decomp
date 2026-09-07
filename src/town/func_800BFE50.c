#include "common.h"

typedef struct Func800BFE50Object {
    u8 pad00[0x48];
    s32 field48;
    u8 pad4C[4];
    s32 field50;
    u8 pad54[0x68 - 0x54];
    s16 field68;
    u8 pad6A[0x95 - 0x6A];
    u8 field95;
    u8 pad96[0xA0 - 0x96];
    s32 fieldA0;
    s32 fieldA4;
} Func800BFE50Object;

extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);
extern void func_8008F074(void *, void *, void *);
extern void func_800BD66C();
extern u8 D_80045340[];
extern u8 D_800BCE78[];
extern u8 D_800D20CC[];
extern s32 D_800D2130;
extern u8 D_800E9E7C[];

void func_800BD5B0(Func800BFE50Object *arg0, s32 *arg1, void *arg2) {
    u8 state;

    *(void **)((u8 *)arg0 - 0x10) = D_800BCE78;
    arg0->field50 = 0;
    func_8004491C((u8 *)arg0 - 0x20, D_80045340);

    arg0->fieldA0 = arg1[0];
    arg0->fieldA4 = arg1[1];
    state = arg0->field95;

    switch (state) {
    default: {
        void *dispatch_arg = arg2;
        
        return func_800BD66C();
    }

    case 0:
        func_8008F074(arg0, arg1, D_800D20CC);
        func_8003DB94(arg2, D_800E9E7C, 0);
        arg0->field68 = 0;
        arg0->field48 = D_800D2130;
        return func_800BD66C();

    case 1:
        func_8003DB94(arg2, D_800E9E7C, 0);
        arg0->field68 = 0;
        break;
    }
}

/* MECHANISM: The natural 0x20 frame holds arg0/arg1/arg2 in s0/s1/s2 and preserves the default-first CFG.
   A block-local guarded $a0 carrier makes the beq delay-slot move the sole dispatcher-argument setup;
   the zero-argument call then lets LEAD 22 emit the retail j with a nop delay slot. */
