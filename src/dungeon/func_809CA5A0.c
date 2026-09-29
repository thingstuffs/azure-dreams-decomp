#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"


typedef struct S_80171DA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171DA0_1;   /* held_arg2 in func_80171DA0 */




extern void func_80047784();
extern void func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern void func_800C7930();
extern u8 D_80173C7C;

/* Checks whether the actor can transition and starts its directional effect. */
s32 func_80171DA0(Rec_func_800A9E70_arg0 *action_state, s32 motion_param, void *sprite_arg, EntityRec *actor)
{
    s32 target_angle;
    u16 status_flags;
    u8 actor_flags;
    s32 saved_motion_param;
    register void *sprite ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    u32 status_page;
    u16 *status;
    volatile s32 frame_pad[2];

    actor_flags = actor->unk_71;
    saved_motion_param = motion_param;
    actor_flags &= 0x7F;
    actor->unk_71 = actor_flags;
    do {
        status_page = 0x80080000U;
    } while (0);
    ASM_KEEP(status_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    status = (u16 *)(status_page + 0x3460);
    if (status[1] & 0x2000) {
        goto abort_transition;
    }
    sprite = sprite_arg;

    target_angle = func_800A04F0(actor, ((S_80171DA0_1 *)sprite)->unk_24,
                           ((S_80171DA0_1 *)sprite)->unk_25, actor->facing);
    if ((func_800A2CB8(actor, target_angle) << 16) == 0) {
        return 0;
    }

    status_flags = status[1];
    if (status_flags & 0x2000) {
        return -1;
    }
    if (!(actor->unk_46 & 0x8000) && (status_flags & 8)) {
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
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    return -1;

transition_ok:
    {
        s32 actor_angle;
        register u32 effect_lookup ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u8 *effect_table;

        action_state->unk_9A.as_u8 = 0x11;
        do {
            effect_lookup = 0x7C;
        } while (0);
        effect_table = &D_80173C7C;
        action_state->unk_9B.as_u8 = 0;
        action_state->unk_8C = 0;
        actor->unk_84 = effect_lookup;
        effect_lookup = 0x80080000U;
        ASM_KEEP(effect_lookup);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        actor->unk_85 = 0;
        ((S_80171DA0_1 *)sprite)->unk_2C = effect_table;
        effect_lookup = (s32)*(s16 *)(effect_lookup + 0x3228);
        actor_angle = actor->facing;
        effect_lookup += actor_angle;
        effect_lookup += 0x100;
        effect_lookup = ((s32)effect_lookup >> 9) & 7;
        effect_lookup += (u32)effect_table;
        func_80047784(sprite,
                      *(u8 *)effect_lookup,
                      0);
        actor->unk_6D--;
        func_8009C93C(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
}

/* MECHANISM: An addressless 8-byte frame object plus held s2 status base gives the 0x40 frame;
   split s5/s3 input live ranges and a zero-byte abort fence reproduce the prologue and local CFG.
   A held a1 effect base and successive v0 scratch roles close the success addressing chain. */
