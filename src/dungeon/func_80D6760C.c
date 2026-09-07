#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172E0C_0 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
} S_80172E0C_0;   /* arg0 in func_80172E0C */



M2C_UNK func_80047784();         /* extern */
extern s16 D_80083228;
extern u8 D_800E2360;

void func_80172E0C(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    ((S_80172E0C_0 *)arg0)->unk_9A = 0x10;
    ((S_80172E0C_0 *)arg0)->unk_9B = 0;
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_800E2360;
    func_80047784(arg2, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + &D_800E2360), 0);
    ((S_80172E0C_0 *)arg0)->unk_AA = 0;
}
