#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u16 D_80083462;


typedef struct S_80174824_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80174824_1;   /* arg0 in func_80174824 */

void func_80174824(S_80174824_1 *arg0, M2C_UNK arg1, M2C_UNK arg2, void *arg3) {
    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            arg0->unk_8C = 0;
            arg0->unk_9A = 0x17;
            arg0->unk_9B = 0;
            func_800A4ACC(arg3);
            ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8) (((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
            arg0->unk_96 = 0;
        }
    }
}
