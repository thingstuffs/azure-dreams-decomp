#include "common.h"

typedef struct S_80020618_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    u16 unk_02;
    s32 unk_04;
    s16 * unk_08;
    void * unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
} S_80020618_0;   /* arg0 in func_80020618 */

typedef struct S_80020618_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80020618_1;   /* owner in func_80020618 */



extern void func_800537D0();
extern s32 strlen();
extern s32 D_800814A0;

/* Displays a timed message and signals completion when its owner is ready. */
void func_80020618(void *message)
{
    s16 state;
    u16 timer;
    void *owner;

    owner = ((S_80020618_0 *)message)->unk_0C;
    func_800537D0(
        *((S_80020618_0 *)message)->unk_08,
        strlen(((S_80020618_0 *)message)->unk_04),
        ((S_80020618_0 *)message)->unk_04);

    state = ((S_80020618_0 *)message)->unk_00.s;
    switch (state) {
    case 0:
        timer = ((S_80020618_0 *)message)->unk_02 - 1;
        ((S_80020618_0 *)message)->unk_02 = timer;
        if ((timer << 16) <= 0) {
            ((S_80020618_0 *)message)->unk_1C &= 0xFFFD;
            ((S_80020618_0 *)message)->unk_00.u++;
        }
        break;

    case 1:
        if (((S_80020618_1 *)owner)->unk_2A & 1) {
            (*(u16 *)((u8 *)message + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
        break;
    }
}
