#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800352FC(Rec_func_80094268_arg0 *, M2C_UNK, M2C_UNK, M2C_UNK);
extern M2C_UNK func_800C337C();
extern u8 D_80082660[9];
extern M2C_UNK D_800CFCB4[5];
extern volatile M2C_UNK D_800D5084[20];



typedef struct S_800C3988_1_pre {
    M2C_UNK (*unk_00)(void *, M2C_UNK, M2C_UNK);
    u8 pad_04[0x54];
} S_800C3988_1_pre;   /* the 0x58 bytes before (((s8) temp_v1 * 4) + ((Rec_func_80094268_arg0 *)arg0)->unk_5C) in func_800C3988, addressed as (((s8) temp_v1 * 4) + ((Rec_func_80094268_arg0 *)arg0)->unk_5C)[-1] */

void func_800C3988(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3) {
    s32 temp_v0;
    u8 temp_v1;
    u8 *entry;
    register M2C_UNK (*handler)(void *, M2C_UNK, M2C_UNK) ASM_REG("$2"); /* MATCH: merge the dispatch target in v0. */
    Rec_func_80094268_arg0 *call_arg0;
    M2C_UNK call_arg1;

    if (func_800352FC(arg0, arg1, arg2, arg3) == 0) {
        s32 *state;

        func_800C337C(arg0, arg1, arg2);
        state = D_800CFCB4;
        if (arg0 == state[4]) {
            state[4] = 0;
            return;
        }
    } else {
        temp_v0 = arg0->unk_60 * 8;
        entry = &D_80082660[temp_v0];
        temp_v1 = *entry;
        if ((u32) (temp_v1 - 2) < 0x14U) {
            call_arg0 = arg0;
            temp_v0 = D_800D5084[(s8) temp_v1];
            handler = (M2C_UNK (*)(void *, M2C_UNK, M2C_UNK)) temp_v0;
            call_arg1 = arg1;
            goto dispatch;
        }
        if ((s8) temp_v1 >= 0x16) {
            register s32 base ASM_REG("$2"); /* MATCH: load the record base into v0 before indexing. */
            call_arg1 = arg1;
            call_arg0 = arg0;
            base = call_arg0->unk_5C;
            handler = ((S_800C3988_1_pre *)((((s8) temp_v1 * 4) + base)))[-1].unk_00;
        dispatch:
            handler(call_arg0, call_arg1, arg2);
            return;
        }
        if ((s8) temp_v1 < 0) {
            *entry = 0U;
            func_800C337C(arg0, arg1, arg2);
        }
    }
}
