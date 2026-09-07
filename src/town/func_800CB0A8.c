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

void func_800C8808(Rec_func_80094268_arg0 *arg0, S_800C8808_1 *arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D627C);
    arg0->unk_54 = &D_800C8788;
    arg1->unk_14 = 0xFFF60000;
}
