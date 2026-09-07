#include "common.h"

/* Sibling of func_8004B298/func_8004B2E0/func_8004B530 (D_800814A0 flags
 * word tail). arg0 is a countdown/timer-like entity struct: halfword at
 * +2 is a counter decremented each call; when it underflows to <=0 the
 * entity is finalized: writes into *(+0xC)->+0x88, sets the 0x8000 "used"
 * bit both one halfword before arg0 and on the global flags word
 * D_800814A0, and decrements a counter field at D_80083460+0xA. */
extern int D_800814A0;
extern u16 D_80083460[];

void func_800C1EC4(u16 *arg0) {
    s16 temp;
    u16 *unk0C;

    temp = arg0[1] - 1;
    arg0[1] = temp;
    if (temp <= 0) {
        unk0C = *(u16 **)((u8 *)arg0 + 0xC);
        unk0C[0x88 / 2] = arg0[4];
        arg0[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
        D_80083460[5]--;
    }
}
