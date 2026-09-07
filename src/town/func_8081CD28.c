#include "common.h"

typedef struct S_80026D28_0_pre {
    u16 unk_00;
} S_80026D28_0_pre;   /* the 0x2 bytes before arg0 in func_80026D28, addressed as arg0[-1] */

typedef struct S_80026D28_0 {
    u8 pad_00[0x50];
    union { s16 s; u16 u; } unk_50;   /* accessed as both */
    u16 unk_52;
} S_80026D28_0;   /* arg0 in func_80026D28 */


extern void func_80026DB4() __attribute__((noreturn));
extern s32 func_80053DA8();
extern s32 D_800814A0[3];


void func_80026D28(void *arg0)
{
    s16 state;
    u16 timer;

    state = ((S_80026D28_0 *)arg0)->unk_50.s;
    if (state != 0) {
        if (state != 1) {
            return func_80026DB4();
        }
        goto tick;
    }

    func_80053DA8(0x603);
    ((S_80026D28_0 *)arg0)->unk_50.u = ((S_80026D28_0 *)arg0)->unk_50.u + 1;

tick:
    timer = ((S_80026D28_0 *)arg0)->unk_52 - 1;
    ((S_80026D28_0 *)arg0)->unk_52 = timer;
    if ((timer << 16) <= 0) {
        func_80053DA8(0x1603);
        ((S_80026D28_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
