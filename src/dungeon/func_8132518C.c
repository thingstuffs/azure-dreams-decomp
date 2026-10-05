#include "common.h"
#include "shared/dungeon_status.h"
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
extern s16 func_800ADDA0(void *context, void *position, void *entity, s16 near_range, s16 far_range, s32 state_out_addr);
extern void func_8016BF74(void *, s32, s32, void *);

/* Dispatches the actor's action state and updates its activity flags. */
s32 func_8016C98C(Rec_func_800A9E70_arg0 *actor, s32 x, s32 y, s32 force_action)
{
    void *base = actor;
    s16 action_state;
    s32 result;

    if (((S_8016C98C_0 *)base)->unk_AE != 0) {
        action_state = func_800ADDA0(x, y, base, 3, 6,
                              (u8 *)base + 0x9C);
        if ((s16)action_state < 0) {
            return 0;
        }
        if ((force_action << 16) != 0) {
            func_8016BF74(base, x, y, base);
            return 0;
        }
    } else {
        action_state = 0;
    }

    switch (action_state) {
    case 0:
        result = 0xE;
        actor->unk_9A.as_s8 = result;
        func_800A9A0C(base);
        return 0;

    case 2:
        func_8016BF74(actor, x, y, base);
        return 0;

    case 1:
        ((S_8016C98C_0 *)base)->unk_71 &= 0x7F;
        if ((func_800A2BDC(base) << 16) != 0) {
            result = 0;
            ((S_8016C98C_0 *)base)->unk_46 &= 0x7FFF;
            return result;
        }
                        /* fall through */

    default:
        ((S_8016C98C_0 *)base)->unk_71 &= 0x7F;
        result = 1;
        if (!(dungeonStatus.flags & 8)) {
            return result;
        }
        result = 0;
        ((S_8016C98C_0 *)base)->unk_46 &= 0x7FFF;
        return result;
    }
}
