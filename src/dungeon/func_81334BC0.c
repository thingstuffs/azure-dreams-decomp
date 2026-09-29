#include "common.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_8016BBC0_0 {
    u8 pad_00[0x46];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x3C];
    u8 unk_AE;
} S_8016BBC0_0;   /* base in func_8016BBC0 */

extern s32 func_800A2BDC(void *);
extern void func_800A9A0C(void *);
extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8016B230(void *, s32, s32, void *);

/* Update the actor's action delay, dispatch movement, and clear completed action flags. */
s32 func_8016BBC0(Rec_func_800A9E70_arg0 *entity, s32 action_ctx, s32 position, s32 force_move)
{
    void *actor = entity;
    s16 action_result;
    s32 result;
    u8 delay;

    delay = ((S_8016BBC0_0 *)actor)->unk_AE;
    action_result = 0;
    if (delay == 0) {
        action_result = func_800ADDA0(action_ctx, position, actor, 3, 6,
                                    (u8 *)actor + 0x9C);
        if ((s16)action_result < 0) {
            return 0;
        }
        if ((force_move << 16) != 0) {
            func_8016B230(actor, action_ctx, position, actor);
            return 0;
        }
    } else {
        ((S_8016BBC0_0 *)actor)->unk_AE = delay - 1;
    }

    switch (action_result) {
    case 0:
        result = 0xE;
        entity->unk_9A.as_s8 = result;
        func_800A9A0C(actor);
        return 0;
    case 2:
        func_8016B230(entity, action_ctx, position, actor);
        return 0;
    case 1:
        ((S_8016BBC0_0 *)actor)->unk_71 &= 0x7F;
        if ((func_800A2BDC(actor) << 16) != 0) {
            result = 0;
            ((S_8016BBC0_0 *)actor)->unk_46 &= 0x7FFF;
            return result;
        }
        break;
    }
    ((S_8016BBC0_0 *)actor)->unk_71 &= 0x7F;
    result = 1;
    if (!(dungeonStatus.flags & 8)) {
        return result;
    }
    result = 0;
    ((S_8016BBC0_0 *)actor)->unk_46 &= 0x7FFF;
    return result;
}
