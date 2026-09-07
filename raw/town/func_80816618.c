#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_800537D0();
extern s32 strlen();
extern s32 D_800814A0;

void func_80020618(void *arg0)
{
    s16 state;
    u16 timer;
    void *owner;

    owner = FIELD(arg0, void *, 0xC);
    func_800537D0(
        *FIELD(arg0, s16 *, 8),
        strlen(FIELD(arg0, s32, 4)),
        FIELD(arg0, s32, 4));

    state = FIELD(arg0, s16, 0);
    switch (state) {
    case 0:
        timer = FIELD(arg0, u16, 2) - 1;
        FIELD(arg0, u16, 2) = timer;
        if ((timer << 16) <= 0) {
            FIELD(arg0, u16, 0x1C) &= 0xFFFD;
            FIELD(arg0, u16, 0)++;
        }
        break;

    case 1:
        if (FIELD(owner, u16, 0x2A) & 1) {
            FIELD(arg0, u16, -2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;
    }
}

/* MECHANISM: A natural 0/1 switch preserves retail's dispatch/default/case order.
   arg0 and owner stay live in s0/s1 across both calls; case 0 performs the
   missing state increment and case 1 uses the true D_800814A0 object. */
