#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80174764_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80174764_0;   /* arg0 in func_80174764 */



typedef struct S_80174764_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80174764_3;   /* target in func_80174764 */

typedef struct S_80174764_4 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80174764_4;   /* ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in func_80174764 */



extern void func_80047784(void *, s16, s16);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80175AF4(void *, void *, void *);
extern s32 func_801761AC(void *);
extern s32 func_80176258(void *);
extern void func_801762A4(s32, void *);
extern void func_80176330(s32, void *);
extern void func_801763CC(s32, void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80171094;
extern u8 D_80176460[8];

void func_80174764(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u16 flags;
    u16 timer;
    void *target;

    switch (((S_80174764_0 *)arg0)->unk_9B) {
    case 0:
        flags = ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v;
        if (flags & 0x8000) {
            ((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v = flags | 0x6000;
            if (((Rec_D_800E3D7C *)arg3)->unk_14.as_s32 & 0x4000) {
                target = ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv;
                if (!func_80176258(target))
                    goto state0_cc_false;
                func_801763CC(1, ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv);
                goto state0_done;
state0_cc_false:
                func_801763CC(0, ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv);
                goto state0_done;
            }

            target = ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv;
            if (((S_80174764_3 *)target)->unk_14 & 0x4000) {
                if (!func_801761AC(target))
                    goto state0_330_false;
                func_80176330(1, ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv);
                goto state0_done;
state0_330_false:
                func_80176330(0, ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv);
                goto state0_done;
            }
            func_801761AC(target);
state0_done:
            ((S_80174764_0 *)arg0)->unk_9B = 2;
            return;
        }

        if (((Rec_D_80082E80 *)arg2)->unk_04.as_s8 == 1) {
            if (!(flags & 0x1000)) {
                if (!(flags & 0x6000)) {
                    break;
                }
            }
        } else if (!(flags & 0x6000)) {
            break;
        }

        func_80175AF4(arg0, arg1, arg2);
        if (((Rec_D_800E3D7C *)arg3)->unk_14.as_s32 & 0x4000) {
            func_801762A4(1, arg3);
        } else if (((S_80174764_4 *)(((Rec_D_800E3D7C *)arg3)->unk_60.as_pv))->unk_14 & 0x4000) {
            func_801762A4(0, arg3);
        }
        func_800A56E0(0x708);
        timer = 0x20;
        ((S_80174764_0 *)arg0)->unk_96 = timer;
        ((S_80174764_0 *)arg0)->unk_9B++;
        break;

    case 1:
        timer = ((S_80174764_0 *)arg0)->unk_96 - 1;
        ((S_80174764_0 *)arg0)->unk_96 = timer;
        if ((timer << 16) == 0 || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0x8000)) {
            if (((Rec_D_800E3D7C *)arg3)->unk_14.as_s32 & 0x4000) {
                target = ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv;
                if (!func_80176258(target))
                    goto state1_cc_false;
                func_801763CC(1, ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv);
                goto state1_done;
state1_cc_false:
                func_801763CC(0, ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv);
                goto state1_done;
            } else {
                target = ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv;
                if (((S_80174764_3 *)target)->unk_14 & 0x4000) {
                    if (!func_801761AC(target))
                        goto state1_330_false;
                    func_80176330(1, ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv);
                    goto state1_done;
state1_330_false:
                    func_80176330(0, ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv);
                    goto state1_done;
                } else {
                    func_801761AC(target);
                }
            }
state1_done:
            ((S_80174764_0 *)arg0)->unk_96 = 4;
            ((S_80174764_0 *)arg0)->unk_9B++;
        }
        break;

    case 2:
        timer = ((S_80174764_0 *)arg0)->unk_96 - 1;
        ((S_80174764_0 *)arg0)->unk_96 = timer;
        if ((timer << 16) == 0 || (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000)) {
            func_800AD594(arg3, 0x400);
            func_800A2B04(arg1, ((Rec_D_80082E80 *)arg2)->unk_24, ((Rec_D_80082E80 *)arg2)->unk_25);
            ((S_80174764_0 *)arg0)->unk_8C = &D_80171094;
            D_8008346C = 0;
            (*(u16 *)((u8 *)arg3 + 0x46)) &= 0x7FFF;
        }
        break;
    }

    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        s32 index;

        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80176460;
        index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
        func_80047784(arg2, D_80176460[index & 7], 0);
        ((S_80174764_0 *)arg0)->unk_98 &= 0xFFF7;
    }
}
