#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_8016C98C_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x3C];
    u16 unk_AE;
} S_8016C98C_0;   /* base in func_8016C98C */


extern s32 func_800A2BDC(void *);
extern void func_800A9A0C(void *);
extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8016BF74(void *, s32, s32, void *);
extern u16 D_80083462;

/* Dispatches the actor's action state and updates its activity flags. */
s32 func_8016C98C(Rec_func_800A9E70_arg0 *actor, s32 x, s32 y, s32 force_action)
{
    void *base = actor;
    s16 action_state;
    s32 result;
    void *action_actor;

    s32 action_x;
    s32 action_y;
    void *action_base;

    if (((S_8016C98C_0 *)base)->unk_AE != 0) {
        action_state = func_800ADDA0(x, y, base, 3, 6,
                              (u8 *)base + 0x9C);
        if ((s16)action_state < 0) {
            s32 tail_result = 0;
            return tail_result;
        }
        if ((force_action << 16) != 0) {
            action_actor = base;
            action_x = x;
            action_y = y;
            action_base = base;
            goto call_action;
        }
        goto dispatch_state;
    }
    action_state = 0;

dispatch_state:
    if (action_state == 1) {
        goto check_action;
    }
    if (action_state < 2) {
        result = 0xE;
        if (action_state == 0) {
            goto reset_action;
        }
        goto finish_action;
    }
    action_actor = actor;
    if (action_state == 2) {
        goto perform_action;
    }
    goto finish_action;

reset_action: {
        s32 tail_result = 0;
        actor->unk_9A.as_s8 = result;
        func_800A9A0C(base);
        tail_result = 0;
        return tail_result;
    }

perform_action: {
        s32 tail_result = 0;
        action_x = x;
        action_y = y;
        action_base = base;
call_action:
        func_8016BF74(action_actor, action_x, action_y, action_base);
        tail_result = 0;
        return tail_result;
    }

check_action:
    ((S_8016C98C_0 *)base)->unk_71 &= 0x7F;
    if ((func_800A2BDC(base) << 16) != 0) {
        goto clear_flags;
    }

finish_action:
    ((S_8016C98C_0 *)base)->unk_71 &= 0x7F;
    result = 1;
    if (!(D_80083462 & 8)) {
        return result;
    }

clear_flags:
    result = 0;
    ((S_8016C98C_0 *)base)->unk_46 &= 0x7FFF;
    return result;
}

