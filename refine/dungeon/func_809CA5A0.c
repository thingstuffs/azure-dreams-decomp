#include "common.h"

typedef struct S_80171DA0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    u8 unk_84;
    u8 unk_85;
} S_80171DA0_0;   /* arg3 in func_80171DA0 */

typedef struct S_80171DA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171DA0_1;   /* held_arg2 in func_80171DA0 */

typedef struct S_80171DA0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
} S_80171DA0_2;   /* arg0 in func_80171DA0 */



extern void func_80047784();
extern void func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern void func_800C7930();
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80173C7C;

/* Checks whether the actor can transition and starts its directional effect. */
s32 func_80171DA0(S_80171DA0_2 *action_state, s32 motion_param, void *sprite_arg, void *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    s32 saved_motion_param;
    register void *sprite ASM_REG("$19");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u32 status_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 *status ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    volatile s32 frame_pad[2];

    actor_flags = ((S_80171DA0_0 *)actor)->unk_71;
    saved_motion_param = motion_param;
    actor_flags &= 0x7F;
    ((S_80171DA0_0 *)actor)->unk_71 = actor_flags;
    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    status_page = 0x80080000U;
    ASM_KEEP(status_page);   /* MATCH pin: load-bearing for the whole function shape */
    status = (u16 *)(status_page + 0x3460);
    ASM_KEEP(status);   /* MATCH pin: load-bearing for the whole function shape */
    if (status[1] & 0x2000) {
        goto abort_transition;
    }
    sprite = sprite_arg;

    target_angle = func_800A04F0(actor, ((S_80171DA0_1 *)sprite)->unk_24,
                           ((S_80171DA0_1 *)sprite)->unk_25, ((S_80171DA0_0 *)actor)->unk_2A);
    if ((func_800A2CB8(actor, target_angle) << 16) == 0) {
        return 0;
    }

    status_flags = status[1];
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(((S_80171DA0_0 *)actor)->unk_46 & 0x8000) && (status_flags & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(target_angle, actor) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)actor - 0x20, saved_motion_param, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) == 0) {
        goto transition_ok;
    }

abort_transition:
    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    return -1;

transition_ok:
    {
        s32 actor_angle;
        register u32 effect_lookup ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        u8 *effect_table;

        action_state->unk_9A = 0x11;
        ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
        effect_lookup = 0x7C;
        effect_table = &D_80173C7C;
        action_state->unk_9B = 0;
        action_state->unk_8C = 0;
        ((S_80171DA0_0 *)actor)->unk_84 = effect_lookup;
        ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
        effect_lookup = 0x80080000U;
        ASM_KEEP(effect_lookup);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_80171DA0_0 *)actor)->unk_85 = 0;
        ((S_80171DA0_1 *)sprite)->unk_2C = effect_table;
        effect_lookup = (s32)*(s16 *)(effect_lookup + 0x3228);
        actor_angle = ((S_80171DA0_0 *)actor)->unk_2A;
        effect_lookup += actor_angle;
        effect_lookup += 0x100;
        effect_lookup = ((s32)effect_lookup >> 9) & 7;
        effect_lookup += (u32)effect_table;
        func_80047784(sprite,
                      *(u8 *)effect_lookup,
                      0);
        ((S_80171DA0_0 *)actor)->unk_6D--;
        func_8009C93C(actor, sprite, ((S_80171DA0_0 *)actor)->unk_2A, 1, 0);
        return 1;
    }
}

/* MECHANISM: An addressless 8-byte frame object plus held s2 status base gives the 0x40 frame;
   split s5/s3 input live ranges and a zero-byte abort fence reproduce the prologue and local CFG.
   A held a1 effect base and successive v0 scratch roles close the success addressing chain. */
