#include "common.h"

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 pad6[2];
} S_80174CF0;

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 pad4[3];
} S_800DCE60;

extern S_80174CF0 D_80174CF0;
extern S_800DCE60 D_800DCE60;
extern s32 D_800832B4[3];
extern void func_8004D7A8(s32);
extern void func_8004D294();

void func_8017140C(void)
{
    S_80174CF0 *p = &D_80174CF0;

    p->unk4 = 0;
    D_800832B4[0] = 0;
    D_80174CF0.unk0 = D_800DCE60.unk0;
    p->unk2 = D_800DCE60.unk2;
    func_8004D7A8(1);
    func_8004D294(0, p, 10);
}

/* MECHANISM: func_8004D7A8 has one s32 argument; retail a1 is a copy temporary,
   not a call argument. A held D_80174CF0 pointer gives the sole s0 save and lets
   direct u16 copies naturally color the page/copy roles as a2, a1, and v1. */
