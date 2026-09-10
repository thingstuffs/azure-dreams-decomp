#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_800E3D7C.h"




M2C_UNK func_80048A44(); /* extern */
M2C_UNK func_80094E34();                            /* extern */
extern s16 D_80083228;
extern u8 D_800DD0E8;

void func_80090200(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    /* MATCH: Keep the shared data pointer in a0 after the first call. */
    register u8 *data ASM_REG("$4");
    s32 mask;

    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_s8 = 0xD;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_s8 = 0;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_s32 = 0;
    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_96.as_s16 = 0;
    do {
        func_80094E34(arg0);
    } while (0);
    mask = ~0x20;
     /* MATCH: Emit the mask before loading the data pointer. */
    data = &D_800DD0E8;
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & mask);
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = data;
    func_80048A44(arg2, *((((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + data), 0, 1);
}
