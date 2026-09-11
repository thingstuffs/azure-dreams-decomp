#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800C9B44_arg0.h"

s32 func_800374F4();
extern void (*D_800D65D8[])(void *, void *, M2C_UNK);

/* Choose a random action and an in-bounds heading, then dispatch the action. */
void func_800C9DB8(Rec_func_800C9B44_arg0 *actor, Rec_D_800E3D7C *motion, M2C_UNK context) {
    s32 x_radius;
    s32 y_radius;
    s32 current_x;
    s32 center_y;
    s32 lower_y_radius;
    s32 current_y;
    s32 direction;
    register s32 action ASM_REG("$17");
    register s32 attempts ASM_REG("$18");
    s32 heading;

    attempts = 0x10;
    ASM_KEEP(attempts);
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    do {
        attempts -= 1;
    } while (0);
retry:
    action = 0;
    if (attempts > 0) {
        action = func_800374F4(3) & 0xFFFF;
        if (action == 1) {
            direction = func_800374F4(4) & 0xFFFF;
            if (direction == 0) {
                s32 center_x = actor->unk_84;
                x_radius = actor->unk_8C;
                attempts -= 1;
                if (motion->unk_00.at02_s16.v < (center_x + x_radius)) {
                    attempts += 1;
                    ASM_KEEP(attempts);
                    heading = 0x400;
                    goto store_heading;
                }
                goto retry;
            }
            if (direction == action) {
                s32 center_y = actor->unk_86;
                y_radius = actor->unk_8E;
                attempts -= 1;
                if (motion->unk_04.at02_s16.v < (center_y + y_radius)) {
                    attempts += 1;
                    ASM_KEEP(attempts);
                    actor->unk_72 = 0;
                    goto dispatch;
                }
                goto retry;
            }
            if (direction == 2) {
                s32 center_x = actor->unk_84;
                s32 lower_x_radius = actor->unk_8C;
                current_x = motion->unk_00.at02_s16.v;
                attempts -= 1;
                if ((center_x - lower_x_radius) < current_x) {
                    attempts += 1;
                    ASM_KEEP(attempts);
                    heading = 0xC00;
                    goto store_heading;
                }
                goto retry;
            }
            center_y = actor->unk_86;
            lower_y_radius = actor->unk_8E;
            current_y = motion->unk_04.at02_s16.v;
            attempts -= 1;
            if ((center_y - lower_y_radius) < current_y) {
                attempts += 1;
                ASM_KEEP(attempts);
                heading = 0x800;
store_heading:
                actor->unk_72 = heading;
                goto dispatch;
            }
            goto retry;
        }

        goto dispatch;
    }
dispatch:
    {
        register void *dispatch_actor ASM_REG("$4") = actor;
        void (**handlers)(void *, void *, M2C_UNK) = D_800D65D8;

        ASM_KEEP(handlers);
        handlers[action](dispatch_actor, motion, context);
        ASM_KEEP(action);
    }
}
