#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"







#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80048A44();
M2C_UNK func_8009A66C();
M2C_UNK func_8009F644();
s32 func_800A44E0();
s32 func_800A7234();
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80081485;
extern s16 D_80083228;
extern u16 D_80083460[];
extern u8 D_800DD0D0[];

void func_8008F6EC(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 sp18;
    s16 sp1A;
    s16 sp1C;
    s32 temp_v1;
    register s32 var_s1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    var_s1 = 0;
    if (D_80081485 == 0x13) {
        var_s1 = (func_8009A66C(((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16, arg2, arg3, 0x20) << 0x10) > 0;
    } else if ((func_800A44E0(((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v, ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v, ((Rec_D_800E3D7C *)arg3)->unk_88.as_s16, ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16) << 0x10) == 0) {
        temp_v1 = ((u16) ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 >> 8) & 0xE;
        if ((func_800A7234((s16) (((Rec_D_80082E80 *)arg2)->unk_24 + *(u16 *)(D_8006CCD8 + temp_v1)), (s16) (((Rec_D_80082E80 *)arg2)->unk_25 + *(u16 *)(D_8006CCE8 + temp_v1)), ((Rec_D_800E3D7C *)arg3)->unk_88.as_s16, &sp18, &sp1A, &sp1C) << 0x10) != 0) {
            do { var_s1 = 1; } while (0);
        }
    }
    if (var_s1 != 0) {
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9A.as_s8 = 0x1F;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_9B.as_s8 = 0;
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8C.as_s32 = 0;
        (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD0D0;
        func_80048A44(arg2, D_800DD0D0[(((s32) (D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100)) >> 9) & 7], 0, 1);
        D_80083460[5] = D_80083460[5] + 1;
        func_8009F644(arg3, 0x28, 0, 0);
    }
}
