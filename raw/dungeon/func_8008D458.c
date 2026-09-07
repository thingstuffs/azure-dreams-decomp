#include "common.h"

typedef struct {
    u8 pad00[8];
    s32 field08;
    u8 pad0c[0x80];
    void *field8c;
    u8 pad90[6];
    u16 countdown;
    u8 pad98[3];
    u8 state;
    u8 pad9c[0x30];
    u8 *table;
    u8 padd0[0x3e];
    s16 field10e;
    s32 field110;
    s32 field114;
} S_8003E2D8;

typedef struct {
    u8 pad00[8];
    s32 field08;
    u8 pad0c[8];
    u16 flags;
    u8 pad16[0x16];
    void *field2c;
} S_arg2;

typedef struct {
    u8 pad00[0x2a];
    s16 coord;
} S_arg3;

typedef struct {
    u8 pad00[0xc8];
    s16 fieldc8;
} S_global83160;

extern S_global83160 D_80083160;
extern s16 D_80083228[5];
extern s16 D_8008346A[];
extern volatile u16 D_80013714[];
extern u8 D_800DD148[];
extern u8 D_800DD150[];
extern u8 D_8008ACDC[];

extern s32 func_8003DE58(s32, void *, void *, s32);
extern void func_80048A44(void *, u8, s16, s32);
extern void func_8008D368(void *, void *, void *, u8 *, s32);
extern void func_80091934(void *, void *, void *);
extern void func_800D7A14(s32);

void func_80092BB8(S_8003E2D8 *arg0, void *arg1, S_arg2 *arg2, S_arg3 *arg3) {
    s32 state;
    s32 sp18;
    s32 index;

    state = arg0->state;
    if (state == 1) {
        goto state1_body;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto state0_body;
        }
        goto done;
    }
    if (state == 2) {
        goto state2_body;
    }
    if (state == 0x10) {
        goto state10_body;
    }
    goto done;

state0_body:
    if ((s32)((((s32)D_80083160.fieldc8 + arg3->coord + 0x100) >> 9) & 7) == 2) {
        u8 *table;

        table = arg0->table;
        arg2->field2c = table;
        index = (((s32)D_80083160.fieldc8 + arg3->coord + 0x100) >> 9) & 7;
        func_80048A44(arg2, table[index], arg0->field10e, 1);
        arg0->state++;
    } else {
        arg3->coord = (u16)arg3->coord + 0x200;
    }
    return;

state1_body:
    if (*D_80013714 & 8) {
        if (arg2->flags & 0x6000) {
            if (arg2->field2c == D_800DD148) {
                arg0->state = 0x10;
            } else {
                goto state2_store;
            }
        }
    } else if ((func_8003DE58(arg2->field08, arg2, &sp18, 0) != 0) || (arg2->flags & 0x8000)) {
        func_800D7A14(arg0->field114);
        arg0->state++;
    }
    return;

state2_body:
    if ((arg2->flags & 0x8000) || (*D_8008346A < 2)) {
        if (arg0->field110 != 0) {
            func_80091934(arg0, arg1, arg2);
            return;
        }
        arg2->field2c = D_800DD150;
        func_80048A44(arg2, D_800DD150[(((s32)D_80083228[0] + arg3->coord + 0x100) >> 9) & 7], 2, 1);
        goto state2_store;
    }
    goto done;

state2_store:
    arg0->field8c = D_8008ACDC;
    goto done;

state10_body:
    {
        u16 countdown;

        countdown = arg0->countdown - 1;
        arg0->countdown = countdown;
        if ((s32)(countdown << 16) <= 0) {
            func_8008D368(arg0, arg1, arg2, D_800DD150, 0);
        }
    }

done:
    return;
}
