#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"

extern s32 Control_CD();
extern s32 func_80049984();
extern s16 func_800B6CEC();
extern M2C_UNK func_800B6D54();
extern M2C_UNK func_800B6D94();
extern s32 func_800B6F40();
extern s32 func_800B6F54();
extern s16 D_80083D78[8];
extern u8 D_800B5B20[16];


typedef struct S_800B6E3C_1 {
    s16 unk_00;
    s16 unk_02;
} S_800B6E3C_1;   /* temp_a0 in func_800B6E3C */

typedef struct S_800B6E3C_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800B6E3C_2;   /* (void *)temp_idx in func_800B6E3C */

s32 func_800B6E3C(void *arg0) {
    s32 temp_v0;
    s32 temp_idx;
    S_800B6E3C_1 *temp_a0;
    register s32 tail_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    ((Rec_func_800B683C_arg0 *)arg0)->unk_0A = func_800B6CEC(((Rec_func_800B683C_arg0 *)arg0)->unk_04);
    temp_v0 = func_80049984(((Rec_func_800B683C_arg0 *)arg0)->unk_04);
    ((Rec_func_800B683C_arg0 *)arg0)->unk_10 = temp_v0;
    if (temp_v0 == 3) {
        ((Rec_func_800B683C_arg0 *)arg0)->unk_10 = 0;
    }
    if (func_800B6F54(arg0) != 0) {
        *((((Rec_func_800B683C_arg0 *)arg0)->unk_08 * 2) + D_80083D78) = -1;
    }
    temp_a0 = (((Rec_func_800B683C_arg0 *)arg0)->unk_08 * 2) + D_80083D78;
    if ((temp_a0->unk_00 != ((Rec_func_800B683C_arg0 *)arg0)->unk_0A) || (temp_a0->unk_02 != ((Rec_func_800B683C_arg0 *)arg0)->unk_10)) {
        temp_a0->unk_00 = -1;
        temp_idx = ((Rec_func_800B683C_arg0 *)arg0)->unk_08;
        temp_idx <<= 2;
        temp_idx += (s32)D_80083D78;
        ((S_800B6E3C_2 *)((void *)temp_idx))->unk_02 = -1;
        func_800B6D94(((Rec_func_800B683C_arg0 *)arg0)->unk_14, &D_80083D78);
        ((Rec_func_800B683C_arg0 *)arg0)->unk_DC = 0;
        func_800B6D54(arg0);
        ((Rec_func_800B683C_arg0 *)arg0)->unk_D0 = Control_CD(6, arg0 + 0xD8, NULL);
        ((Rec_func_800B683C_arg0 *)arg0)->unk_D4 = Control_CD(0xFF, &D_800B5B20, arg0);
        tail_value = 1;
        ASM_TAILSLOT_PIN(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        return func_800B6F40();
    }
    return 0;
}
