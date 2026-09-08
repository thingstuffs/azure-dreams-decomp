#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800C9F34_arg0.h"


void func_800CAA94(Rec_func_800C9F34_arg0 *arg0) {
    arg0->unk_9A.as_s8 = 8;
    arg0->unk_96 = 0x40;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    arg0->unk_1C = (s32) ((arg0->unk_1C | 0x04000000) & ~0x1638);
}
