#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u16 D_80083462;


typedef struct S_80175BE0_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x18];
    u16 unk_B4;
} S_80175BE0_1;   /* arg0 in func_80175BE0 */


void func_80175BE0(S_80175BE0_1 *arg0, Rec_D_800E3D7C *arg1, M2C_UNK arg2, void *arg3) {
    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            arg0->unk_8C = 0;
            arg0->unk_9A = 0x18;
            arg0->unk_9B = 0;
            arg0->unk_96 = 0;
            arg1->unk_14.as_s32 = 0;
            arg1->unk_10.at00_s32.v = 0;
            arg1->unk_0C.as_s32 = 0;
            arg0->unk_92 = (u16) (arg0->unk_92 + ((Rec_D_800E3D7C *)arg3)->unk_88.as_u16);
            arg0->unk_B4 = (u16) ((Rec_D_800E3D7C *)arg3)->unk_88.as_u16;
            ((Rec_D_800E3D7C *)arg3)->unk_88.as_u16 = 0U;
            arg0->unk_98 = (u16) (arg0->unk_98 | 8);
            func_800A4ACC(arg3);
            ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
        }
    }
}
