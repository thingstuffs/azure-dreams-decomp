#include "common.h"
#include "m2c_compat.h"

extern s16 D_80083228[5];
extern s32 D_80170F68;
extern s32 D_8008346C[];
extern void *D_800E3DE8[];
extern u8 D_80173FE8[];
extern u8 D_80174010[];

typedef struct {
    u8 pad0[0x8C];
    s32 *field8C;
    u8 pad90[6];
    u16 field96;
    u16 field98;
    u8 pad9A;
    u8 field9B;
} Obj0;

typedef struct {
    u8 pad0[0x14];
    u16 field14;
    u8 pad16[0x0E];
    u8 field24;
    u8 field25;
    u8 pad26[6];
    u8 *field2C;
} Obj2;

typedef struct {
    u8 pad0[0x2A];
    s16 field2A;
    u8 pad2C[0x1A];
    u16 field46;
    u8 pad48[0x25];
    s8 field6D;
} Obj3;

extern void func_80047784(Obj2 *, u8, s32);
extern void func_8009C12C(Obj3 *, Obj2 *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(Obj3 *);
extern void func_800A56E0(s32);
extern void func_800AD594(Obj3 *, s32);

void func_801727CC(Obj0 *arg0, M2C_UNK arg1, Obj2 *arg2, Obj3 *arg3) {
    s16 count;
    s32 state;
    s32 volume;

    state = arg0->field9B;
    count = arg0->field96 - 1;
    arg0->field96 = count;
    if (state == 1)
        goto state_one;
    if (state < 2) {
        if (state == 0)
            goto state_zero;
        goto done;
    }
    if (state == 0xFF)
        goto state_ff;
    goto done;

state_zero:
    if (arg2->field14 & 0x8000) {
        arg0->field9B = 0xFF;
        arg2->field14 |= 0x6000;
        func_8009C12C(arg3, arg2, arg3->field2A, 1);
        goto done;
    }
    if (arg0->field98 & 0x8000) {
        arg2->field2C = D_80174010;
        count = 10;
    } else {
        arg2->field2C = D_80173FE8;
        count = 4;
    }
    arg0->field96 = count;
    func_80047784(arg2, arg2->field2C[(((s32) (D_80083228[0] + arg3->field2A + 0x100) >> 9) & 7)], 0);
    arg0->field9B++;
    goto done;

state_one:
    if ((count << 16) > 0)
        goto done;
    func_800A56E0(0x809);
    func_8009C12C(arg3, arg2, arg3->field2A, 1);
    arg0->field9B = 0xFF;
    goto done;

state_ff:
    if ((arg2->field14 & 0xE000) == 0)
        goto done;
    func_800A2B04(arg1, arg2->field24, arg2->field25);
    volume = 0x100;
    if (arg0->field98 & 0x8000)
        volume = 0x800;
    func_800AD594(arg3, volume);
    arg0->field8C = &D_80170F68;
    *D_8008346C = 0;
    func_800A4ACC(arg3);
    if (arg3->field6D == 0) {
        arg3->field46 &= 0x7FFF;
        goto done;
    }
    *D_800E3DE8 = (void *)((s8 *)arg3 - 0x20);

done:
    return;
}
