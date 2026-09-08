#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern s16 func_800BCB04(u16, u16, s16);
extern void func_80173AE4(void) __attribute__((noreturn));

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_800E2380[8];
extern u8 D_800E2388[8];
extern u8 D_80170838[16];
extern s32 D_80171F1C;


typedef struct S_801737F8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    union { s16 s; u16 u; } unk_92;   /* accessed as both */
    u8 pad_94[0x2];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801737F8_0;   /* arg0 in func_801737F8 */

typedef struct S_801737F8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801737F8_1;   /* arg1 in func_801737F8 */



void func_801737F8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    static void *const keepalive[] = { &&L0, &&L1, &&L2, &&L3, &&L4 };

    state = ((S_801737F8_0 *)arg0)->unk_9B;
    if ((u32)state >= 5) {
        return;
    }
    goto *(((void **)D_80170838)[state]);

L0:
    ((S_801737F8_1 *)arg1)->unk_14 = 0;
    ((S_801737F8_1 *)arg1)->unk_10 = 0;
    ((S_801737F8_1 *)arg1)->unk_0C = 0;
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000) {
        ((S_801737F8_0 *)arg0)->unk_9B = 4;
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x6000;
        func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
        return;
    }
    if (((S_801737F8_0 *)arg0)->unk_92.s !=
        (s16)(func_800BCB04(((S_801737F8_1 *)arg1)->unk_02,
                            ((S_801737F8_1 *)arg1)->unk_06,
                            (s16)(((Rec_D_800E3D7C *)arg3)->unk_88.as_u16 - 0x20)) -
              ((Rec_D_800E3D7C *)arg3)->unk_88.as_u16)) {
        return;
    }
    ((S_801737F8_0 *)arg0)->unk_9B++;
    ((Rec_D_80082E80 *)arg2)->unk_10.as_s16 = 0x20;
    {
        u16 tail_flags;

        tail_flags = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v | 0x000C;
        ASM_TAILSLOT_PIN(tail_flags);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80173AE4();
    }

L1:
    (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_800E2380;
    func_80047784(arg2,
        D_800E2380[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    ((S_801737F8_0 *)arg0)->unk_96.u = 0;
    ((S_801737F8_0 *)arg0)->unk_9B++;
    return;

L2:
    {
        s32 ten = 10;
        u16 timer = ((S_801737F8_0 *)arg0)->unk_96.u + 1;

        ((S_801737F8_0 *)arg0)->unk_96.u = timer;
        if ((s16)timer == ten || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
            func_8009C12C(arg3, arg2, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, 1);
            ((S_801737F8_0 *)arg0)->unk_96.u = ten;
            ((S_801737F8_0 *)arg0)->unk_9B++;
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v |= 0x0800;
        }
        if (((S_801737F8_0 *)arg0)->unk_96.s == 9) {
            func_800A56E0(0x809);
            return;
        }
        return;
    }

L3:
    if (((S_801737F8_0 *)arg0)->unk_96.s > 0) {
        u16 timer = ((S_801737F8_0 *)arg0)->unk_96.u - 1;

        ((S_801737F8_0 *)arg0)->unk_96.u = timer;
        if ((timer << 16) != 0) {
            return;
        }
        ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xF7FF;
        ((S_801737F8_0 *)arg0)->unk_98 |= 8;
        (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_800E2388;
        func_80047784(arg2,
            D_800E2388[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

L4:
    if (((S_801737F8_0 *)arg0)->unk_92.s >= -0x1F) {
        ((S_801737F8_0 *)arg0)->unk_92.u -= 4;
        return;
    }
    ((S_801737F8_0 *)arg0)->unk_9B++;
    if (!(((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
        return;
    }
    func_800AD594(arg3, 0x100);
    ((S_801737F8_0 *)arg0)->unk_8C = &D_80171F1C;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v &= 0x7FFF;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000;
    ((S_801737F8_0 *)arg0)->unk_98 |= 8;
    ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v &= 0xFFF3;
}
