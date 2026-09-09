#include "common.h"
#include "m2c_compat.h"

/* extern */
extern s8 D_80082688;

typedef struct S_800CEAC8_0 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800CEAC8_0;   /* arg0 in func_800CEAC8 */


M2C_UNK func_800CEB00(S_800CEAC8_0 *, s32, s32);
/* Call func_800CEB00, clear D_80082688, and set the object state to 4. */
void func_800CEAC8(S_800CEAC8_0 *object, s32 context, s32 update_data) {
    func_800CEB00(object, context, update_data);
    D_80082688 = 0;
    object->unk_90 = 4;
}
