#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800D55A0;
extern M2C_UNK D_800D55A8;
extern M2C_UNK D_800D55D0;
extern M2C_UNK D_800D55D4;

typedef struct S_800C5D38_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800C5D38_0;   /* arg2 in func_800C5D38 */

typedef struct S_800C5D38_1 {
    u8 pad_00[0x58];
    M2C_UNK * unk_58;
    M2C_UNK * unk_5C;
    u8 pad_60[0x1C];
    M2C_UNK * unk_7C;
    M2C_UNK * unk_80;
} S_800C5D38_1;   /* arg0 in func_800C5D38 */


void func_800C4174(void *object, s32 update_context, s32 setup_context);
/* Install the actor's response tables and process input when either masked flag is set. */
void func_800C5D38(S_800C5D38_1 *actor, s32 context, S_800C5D38_0 *input) {
    if (input->unk_14 & 0x6000) {
        actor->unk_58 = &D_800D55D0;
        actor->unk_5C = &D_800D55D4;
        actor->unk_7C = &D_800D55A0;
        actor->unk_80 = &D_800D55A8;
        func_800C4174(actor, context, input);
    }
}
