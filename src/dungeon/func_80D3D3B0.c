#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_800A9E70_arg0.h"

void func_8009C93C(void *, void *, s16, s32, s32);
s32 func_800A0134(s32, void *);
s32 func_800A04F0(void *, u8, u8, s16);
s32 func_800A2B5C(void *);
s32 func_800A2CB8(void *, s32);
void func_800C7930(void *, s32, s32, s32);
void func_80175F44(void *, s32, void *, s32, s32);
extern s32 D_80083460;




/* Turn toward the target and start an action once aligned. */
s32 func_80172BB0(Rec_func_800A9E70_arg0 *action_state, M2C_UNK action_context, Rec_D_80082E80 *target, void *actor) {
    s32 target_angle;
    s32 result;
    register u16 *global_flags ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    {
        register s32 history ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        history = ((Rec_D_800E3D7C *)actor)->unk_71.as_u8;
        history &= 0x7F;
        ((Rec_D_800E3D7C *)actor)->unk_71.as_u8 = history;
    }
    {
        register u8 *page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

        page = (u8 *)0x80080000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        global_flags = (u16 *)(page + 0x3460);
    }
    result = 0;
    if (global_flags[1] & 0x2000) {
        return -1;
    }

    target_angle = func_800A04F0(actor, target->unk_24,
        target->unk_25, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16);
    if ((func_800A2CB8(actor, target_angle) << 0x10) == 0) {
        return result;
    }

    if (global_flags[1] & 0x2000) {
        return -1;
    }
    if (!(((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) && (global_flags[1] & 8)) {
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

        action_state->unk_9B.as_s8 = 0;
        if (action_state->unk_B5 == 0) {
            action_state->unk_9A.as_s8 = 0x11;
            action_state->unk_8C = 0;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7C;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 0;
            action_state->unk_98 =
                (u16)(action_state->unk_98 | 8);
            func_8009C93C(actor, target, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
            ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
        } else {
            register s32 one ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

            one = 1;
            func_80175F44(action_state, action_context, target, one, one);
        }
    }
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    return result;
}
