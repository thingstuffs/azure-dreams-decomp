#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_80171F9C_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171F9C_0;   /* held_arg2 in func_80171F9C */





extern s32 func_80047784();
extern s32 func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern s32 func_800C7930();
extern u8 D_80175E50[];
extern u8 D_80175E70[];
extern u8 D_80175EA8[];

/* Select and start an actor action based on the target delta. */
s32 func_80171F9C(Rec_func_800A9E70_arg0 *action_state, s32 action_param, void *visual_data, void *actor) {
    s32 target_delta;
    s16 action_mode;
    u16 pending_amount;
    register u16 action_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u8 status;
    u16 stored_amount;

    status = *(volatile u8 *)((u8 *)actor + 0x71);
    {
        S_80171F9C_0 *visual = visual_data;
        register s32 target ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        register u16 *global_flags ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *flags_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        *(volatile u8 *)((u8 *)actor + 0x71) = status & 0x7F;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        flags_page = (u8 *)0x80080000;
        ASM_KEEP(flags_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        global_flags = (u16 *)(flags_page + 0x3460);
        action_mode = 0;
        if (global_flags[1] & 0x2000) {
            return -1;
        }

        target = func_800A04F0(actor, visual->unk_24, visual->unk_25, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16);
        if ((func_800A2CB8(actor, target) << 16) == 0) {
            return 0;
        }
        if (global_flags[1] & 0x2000) {
            return -1;
        }
        if (!(((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) && (global_flags[1] & 8)) {
            return -1;
        }

        target_delta = 0 - func_800A0134(target, actor);
        if ((u32)((target_delta - 0x20) & 0xFFFF) < 0x21U) {
            action_mode = 1;
            goto check_ready;
        }
        if ((u32)((target_delta + 0x10) & 0xFFFF) < 0x31U) {
            action_mode = 2;
            goto check_ready;
        }
        if ((u32)((target_delta + 0x40) & 0xFFFF) >= 0x31U) {
            return action_mode;
        }
        action_mode = 3;

check_ready:
        if ((func_800A2B5C(actor) << 16) != 0) {
            return -1;
        }
        func_800C7930((u8 *)actor - 0x20, action_param, 8, 0x300);
        if ((func_800A2B5C(actor) << 16) != 0) {
            return -1;
        }

        {
            s32 selected_mode = action_mode;
            action_state->unk_9B.as_s8 = 0;
            if (selected_mode == 1) {
                action_state->unk_8C = 0;
                visual->unk_2C = D_80175E50;
                action_flags = action_state->unk_98;
                action_state->unk_9A.as_s8 = 0x11;
                goto set_flag;
            }
            if (selected_mode == 2) {
                action_state->unk_8C = 0;
                visual->unk_2C = D_80175E70;
                action_flags = action_state->unk_98;
                action_state->unk_9A.as_s8 = 0x17;
set_flag:
                action_state->unk_98 = action_flags | 8;
                ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7C;
                ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 0;
                goto common;
            }

            action_state->unk_8C = 0;
            visual->unk_2C = D_80175EA8;
            action_state->unk_9A.as_s8 = 0x18;
            ((Rec_D_800E3D7C *)actor)->unk_84.as_s8 = 0x7C;
            ((Rec_D_800E3D7C *)actor)->unk_85.as_s8 = 0;
            ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= 0xFFFBFFFF;

common:
            {
                u8 *phase_page;
                phase_page = (u8 *)0x80080000;
                func_80047784(visual, visual->unk_2C[((*(s16 *)(phase_page + 0x3228) + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7], 0);
            }
            ((Rec_D_800E3D7C *)actor)->unk_6D.as_u8--;
            func_8009C93C(actor, visual, ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16, 1, 0);
            stored_amount = action_state->unk_90.at02_u16.v;
            pending_amount = action_state->unk_A0.at02_u16.v;
            action_state->unk_A0.at02_u16.v = 0;
            action_state->unk_9E.as_s16 = 0;
            action_state->unk_90.at02_u16.v = stored_amount - pending_amount;
            return action_mode;
        }
    }
}
