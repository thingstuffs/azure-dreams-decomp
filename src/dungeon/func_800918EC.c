#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"

M2C_UNK func_80095DD0(); /* extern */
M2C_UNK func_800A2B04();              /* extern */
extern M2C_UNK D_80083460;
extern M2C_UNK D_80096384;


typedef struct S_8009704C_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    s16 unk_04;
} S_8009704C_0;   /* state in func_8009704C */




void func_8009704C(Rec_func_8008ACDC_arg0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, M2C_UNK arg3) {
    s16 temp_v0;
    u16 temp_v1;
    register s8 *state = (s8 *)&D_80083460;
    M2C_UNK saved_arg3;
    saved_arg3 = arg3;

    if (((S_8009704C_0 *)state)->unk_02 & 0x80) {
        ((S_8009704C_0 *)state)->unk_04 = 0;
    }
    if (((S_8009704C_0 *)state)->unk_04 != 0) {
        arg1->unk_0C.as_s32 = (s32) ((s32) ((((arg2->unk_24 << 6) + 0x20) << 0x10) - arg1->unk_00.at00_s32.v) / (s16) ((S_8009704C_0 *)state)->unk_04);
        arg1->unk_10.at00_s32.v = (s32) ((s32) ((((arg2->unk_25 << 6) + 0x20) << 0x10) - arg1->unk_04.at00_s32.v) / (s16) ((S_8009704C_0 *)state)->unk_04);
    }
    do { temp_v1 = arg0->unk_A2; } while (0);
    if (!(temp_v1 & 0x10)) {
        arg0->unk_A2 = (u16) (temp_v1 | 1);
    }
    temp_v0 = (u16) ((S_8009704C_0 *)state)->unk_04 - 1;
    ((S_8009704C_0 *)state)->unk_04 = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        ((S_8009704C_0 *)state)->unk_04 = 0;
        arg1->unk_14.as_s32 = 0;
        arg1->unk_10.at00_s32.v = 0;
        arg1->unk_0C.as_s32 = 0;
        func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);
        arg2->unk_14.at00_u16.v = (u16) (arg2->unk_14.at00_u16.v | 0x4000);
        if (arg0->unk_100 >= 0) {
            func_80095DD0(arg0, arg1, arg2, saved_arg3);
            return;
        }
        arg0->unk_8C.as_pm = &D_80096384;
    }
}

/* MECHANISM: An early guarded keep makes &D_80083460 an opaque held base, preserving alias reloads.
   An explicit $s3 ABI local schedules arg3 into the first branch slot; its keep lives on the cold path.
   2.7.2-cdk-G0 supplies retail's v0-to-a1 split address materialization. */
