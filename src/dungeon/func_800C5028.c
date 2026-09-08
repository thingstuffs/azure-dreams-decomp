#include "common.h"

typedef struct S_800CA788_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800CA788_0;   /* global_base in func_800CA788 */

typedef struct S_800CA788_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_800CA788_1;   /* actor in func_800CA788 */

typedef struct S_800CA788_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CA788_2;   /* held_arg2 in func_800CA788 */

typedef struct S_800CA788_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
} S_800CA788_3;   /* object in func_800CA788 */



extern s32 D_80083460;

extern s32 func_8009B4B0(void *, u8, u8);
extern void func_8009C93C(void *, void *, s32, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A2B5C(void *);
extern void func_800C7930(void *, void *, s32, s32);

/* Attempt an action toward the target and decrement the actor counter on success. */
s32 func_800CA788(void *object_ptr, void *action_context, void *target_ptr, void *actor_ptr)
{
    s32 target_direction;
    s32 clear_action_flag;
    u8 *object;
    u8 *actor;
    register void *context ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register void *target ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *global_state;
    u16 global_flags;

    object = object_ptr;
    actor = actor_ptr;
    actor[0x71] &= 0x7F;
    context = action_context;
    ASM_KEEP(context);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    global_state = (u8 *)&D_80083460;
    if (((S_800CA788_0 *)global_state)->unk_02 & 0x2000) {
        goto return_negative;
    }
    target = target_ptr;

    ((S_800CA788_1 *)actor)->unk_14 |= 0x2000;
    ((S_800CA788_1 *)actor)->unk_1C |= 0x2000;
    target_direction = func_8009B4B0(actor, ((S_800CA788_2 *)target)->unk_24, ((S_800CA788_2 *)target)->unk_25);
    clear_action_flag = ~0x2000;
    ((S_800CA788_1 *)actor)->unk_14 &= clear_action_flag;
    ((S_800CA788_1 *)actor)->unk_1C &= clear_action_flag;
    global_flags = ((S_800CA788_0 *)global_state)->unk_02;
    if (!(global_flags & 0x2000)) {
        goto check_flag_8;
    }
return_negative:
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    return -1;
check_flag_8:
    if (global_flags & 8) {
        return -1;
    }

    if ((u32)((-func_800A0134(target_direction, actor) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    func_800C7930(actor - 0x20, context, 8, 0x300);
    if ((func_800A2B5C(actor) << 16) != 0) {
        return -1;
    }

    {
        void *action_actor;
        register void *action_target ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        s32 actor_param;
        s32 action_mode;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        s32 actor_flags_14;
        s32 actor_flags_1c;

        action_actor = actor;
        ASM_KEEP(action_actor);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        action_target = target;
        object[0x9B] = 0;
        ((S_800CA788_3 *)object)->unk_8C = 0;
        object[0x9A] = 0x11;
        actor_param = ((S_800CA788_1 *)actor)->unk_2A;
        actor[0x84] = 0x80;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        actor_flags_14 = ((S_800CA788_1 *)actor)->unk_14;
        actor_flags_1c = ((S_800CA788_1 *)actor)->unk_1C;
   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        action_mode = 0;
        actor[0x85] = 0;
        actor_flags_14 |= 0x2000;
        actor_flags_1c |= 0x2000;
        ((S_800CA788_1 *)actor)->unk_14 = actor_flags_14;
        ((S_800CA788_1 *)actor)->unk_1C = actor_flags_1c;
        func_8009C93C(action_actor, action_target, actor_param, action_mode, 0);
    }
    ((S_800CA788_1 *)actor)->unk_14 &= clear_action_flag;
    ((S_800CA788_1 *)actor)->unk_1C &= clear_action_flag;
    actor[0x6D]--;
    return 1;
}
