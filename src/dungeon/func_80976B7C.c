#include "common.h"

typedef struct S_8017237C_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
} S_8017237C_0;   /* p3 in func_8017237C */

typedef struct S_8017237C_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017237C_1;   /* p2 in func_8017237C */

typedef struct S_8017237C_2 {
    u8 pad_00[0x8C];
    volatile s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    volatile u8 unk_9A;
    u8 unk_9B;
} S_8017237C_2;   /* p0 in func_8017237C */

typedef struct S_8017237C_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    volatile u8 unk_6D;
    u8 pad_6E[0x16];
    volatile u8 unk_84;
    volatile u8 unk_85;
} S_8017237C_3;   /* call0 in func_8017237C */



extern void func_8009C93C(void *, void *, s32, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, u8, u8, s16);
extern s16 func_800A2B5C(void *);
extern s16 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, void *, s32, s32);
extern s32 D_80083460;
extern u16 D_80083462;

/* Validates an actor action, applies its effect, and updates the action state and remaining count. */
s32 func_8017237C(void *action_data, void *effect_data, void *target_data, void *actor_data)
{
    S_8017237C_2 *action = action_data;
    void *effect = effect_data;
    void *actor = actor_data;
    u16 *global_flags;
    u8 *global_page;
    register s32 action_ready ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 target_code;
    u8 actor_flags;

    actor_flags = ((S_8017237C_0 *)actor)->unk_71;
    {
        S_8017237C_1 *target = target_data;

        actor_flags = (u8)(actor_flags & 0x7F);
        ((S_8017237C_0 *)actor)->unk_71 = actor_flags;
        global_page = (u8 *)0x80080000;
        ASM_KEEP(global_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        global_flags = (u16 *)(global_page + 0x3460);
        action_ready = 0;

        if (global_flags[1] & 0x2000) {
            return -1;
        }

        target_code = func_800A04F0(
            actor, target->unk_24, target->unk_25,
            ((S_8017237C_0 *)actor)->unk_2A);
        {
            register void *check_actor ASM_REG("$4") = actor;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            register s32 result ASM_REG("$17") = target_code;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

            if (func_800A2CB8(check_actor, result) == 0) {
                return action_ready;
            }
            if (global_flags[1] & 0x2000) {
                return -1;
            }
            if ((((S_8017237C_0 *)actor)->unk_46 & 0x8000) == 0) {
                if (global_flags[1] & 8) {
                    return -1;
                }
            }

            if ((u16)(0 - func_800A0134(result, actor) + 0x40) >= 0x81U) {
                return action_ready;
            }

            action_ready = 1;
            if ((((S_8017237C_0 *)actor)->unk_46 & 0x8000) == 0) {
                if (D_80083462 & 8) {
                    return -1;
                }
            }
            if (func_800A2B5C(actor) != 0) {
                return -1;
            }

            func_800C7930((u8 *)actor - 0x20, effect, 8, 0x300);

            if (func_800A2B5C(actor) != 0) {
                return -1;
            }
            result = action_ready;

            action->unk_9B = 0;
            action->unk_96 = 0;
            if (result != 0) {
                S_8017237C_3 *active_actor = actor;
                void *action_target = target;
                s32 facing;
                u8 remaining_count;

                action->unk_8C = 0;
                action->unk_9A = 0x11;
                facing = active_actor->unk_2A;
                active_actor->unk_84 = 0x7C;
                remaining_count = active_actor->unk_6D;
                active_actor->unk_85 = 0;
                active_actor->unk_6D = (u8)(remaining_count - 1);
                func_8009C93C(active_actor, action_target, facing, 1, 0);
            }

            ASM_KEEP(action);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP(effect);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP(target);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            return result;
        }
    }
}

/* MECHANISM: Pinned argument roles produce the 0x38 frame and s4/s6/s5/s0 holds.
   RMW seams plus a pinned 0x80080000 page emit v0->s3; a nested raw-return
   live range orders a0 before s1. Volatile tail stores retain the call ABI order. */
