#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

void func_80041E70(void *);             /* extern */
s32 func_80042900();            /* extern */
M2C_UNK func_8008D344(); /* extern */
M2C_UNK func_80098864();           /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_80099844();           /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
extern M2C_UNK D_80082E80;
extern M2C_UNK D_80083460;
extern M2C_UNK D_80083780;
extern u8 D_800DDE84[];
extern M2C_UNK D_800E1580;
extern M2C_UNK D_800E15A2;
extern s32 D_800E3D7C;
extern void *D_800E3DF0[];



typedef struct S_800C22EC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C22EC_1;   /* counter in func_800C22EC */

typedef struct S_800C22EC_2 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x1];
    u8 unk_03;
} S_800C22EC_2;   /* temp_a0 in func_800C22EC */

typedef struct S_800C22EC_3 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    s8 unk_28;
    u8 unk_29;
} S_800C22EC_3;   /* temp_s0 in func_800C22EC */

s32 func_800C22EC(Rec_D_800E3D7C *arg0, s32 arg1, s16 arg2, M2C_UNK arg3) {
    s32 temp_v1;
    s32 mask;
    s32 var_s2;
    S_800C22EC_2 *temp_a0;
    S_800C22EC_3 *temp_s0;

    var_s2 = 0;
    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }
    if (arg0 == D_800E3D7C) {
        arg0->unk_110 = arg1;
        func_8008D344(arg0, &D_80083780, &D_80082E80, arg0);
        return 0;
    }
    if ((u32) arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);
        if (func_800AD6FC(arg0, ((u16 *)D_800DDE84)[arg0->unk_10.at03_u8.v] & 3, 0) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
        /* Duplicate return node #16. Try simplifying control flow for better match */
        func_80098B38(arg1);
        {
            void *counter;

            counter = &D_80083460;
            ((S_800C22EC_1 *)counter)->unk_0A = (u16) (((S_800C22EC_1 *)counter)->unk_0A - 1);
        }
        return 1;
    }
    temp_a0 = *(void **)((u8 *)&D_80082E80 + 0x34);
    if (temp_a0->unk_01 == 0x13) {
        temp_v1 = temp_a0->unk_03 & 0x1F;
        if (temp_v1 < 0x14) {
            temp_s0 = D_800E3DF0[temp_v1];
            if ((func_80042900(temp_s0, 0xE, arg2) << 0x10) != 0) {
                register void *call_a0 ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */

                mask = 0xFBFFFFFF;
                call_a0 = temp_s0;
                temp_s0->unk_28 = (s8) (((u8) temp_s0->unk_29 >> 1) + 1);
                temp_s0->unk_1C = (s32) (temp_s0->unk_1C & mask);
                var_s2 = 1;
                func_80041E70(call_a0);
                func_80099844(temp_s0, &D_800E1580);
            }
        }
    }
    if (var_s2 == 0) {
        func_800997FC(&D_800E15A2);
    }
    func_80098B38(arg1);
    {
        void *counter;

        counter = &D_80083460;
        ((S_800C22EC_1 *)counter)->unk_0A = (u16) (((S_800C22EC_1 *)counter)->unk_0A - 1);
    }
    return 1;
}

/* MECHANISM: The natural arg0/arg1/status lifetimes produce retail's 0x20 frame and s0-s2 saves.
   Exact callee arity plus typed u16/pointer tables recover the call schedule and table strides.
   Scoped a0 pins hold the fixup call argument and D_80083460 tail base without backend fences. */
