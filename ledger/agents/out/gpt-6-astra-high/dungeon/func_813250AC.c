#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_80083462[5];
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */

typedef struct S_8016C8AC_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_8016C8AC_0;   /* arg3 in func_8016C8AC */

typedef struct S_8016C8AC_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8016C8AC_1;   /* arg0 in func_8016C8AC */

/* Clear the actor flag and update its action state when both checks pass. */
void func_8016C8AC(S_8016C8AC_1 *action_state, M2C_UNK action_context, M2C_UNK effect_context, void *actor) {
    ((S_8016C8AC_0 *)actor)->unk_71 = (u8) (((S_8016C8AC_0 *)actor)->unk_71 & 0x7F);
    if (!(*D_80083462 & 0x2000) && ((func_800A2B5C(actor) << 0x10) == 0)) {
        func_800C7930(actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A = 0x11;
            action_state->unk_9B = 0;
            ((S_8016C8AC_0 *)actor)->unk_6D = (u8) (((S_8016C8AC_0 *)actor)->unk_6D - 1);
            func_8009C93C(actor, effect_context, ((S_8016C8AC_0 *)actor)->unk_2A, 1, 0);
            ((S_8016C8AC_0 *)actor)->unk_84 = 0x7C;
            ((S_8016C8AC_0 *)actor)->unk_85 = 6;
        }
    }
}
