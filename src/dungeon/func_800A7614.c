#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004491C();
extern M2C_UNK func_80044A50();
extern M2C_UNK D_80083460;
extern M2C_UNK D_800C6AEC;




void func_800ACD74(void *arg0, void *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    void *temp_s0;
    u16 *state;

    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_s8 = 0x13;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
    arg2->unk_14.at00_u16.v = (u16)(arg2->unk_14.at00_u16.v & 0xF7FF);
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_96.as_s16 = 0;
    temp_s0 = arg0 - 0x20;
    state = (u16 *)&D_80083460;
    state[5] = (u16)(state[5] + 1);
    func_80044A50(temp_s0);
    func_8004491C(temp_s0, &D_800C6AEC);
    arg2->unk_0C.at03_s8.v = 0;
    arg2->unk_0C.at02_s8.v = 0;
    arg2->unk_0C.at01_s8.v = 0;
    arg2->unk_0C.at00_s8.v = 0;
    arg2->unk_10.as_s16 = 0x20;
    arg2->unk_12.at00_u16.v = (u16)(arg2->unk_12.at00_u16.v - 0x80);
    arg3->unk_1C.as_s32 = (s32)(arg3->unk_1C.as_s32 | 0x10000000);
}
