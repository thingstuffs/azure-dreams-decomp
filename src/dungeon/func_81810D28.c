#include "common.h"
#include "records/Rec_func_80025D28_arg0.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))


void func_80025D28(Rec_func_80025D28_arg0 *arg0) {
    volatile s32 sp0;
    s32 value;
    u8 flags;

    sp0 = 0xB8C8;
    arg0->unk_01 = 0x28;
    value = sp0;
    flags = arg0->unk_00;
    arg0->unk_02 = 2;
    arg0->unk_03 = 2;
    arg0->unk_0A = 0xC;
    arg0->unk_0B = 0xC;
    arg0->unk_04 = value;
    arg0->unk_00 = (u8)(flags | 0x80);
}
