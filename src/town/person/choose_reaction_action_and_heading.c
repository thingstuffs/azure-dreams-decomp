#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_800C9B44_arg0.h"
#include "engine/window.h"
#include "town/person.h"

extern TownIndexedHandler reaction_action_handlers[];

/* Choose a random action and an in-bounds heading, then dispatch the action. */
void choose_reaction_action_and_heading(TownObjectRecord *actor, ObjectPosition *motion, SpriteFrameState *context) {
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
    motion->velocity_y = 0;
    motion->velocity_x = 0;
    while (1) {
        attempts -= 1;
        action = 0;
        if (attempts <= 0)
            break;
        {
            action = scale_random_by_limit(3) & 0xFFFF;
            if (action == 1) {
                direction = scale_random_by_limit(4) & 0xFFFF;
                if (direction == 0) {
                    s32 center_x = actor->origin_x;
                    x_radius = actor->roam_range_x;
                    if (motion->x.w.i < (center_x + x_radius)) {
                        actor->heading = 0x400;
                        break;
                    }
                    continue;
                }
                if (direction == action) {
                    s32 target_y = actor->origin_y;
                    y_radius = actor->roam_range_y;
                    if (motion->y.w.i < (target_y + y_radius)) {
                        actor->heading = 0;
                        break;
                    }
                    continue;
                }
                if (direction == 2) {
                    s32 center_x = actor->origin_x;
                    s32 lower_x_radius = actor->roam_range_x;
                    current_x = motion->x.w.i;
                    if ((center_x - lower_x_radius) < current_x) {
                        actor->heading = 0xC00;
                        break;
                    }
                    continue;
                }
                center_y = actor->origin_y;
                lower_y_radius = actor->roam_range_y;
                current_y = motion->y.w.i;
                if ((center_y - lower_y_radius) < current_y) {
                    actor->heading = 0x800;
                    break;
                }
                continue;
            }
            break;
        }
    }
    {
        TownIndexedHandler *handlers = reaction_action_handlers;

        handlers[action](actor, motion, context);
    }
}
