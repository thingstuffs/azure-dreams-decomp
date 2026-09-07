#include "common.h"
#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 pad0[8];
    s32 flags;
    u8 padC[0xBC];
    s16 offset_c8;
} S_80083160;

typedef struct {
    u8 pad0[0x14];
    u16 flags14;
    u8 pad16[0x16];
    u8 *table;
} Arg2Struct;

typedef struct {
    u8 pad0[0x1C];
    s32 flags1c;
    u8 pad20[0xA];
    s16 angle;
    u8 pad2C[0x30];
    s32 val5c;
} Arg3Struct;

typedef struct {
    u8 pad0[0x8C];
    void *handler;
    u8 pad90[6];
    u16 timer;
    u8 pad98[3];
    u8 state;
    u8 pad9C[6];
    u16 flagsa2;
} Arg0Struct;

extern S_80083160 D_80083160;
extern u16 D_80083460[];
extern void *D_8008ACDC[];
extern u8 D_800DD0F8[];
extern s16 D_80083228[5];
extern void *D_8008B870;
extern u8 D_800DD0F0;

extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_80048A44(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80099F04(s32 arg0);
extern void func_80099F70(s32 arg0);
extern void func_800A56E0(s32 arg0);
extern s32 func_800A5C70(void);

void func_80090298(Arg0Struct *arg0, void *arg1, Arg2Struct *arg2, Arg3Struct *arg3) {
    s32 code;
    S_80083160 *base = &D_80083160;

    (void)arg1;
    switch (arg0->state) {
    case 0:
        if (arg2->flags14 & 0xE000) {
            arg2->table = &D_800DD0F0;
            func_80048A44(arg2, (&D_800DD0F0)[((s32)(base->offset_c8 + arg3->angle + 0x100) >> 9) & 7], 0, 1);
            arg0->handler = &D_8008B870;
            arg0->state = (s8)(arg0->state + 1);
        }
        break;

    case 1:
        if (!(arg0->timer & 0x1F)) {
            code = 0x50F;
            if (arg0->timer & 0x20) {
                code = 0x50E;
            }
            func_800A56E0(code);
        }
        if (!(D_80083460[1] & 4) && (arg0->flagsa2 & 0x10)) {
            if ((base->flags & 0x20) && (func_800A5C70() != 0)) {
                D_80083460[1] |= 0x80;
            }
            if ((func_80042900(arg3, 1) << 0x10) == 0) {
                arg2->table = D_800DD0F8;
                func_80048A44(arg2, D_800DD0F8[((s32)(*D_80083228 + arg3->angle + 0x100) >> 9) & 7], 0, 1);
                arg0->handler = NULL;
                D_80083460[5] += 1;
                arg0->state += 1;
            } else {
                func_80099F70(arg3->val5c);
                func_80099F04(arg3->val5c);
                D_80083460[1] |= 0x812;
            }
        }
        break;

    case 2:
        if (arg2->flags14 & 0xE000) {
            arg3->flags1c &= ~0x200;
            func_80099F70(arg3->val5c);
            func_80099F04(arg3->val5c);
            D_80083460[1] |= 0x812;
            arg0->handler = D_8008ACDC;
            D_80083460[5] -= 1;
        }
        break;
    }

    arg0->timer += 1;
}
