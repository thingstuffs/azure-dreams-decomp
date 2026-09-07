#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern u16 D_80083462;

typedef struct S_80172548_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172548_0;   /* arg3 in func_80172548 */

typedef struct S_80172548_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80172548_1;   /* arg0 in func_80172548 */

/* Clear the entity flag and advance its action state when the checks pass. */
void func_80172548(S_80172548_1 *action_state, M2C_UNK effect_context, M2C_UNK update_context, void *entity) {
    ((S_80172548_0 *)entity)->unk_71 = (u8) (((S_80172548_0 *)entity)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(entity) << 0x10) == 0)) {
        func_800C7930(entity - 0x20, effect_context, 8, 0x300);
        if ((func_800A2B5C(entity) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A = 0x11;
            action_state->unk_9B = 0;
            action_state->unk_96 = 0;
            ((S_80172548_0 *)entity)->unk_6D = (u8) (((S_80172548_0 *)entity)->unk_6D - 1);
            func_8009C93C(entity, update_context, ((S_80172548_0 *)entity)->unk_2A, 1, 0);
            ((S_80172548_0 *)entity)->unk_84 = 0x7C;
            ((S_80172548_0 *)entity)->unk_85 = 0;
        }
    }
}
