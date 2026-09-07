#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"



typedef s32 M2C_UNK;


typedef struct S_800AA888_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800AA888_4;   /* ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in func_800AA888 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8009A3D0();




void func_800AA888(Rec_func_800A9E70_arg0 *arg0, void *arg1, Rec_func_800AA258_arg2 *arg2, Rec_D_800E3D7C *arg3) {
    u8 call_arg0;
    u8 call_arg1;
    M2C_UNK var_v1;

    arg0->unk_9A.as_s8 = 0xB;
    arg0->unk_9B.as_s8 = 0;
    arg0->unk_8C = 0;
    call_arg0 = arg2->unk_24;
    call_arg1 = arg2->unk_25;
    var_v1 = 0x3000;
    if (arg3->unk_1C.as_s32 & 0x2000) {
        var_v1 = 0x300;
    }
    func_8009A3D0(call_arg0, call_arg1, var_v1);
    arg0->unk_98 = (u16)(arg0->unk_98 | 8);
    arg3->unk_1C.as_s32 = (s32)(arg3->unk_1C.as_s32 & 0xFFFBFFFF);
    arg0->unk_96.as_s16 = 0;
    arg3->unk_6A.as_u16 = (u16)((S_800AA888_4 *)(((Rec_D_800E3D7C *)arg3)->unk_60.as_pv))->unk_2A;
}

/* MECHANISM: Named u8 call-argument locals force both byte loads before the flag branch,
   freeing v1 to carry the selected third argument into the jal delay slot.
   Natural arg0/arg3 lifetimes yield the exact 0x20 frame and s0/s1 save order. */
