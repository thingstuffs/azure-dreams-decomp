#include "common.h"

typedef struct S_80050CDC_0 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
} S_80050CDC_0;   /* arg2 in func_80050CDC */

typedef struct S_80050CDC_1 {
    u8 unk_00;
    u8 unk_01;
    union { u16 u16; u8 u8; } unk_02;   /* accessed as both */
    u8 pad_04[0x4];
    u16 unk_08;
    u8 pad_0A[0x2];
    u16 unk_0C;
} S_80050CDC_1;   /* part in func_80050CDC */

typedef struct S_80050CDC_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80050CDC_2;   /* arg0 in func_80050CDC */



extern void func_8004B248(void *arg0);
extern s32 D_800814A0;

/* Update and fade the effect parts, then signal completion when the timer expires. */
void func_80050CDC(void *effect, void *unused, void *parts)
{
    s32 ticks_left;
    u8 color;
    void *part;

    part = ((S_80050CDC_0 *)parts)->unk_08;
    ((S_80050CDC_1 *)part)->unk_02.u16 -= 0x40;
    part = ((S_80050CDC_0 *)parts)->unk_04;
    ((S_80050CDC_1 *)part)->unk_0C += 0x20;
    part = ((S_80050CDC_0 *)parts)->unk_04;
    ((S_80050CDC_1 *)part)->unk_08 -= 0x40;
    part = ((S_80050CDC_0 *)parts)->unk_04;
    color = ((S_80050CDC_1 *)part)->unk_02.u8 - 0x20;
    ((S_80050CDC_1 *)part)->unk_02.u8 = color;
    ((S_80050CDC_1 *)part)->unk_01 = color;
    ((S_80050CDC_1 *)part)->unk_00 = color;

    ticks_left = ((S_80050CDC_2 *)effect)->unk_08 - 1;
    ((S_80050CDC_2 *)effect)->unk_08 = ticks_left;
    if (ticks_left == -1) {
        func_8004B248((u8 *)effect + 0x6C);
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
