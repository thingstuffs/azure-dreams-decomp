#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern s8 D_80082688;
extern M2C_UNK D_800CE780;
extern M2C_UNK D_800D72D4;


typedef struct S_800CECC8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800CECC8_1;   /* arg1 in func_800CECC8 */

/* Initialize the object, clear the global flag, and set its handler and initial offset. */
void func_800CECC8(Rec_func_80094268_arg0 *object, S_800CECC8_1 *motion, M2C_UNK init_data) {
    func_800C2E84(object, init_data, &D_800D72D4);
    D_80082688 = 0;
    object->unk_54 = &D_800CE780;
    motion->unk_14 = 0xFFF60000;
}
