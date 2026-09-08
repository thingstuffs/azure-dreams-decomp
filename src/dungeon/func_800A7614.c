#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004491C();
extern M2C_UNK func_80044A50();
extern M2C_UNK D_80083460;
extern M2C_UNK D_800C6AEC;




/* Resets object state, runs object setup, and updates property and status flags. */
void func_800ACD74(void *object_state, void *unused_context, Rec_D_80082E80 *properties, Rec_D_800E3D7C *status) {
    void *object;
    u16 *global_state;

    ((Rec_func_800A9E70_arg0 *)object_state)->unk_9A.as_s8 = 0x13;
    ((Rec_func_800A9E70_arg0 *)object_state)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)object_state)->unk_8C = 0;
    properties->unk_14.at00_u16.v = (u16)(properties->unk_14.at00_u16.v & 0xF7FF);
    ((Rec_func_800A9E70_arg0 *)object_state)->unk_96.as_s16 = 0;
    object = object_state - 0x20;
    global_state = (u16 *)&D_80083460;
    global_state[5] = (u16)(global_state[5] + 1);
    func_80044A50(object);
    func_8004491C(object, &D_800C6AEC);
    properties->unk_0C.at03_s8.v = 0;
    properties->unk_0C.at02_s8.v = 0;
    properties->unk_0C.at01_s8.v = 0;
    properties->unk_0C.at00_s8.v = 0;
    properties->unk_10.as_s16 = 0x20;
    properties->unk_12.at00_u16.v = (u16)(properties->unk_12.at00_u16.v - 0x80);
    status->unk_1C.as_s32 = (s32)(status->unk_1C.as_s32 | 0x10000000);
}
