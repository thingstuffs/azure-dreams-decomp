#include "common.h"

typedef struct S_80026FB0_0 {
    u8 pad_00[0x64];
    union { s16 s; u16 u; } unk_64;   /* accessed as both */
    s16 unk_66;
} S_80026FB0_0;   /* arg0 in func_80026FB0 */

typedef struct S_80026FB0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80026FB0_1;   /* arg2 in func_80026FB0 */



extern void func_80027068(void) __attribute__((noreturn));
extern s32 D_800814A0;

void func_80026FB0(void *arg0, s32 arg1, void *arg2)
{
    s16 state;
    s32 timer;
    s32 value;

    state = ((S_80026FB0_0 *)arg0)->unk_64.s;
    switch (state) {
    default:
        func_80027068();

    case 0:
        timer = (u16)((S_80026FB0_0 *)arg0)->unk_66 - 1;
        ((S_80026FB0_0 *)arg0)->unk_66 = timer;
        if ((timer << 16) <= 0) {
            ((S_80026FB0_0 *)arg0)->unk_66 = 0x10;
            ((S_80026FB0_0 *)arg0)->unk_64.u += 1;
            func_80027068();
        }
        break;

    case 1:
        value = ((S_80026FB0_1 *)arg2)->unk_0C;
        value = value + ((0x80 - value) / ((S_80026FB0_0 *)arg0)->unk_66);
        ((S_80026FB0_1 *)arg2)->unk_0C = value;
        ((S_80026FB0_1 *)arg2)->unk_0E = value;
        ((S_80026FB0_1 *)arg2)->unk_0D = value;
        timer = (u16)((S_80026FB0_0 *)arg0)->unk_66 - 1;
        ((S_80026FB0_0 *)arg0)->unk_66 = timer;
        if ((timer << 16) <= 0) {
            (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;

    }
}

/* MECHANISM: The zero-argument noreturn tails keep this function frameless.
   Lexically placing default first emits its jump inline before cases 0 and 1.
   Direct scalar D_800814A0 access preserves retail's %hi/%lo displacement. */
