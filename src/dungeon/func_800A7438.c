#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern struct {
    s8 pad[0xA];
    u16 field_0xA;
} D_80083460;




void func_800ACB98(Rec_func_800A9E70_arg0 *arg0, void *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    arg0->unk_9A.as_s8 = 0x14;
    arg0->unk_9B.as_s8 = 0;
    arg0->unk_8C = 0;
    arg2->unk_14.at00_u16.v = (u16)(arg2->unk_14.at00_u16.v | 0x800);
    arg0->unk_96.as_s16 = 0;
    D_80083460.field_0xA = D_80083460.field_0xA + 1;
    arg3->unk_1C.as_s32 = (s32)(arg3->unk_1C.as_s32 | 0x10000000);
}
