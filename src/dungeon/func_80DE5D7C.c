#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8017357C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_8017357C_0;   /* arg0 in func_8017357C */


typedef struct S_8017357C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8017357C_2;   /* global in func_8017357C */


typedef struct S_8017357C_4 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8017357C_4;   /* owner in func_8017357C */


extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801737DC(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 D_80170E5C[];
extern u8 D_80174520[];
extern u8 D_80174538[];


void func_8017357C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u8 state;
    u8 *effect;
    s32 index;

    state = ((S_8017357C_0 *)arg0)->unk_9B;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    {
    u8 *global;
    u8 *stateEffect;

    if ((((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) == 0) {
        return;
    }

    global = (u8 *)&D_80083460;
    stateEffect = D_80174538;
    ((S_8017357C_2 *)global)->unk_0A--;
    (*(void * *)((u8 *)arg2 + 0x2C)) = stateEffect;
    index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, stateEffect[index & 7], 0);
    ((S_8017357C_0 *)arg0)->unk_9B++;
    return;
    }

state_one:
    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        if (D_80083462 & 0x1000) {
            return;
        }

        if ((((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) &&
            func_800AA6B4(arg0, arg1, arg2, 0)) {
            return;
        }

        if ((s16)func_800A2C34(arg3) != 0) {
            return;
        }

        {
        register void *callArg0 ASM_REG("$4") = arg0;   /* MATCH pin: retail delay-slot fill depends on it */

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x100) {
            func_800AA258(callArg0, arg1, arg2, arg3);
            return;
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(callArg0, arg1, arg2, arg3);
            func_801737DC(arg0, arg1, arg2, arg3);
            return;
        }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 == 0) {
            return;
        }

        if ((s16)func_800A2C34(arg3) != 0) {
            void *owner;

            owner = D_800814A8;
            if ((s16)func_8009A180(arg3, (u8 *)((S_8017357C_4 *)owner)->unk_58 + 0x20) != 0) {
                return;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
            return;
        }
    }

    effect = D_80174520;
    (*(void * *)((u8 *)arg2 + 0x2C)) = effect;
    index = (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(arg2, effect[index & 7], 0);
    ((S_8017357C_0 *)arg0)->unk_8C = D_80170E5C;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= ~0x200;
}
