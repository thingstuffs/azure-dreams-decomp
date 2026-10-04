#include "common.h"

#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

static __inline__ s16 distance_exceeds(s32 limit, s32 distance) {
    return limit < __builtin_abs(distance);
}

s32 func_800352FC(s32 arg0, s32 *arg1, s32 arg2, s32 arg3); /* extern */
M2C_UNK SD_Call();                     /* extern */
s32 func_800C2AB4();                          /* extern */

/* Advance the actor state on nearby activation or release, playing the activation sound. */
void func_800BF8DC(Rec_D_80082D58 *actor, s32 *position, s32 check_param, s32 check_mode) {
    s16 state;
    s32 check_value;
    s32 next_state;

    check_value = (s32)actor;
    state = actor->unk_68;

    switch (state) {
    case 0:
    case 2:
        {
            s32 threshold;
            s32 distance;

            distance = *(s32 *)((u8 *)(&D_80083780));
            check_value = *position;
            distance -= check_value;
            threshold = 0x3FFFFF;

            threshold = distance_exceeds(threshold, distance);
            if ((threshold == 0) && (func_800352FC(check_value, position, check_param, check_mode) != 0)
                && (func_800C2AB4(actor) != 0)) {
                SD_Call(0x50B);
                distance = (u16)actor->unk_68;
                threshold = 0x20;
                actor->unk_6C.as_s16 = threshold;
                distance++;
                next_state = distance;
            } else {
                return;
            }
        }
        break;
    case 1:
    case 3:
        if ((func_800352FC(check_value, position, check_param, check_mode) == 0) || (func_800C2AB4(actor) == 0)) {
            next_state = ((u16) actor->unk_68 + 1) & 3;
        } else {
            return;
        }
        break;
    default:
        return;
    }

    actor->unk_68 = next_state;
    return;
}
