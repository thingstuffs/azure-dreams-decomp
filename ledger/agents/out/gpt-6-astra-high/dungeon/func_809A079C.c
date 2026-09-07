#include "common.h"

typedef struct S_80171F9C_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171F9C_0;   /* held_arg2 in func_80171F9C */

typedef struct S_80171F9C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x16];
    s8 unk_84;
    s8 unk_85;
} S_80171F9C_1;   /* arg3 in func_80171F9C */

typedef struct S_80171F9C_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80171F9C_2;   /* arg0 in func_80171F9C */



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
s32 func_80171F9C(S_80171F9C_2 *action_state, s32 action_param, void *visual_data, void *actor) {
    register s32 saved_action_param ASM_REG("$22") = action_param;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 target_delta;
    s32 action_mode;
    u16 pending_amount;
    register u16 action_flags ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u8 status;
    u16 stored_amount;

    ASM_KEEP(saved_action_param);   /* MATCH pin: retail schedule: same instructions, different order without it */
    status = *(volatile u8 *)((u8 *)actor + 0x71);
    {
        S_80171F9C_0 *visual = visual_data;
        register s32 target ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
        register u16 *global_flags ASM_REG("$21");   /* MATCH pin: load-bearing for the whole function shape */
        register u8 *flags_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

        *(volatile u8 *)((u8 *)actor + 0x71) = status & 0x7F;
        ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
        flags_page = (u8 *)0x80080000;
        ASM_KEEP(flags_page);   /* MATCH pin: load-bearing for the whole function shape */
        global_flags = (u16 *)(flags_page + 0x3460);
        ASM_KEEP(global_flags);   /* MATCH pin: keeps a statement from moving across a call/branch */
        action_mode = 0;
        if (global_flags[1] & 0x2000) {
            return -1;
        }

        target = func_800A04F0(actor, visual->unk_24, visual->unk_25, ((S_80171F9C_1 *)actor)->unk_2A);
        if ((func_800A2CB8(actor, target) << 16) == 0) {
            return 0;
        }
        if (global_flags[1] & 0x2000) {
            return -1;
        }
        if (!(((S_80171F9C_1 *)actor)->unk_46 & 0x8000) && (global_flags[1] & 8)) {
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
        func_800C7930((u8 *)actor - 0x20, saved_action_param, 8, 0x300);
        if ((func_800A2B5C(actor) << 16) != 0) {
            return -1;
        }

        {
            register s32 selected_mode ASM_REG("$3") = action_mode;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            action_state->unk_9B = 0;
            if (selected_mode == 1) {
                action_state->unk_8C = 0;
                visual->unk_2C = D_80175E50;
                action_flags = action_state->unk_98;
                action_state->unk_9A = 0x11;
                goto set_flag;
            }
            if (selected_mode == 2) {
                action_state->unk_8C = 0;
                visual->unk_2C = D_80175E70;
                action_flags = action_state->unk_98;
                action_state->unk_9A = 0x17;
set_flag:
                action_state->unk_98 = action_flags | 8;
                ((S_80171F9C_1 *)actor)->unk_84 = 0x7C;
                ((S_80171F9C_1 *)actor)->unk_85 = 0;
                goto common;
            }

            action_state->unk_8C = 0;
            visual->unk_2C = D_80175EA8;
            action_state->unk_9A = 0x18;
            ((S_80171F9C_1 *)actor)->unk_84 = 0x7C;
            ((S_80171F9C_1 *)actor)->unk_85 = 0;
            ((S_80171F9C_1 *)actor)->unk_1C &= 0xFFFBFFFF;

common:
            {
                u8 *phase_page;
                phase_page = (u8 *)0x80080000;
                func_80047784(visual, visual->unk_2C[((*(s16 *)(phase_page + 0x3228) + ((S_80171F9C_1 *)actor)->unk_2A + 0x100) >> 9) & 7], 0);
            }
            ((S_80171F9C_1 *)actor)->unk_6D--;
            func_8009C93C(actor, visual, ((S_80171F9C_1 *)actor)->unk_2A, 1, 0);
            stored_amount = action_state->unk_92;
            pending_amount = action_state->unk_A2;
            action_state->unk_A2 = 0;
            action_state->unk_9E = 0;
            action_state->unk_92 = stored_amount - pending_amount;
            return action_mode;
        }
    }
}
