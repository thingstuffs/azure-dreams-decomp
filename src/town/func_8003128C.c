/* Relink of matched town/func_800CB0A8; every changed retail word is a paired relocation. */
#define D_800C8788 D_800CE19C
#define D_800D627C D_800D72D4
#include "common.h"
#include "records/Rec_func_80094268_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_800C2E84();
extern M2C_UNK D_800CE19C;
extern M2C_UNK D_800D72D4;


typedef struct S_800C8808_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C8808_1;   /* arg1 in func_800CE9EC */

/* Initialize the object callback and set its state value to negative ten in fixed point. */
void func_800CE9EC(Rec_func_80094268_arg0 *object, S_800C8808_1 *state, M2C_UNK init_data) {
    func_800C2E84(object, init_data, &D_800D72D4);
    object->unk_54 = &D_800CE19C;
    state->unk_14 = 0xFFF60000;
}
