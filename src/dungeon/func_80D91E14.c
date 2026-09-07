#include "common.h"

#define U8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define S8(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void func_80047784(void *, s32, s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800AD594(void *, s32);
extern void func_800C8A3C(void *, s32, s32);

extern s16 D_80083228;
extern s32 D_8008346C;
extern void *D_800E3DE8;
extern u8 D_80170854[];
extern u8 D_80170E68;
extern u8 D_801738A4[];

void func_80173614(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 first;
    s32 result;
    s32 saved_first;
    void *object;
    u8 state;

    state = U8(arg0, 0x9B);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    result = func_80099734(arg3, first = func_800990FC());
    saved_first = first;
    first = result;
    func_80099290(func_80099194(D_80170854, first));
    func_800A5720(saved_first);
    object = func_800A05A4(arg3, U8(arg2, 0x24), U8(arg2, 0x25),
                           S16(arg3, 0x2A), 0x10);
    PTR(arg3, 0x60) = object;
    PTR(arg2, 0x2C) = D_801738A4;
    func_80047784(arg2,
        D_801738A4[((D_80083228 + S16(arg3, 0x2A) + 0x100) >> 9) & 7],
        0);
    func_800A56E0(0x812);
    U8(arg0, 0x9B) = U8(arg0, 0x9B) + 1;
    S32(arg1, 0x14) = 0;
    S32(arg1, 0x10) = 0;
    S32(arg1, 0x0C) = 0;
    goto done;

state_one:
    if (!(U16(arg2, 0x14) & 0xE000)) {
        goto done;
    }
    func_800AD594(arg3, 0xC00);
    PTR(arg0, 0x8C) = &D_80170E68;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (S8(arg3, 0x6D) == 0) {
        U16(arg3, 0x46) &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }
    object = PTR(arg3, 0x60);
    if (object != 0) {
        func_800C8A3C(object, 0x10, 0x10);
    }

done:
    return;
}

/* MECHANISM: True-space func_80173614 turns 0x80173780/0x80173798 into local CFG joins
   and orders state-zero before state-one, preserving the 0x30 frame and five held bases.
   Byte-scaled table indexing keeps lbu/shift-nine; distinct result/saved_first lifetimes
   emit retail's a1<-v0 and call-delay s0<-a1 around func_80099734. */
