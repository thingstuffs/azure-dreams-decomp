#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

s32 func_800352FC(s32 arg0, s32 *arg1, s32 arg2, s32 arg3); /* extern */
M2C_UNK SD_Call();                     /* extern */
s32 func_800C2AB4();                          /* extern */
extern u8 D_80083780[];

/* Advance the actor state on nearby activation or release, playing the activation sound. */
void func_800BF8DC(Rec_D_80082D58 *actor, s32 *position, s32 check_param, s32 check_mode) {
    s16 state;
    s32 check_value;
    s32 next_state;

    check_value = (s32)actor;
    state = actor->unk_68;
    if (state != 1) {
        if (state < 2) {
            if (state != 0) {
                ASM_SCHED_BARRIER(); /* MATCH: preserve the retail guard layout. */
                goto end;
            }
            goto check_distance;
        }
        if (state != 2) {
            if (state != 3) {
                goto end;
            }
            goto check_release;
        }
check_distance:
        {
            s32 threshold;
            s32 distance;

            distance = *(s32 *)D_80083780;
            check_value = *position;
            distance -= check_value;
            threshold = 0x3FFFFF;
            ASM_KEEP(threshold);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            if (distance < 0) {
                distance = -distance;
            }
            threshold = threshold < distance;
            if ((threshold == 0) && (func_800352FC(check_value, position, check_param, check_mode) != 0) && (func_800C2AB4(actor) != 0)) {
                SD_Call(0x50B);
                distance = (u16)actor->unk_68;
                threshold = 0x20;
                actor->unk_6C.as_s16 = threshold;
                distance++;
                next_state = distance;
            } else {
                goto end;
            }
        }
    } else {
check_release:
        if ((func_800352FC(check_value, position, check_param, check_mode) == 0) || (func_800C2AB4(actor) == 0)) {
            next_state = ((u16) actor->unk_68 + 1) & 3;
        } else {
            goto end;
        }
    }
    actor->unk_68 = next_state;
end:
    return;
}
