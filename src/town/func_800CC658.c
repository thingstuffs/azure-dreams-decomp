#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800C9B44_arg0.h"

s32 func_800374F4();
extern void (*D_800D65D8[])(void *, void *, M2C_UNK);

/* Choose a random action and an in-bounds heading, then dispatch the action. */
void func_800C9DB8(Rec_func_800C9B44_arg0 *actor, EntityRec *motion, M2C_UNK context) {
    s32 x_radius;
    s32 y_radius;
    s32 current_x;
    s32 center_y;
    s32 lower_y_radius;
    s32 current_y;
    s32 direction;
    s32 action;
    s32 attempts;

    attempts = 0x10;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    for (;;) {
retry:
        attempts -= 1;
        action = 0;
        if (attempts <= 0) break;
        {
            action = func_800374F4(3) & 0xFFFF;
            if (action == 1) {
                direction = func_800374F4(4) & 0xFFFF;
                if (direction == 0) {
                    s32 center_x = actor->unk_84;
                    x_radius = actor->unk_8C;
                    if (motion->x.w.i < (center_x + x_radius)) {
                        actor->unk_72 = 0x400;
                        break;
                    }
                    goto retry;
                }
                if (direction == action) {
                    s32 center_y = actor->unk_86;
                    y_radius = actor->unk_8E;
                    if (motion->y.w.i < (center_y + y_radius)) {
                        actor->unk_72 = 0;
                        break;
                    }
                    continue;
                }
                if (direction == 2) {
                    s32 center_x = actor->unk_84;
                    s32 lower_x_radius = actor->unk_8C;
                    current_x = motion->x.w.i;
                    if ((center_x - lower_x_radius) < current_x) {
                        actor->unk_72 = 0xC00;
                        break;
                    }
                    continue;
                }
                center_y = actor->unk_86;
                lower_y_radius = actor->unk_8E;
                current_y = motion->y.w.i;
                if ((center_y - lower_y_radius) < current_y) {
                    actor->unk_72 = 0x800;
                    break;
                }
                continue;
            }
            break;
        }
    }
    {
        void *dispatch_actor = actor;
        void (**handlers)(void *, void *, M2C_UNK) = D_800D65D8;

        handlers[action](dispatch_actor, motion, context);
    }
}
