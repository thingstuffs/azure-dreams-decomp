#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082E80.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_8009BFD8();
extern M2C_UNK D_80045340;
extern M2C_UNK D_8009B148;
extern M2C_UNK D_8009B2BC;


typedef struct S_8009B218_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_8009B218_0_pre;   /* the 0x10 bytes before arg0 in func_8009B218, addressed as arg0[-1] */



void func_8009B218(void *arg0, M2C_UNK arg1, Rec_D_80082E80 *arg2, s32 arg3) {
    ((S_8009B218_0_pre *)arg0)[-1].unk_00 = &D_8009B148;
    func_80033CD8(arg0, &D_80045340);
    ((Rec_func_80094268_arg0 *)arg0)->unk_8C = 0;
    ((Rec_func_80094268_arg0 *)arg0)->unk_8E = 0;
    arg2->unk_00 = 0;
    arg2->unk_04.as_s8 = 0;
    arg2->unk_05.as_s8 = 0;
    if (arg3 != 0) {
        ((Rec_func_80094268_arg0 *)arg0)->unk_58 = arg3;
        func_8009BFD8(arg0, arg0, arg1, arg2);
        return;
    }
    ((Rec_func_80094268_arg0 *)arg0)->unk_50.as_pm = &D_8009B2BC;
}
