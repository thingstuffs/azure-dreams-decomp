#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800A7E7C_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A7E7C_0_pre;   /* the 0x10 bytes before arg0 in func_800A7E7C, addressed as arg0[-1] */


typedef struct S_800A7E7C_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
} S_800A7E7C_1;   /* arg2 in func_800A7E7C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
extern M2C_UNK D_80045340;
extern M2C_UNK D_8006E240;
extern M2C_UNK D_800A7EC0;

/* Initialize the object state from its byte value and set the context resource and callback. */
void func_800A7E7C(void *object, M2C_UNK unused, S_800A7E7C_1 *context) {
    ((S_800A7E7C_0_pre *)object)[-1].unk_00 = &D_800A7EC0;
    ((Rec_func_80094268_arg0 *)object)->unk_60 = (s32) ((Rec_func_80094268_arg0 *)object)->unk_96.as_u8;
    context->unk_08 = &D_8006E240;
    func_80033CD8(object, &D_80045340);
}
