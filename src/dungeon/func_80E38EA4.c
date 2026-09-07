#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_801726A4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801726A4_0;   /* arg0 in func_801726A4 */



typedef struct S_801726A4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801726A4_3;   /* arg1 in func_801726A4 */



extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80174690(void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80170EE4[];
extern u8 D_80176600[];
extern u8 D_80176668[];

void func_801726A4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u16 flags;
    u16 timer;
    s32 state;

    state = ((S_801726A4_0 *)arg0)->unk_9B;
    if (state != 1) {
        if ((s32)state < 2) {
            if (state == 0) {
                goto state_zero;
            }
            return;
        }

        if (state == 2) {
            goto state_two;
        }
        if (state == 3) {
            goto state_three;
        }
        return;
    }
    goto state_one;

state_zero:
    ((S_801726A4_0 *)arg0)->unk_98 |= 1;
    ((S_801726A4_0 *)arg0)->unk_9B++;

state_one:
    flags = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
    if (flags & 0x8000) {
        ((S_801726A4_0 *)arg0)->unk_9B = 3;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
        return;
    }

    if (flags & 0x6000) {
        ((S_801726A4_3 *)arg1)->unk_0C =
            ((S_801726A4_3 *)arg1)->unk_10 =
            ((S_801726A4_3 *)arg1)->unk_14 = 0;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80176600;
        func_80047784(arg2,
            D_80176600[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        func_80174690((u8 *)arg0 - 0x20);
        ((S_801726A4_0 *)arg0)->unk_96 = 0;
        ((S_801726A4_0 *)arg0)->unk_9B++;
        func_800A56E0(0x804);
        return;
    }
    return;

state_two:
    timer = ((S_801726A4_0 *)arg0)->unk_96 + 1;
    ((S_801726A4_0 *)arg0)->unk_96 = timer;

    if ((s16)timer == state ||
        (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
    }

    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80176668;
        func_80047784(arg2,
            D_80176668[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((S_801726A4_0 *)arg0)->unk_9B++;
        ((S_801726A4_0 *)arg0)->unk_98 &= 0xFFFE;
        return;
    }
    return;

state_three:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        func_800AD594(arg3, 0x100);
        ((S_801726A4_0 *)arg0)->unk_8C = D_80170EE4;
        D_8008346C = 0;
        (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        func_800A4ACC(arg3);
    }
}
