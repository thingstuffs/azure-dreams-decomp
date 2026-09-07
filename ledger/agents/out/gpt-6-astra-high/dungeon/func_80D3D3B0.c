#include "common.h"
#include "m2c_compat.h"

void func_8009C93C(void *, void *, s16, s32, s32);
s32 func_800A0134(s32, void *);
s32 func_800A04F0(void *, u8, u8, s16);
s32 func_800A2B5C(void *);
s32 func_800A2CB8(void *, s32);
void func_800C7930(void *, s32, s32, s32);
void func_80175F44(void *, s32, void *, s32, s32);
extern s32 D_80083460;

typedef struct S_80172BB0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172BB0_0;   /* arg3 in func_80172BB0 */

typedef struct S_80172BB0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172BB0_1;   /* arg2 in func_80172BB0 */

typedef struct S_80172BB0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x19];
    u8 unk_B5;
} S_80172BB0_2;   /* arg0 in func_80172BB0 */

/* Turn toward the target and start an action once aligned. */
s32 func_80172BB0(S_80172BB0_2 *action_state, M2C_UNK action_context, S_80172BB0_1 *target, void *actor) {
    s32 target_angle;
    s32 result;
    register u16 *global_flags ASM_REG("$20");   /* MATCH pin: retail register colouring depends on it */

    {
        register s32 history ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

        history = ((S_80172BB0_0 *)actor)->unk_71;
        history &= 0x7F;
        ((S_80172BB0_0 *)actor)->unk_71 = history;
    }
    {
        register u8 *page ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

        page = (u8 *)0x80080000;
        ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
        global_flags = (u16 *)(page + 0x3460);
    }
    result = 0;
    if (global_flags[1] & 0x2000) {
        return -1;
    }

    target_angle = func_800A04F0(actor, target->unk_24,
        target->unk_25, ((S_80172BB0_0 *)actor)->unk_2A);
    if ((func_800A2CB8(actor, target_angle) << 0x10) == 0) {
        return result;
    }

    if (global_flags[1] & 0x2000) {
        return -1;
    }
    if (!(((S_80172BB0_0 *)actor)->unk_46 & 0x8000) && (global_flags[1] & 8)) {
        return -1;
    }
    if ((u32)(((0 - func_800A0134(target_angle, actor)) + 0x40) & 0xFFFF) <
            0x81U) {
        result = 1;
        if ((func_800A2B5C(actor) << 0x10) != 0) {
            return -1;
        }
        func_800C7930((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((func_800A2B5C(actor) << 0x10) != 0) {
            return -1;
        }

        action_state->unk_9B = 0;
        if (action_state->unk_B5 == 0) {
            action_state->unk_9A = 0x11;
            action_state->unk_8C = 0;
            ((S_80172BB0_0 *)actor)->unk_84 = 0x7C;
            ((S_80172BB0_0 *)actor)->unk_85 = 0;
            action_state->unk_98 =
                (u16)(action_state->unk_98 | 8);
            func_8009C93C(actor, target, ((S_80172BB0_0 *)actor)->unk_2A, 1, 0);
            ((S_80172BB0_0 *)actor)->unk_6D--;
        } else {
            register s32 one ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */

            one = 1;
            func_80175F44(action_state, action_context, target, one, one);
        }
    }
    ASM_KEEP(result);   /* MATCH pin: retail register colouring depends on it */
    return result;
}
