#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800C2E84();
extern M2C_UNK D_800C8788;
extern M2C_UNK D_800D627C;


typedef struct S_800C8808_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C8808_1;   /* arg1 in func_800C8808 */

/* Initialize the object callback and set its state value to negative ten in fixed point. */
void func_800C8808(Rec_func_80094268_arg0 *object, S_800C8808_1 *state, M2C_UNK init_data) {
    func_800C2E84(object, init_data, &D_800D627C);
    object->unk_54 = &D_800C8788;
    state->unk_14 = 0xFFF60000;
}
