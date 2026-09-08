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



/* Initialize object and state, using the supplied value or default data. */
void func_8009B218(void *object, M2C_UNK context, Rec_D_80082E80 *state, s32 init_value) {
    ((S_8009B218_0_pre *)object)[-1].unk_00 = &D_8009B148;
    func_80033CD8(object, &D_80045340);
    ((Rec_func_80094268_arg0 *)object)->unk_8C = 0;
    ((Rec_func_80094268_arg0 *)object)->unk_8E = 0;
    state->unk_00 = 0;
    state->unk_04.as_s8 = 0;
    state->unk_05.as_s8 = 0;
    if (init_value != 0) {
        ((Rec_func_80094268_arg0 *)object)->unk_58 = init_value;
        func_8009BFD8(object, object, context, state);
        return;
    }
    ((Rec_func_80094268_arg0 *)object)->unk_50.as_pm = &D_8009B2BC;
}
