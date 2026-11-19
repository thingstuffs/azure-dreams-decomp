#include "common.h"
#include "town/scene/collection.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_state.h"
#include "town/scene/animation.h"
#include "town/data.h"
#include "town/scene/score_sprite_data.h"
#include "town/devkit/old_minigame_imports.h"

typedef struct BouncingScoreEntity {
    u8 pad00[0x1e];
    s16 field1E;
    u16 flags20;
} BouncingScoreEntity;

extern TownRewardValues D_80526448;
extern u8 score_bounce_motion_data[];
#include "town/scene/value_total_data.h"


/* Bounces a pickup, applies its reward on a successful position test, and handles blinking and removal. */
void animate_bouncing_score_object(BouncingScoreBody *st, ObjectPosition *mot, SpriteFrameState *act)
{
    BouncingScoreEntity *entity;
    s16 dispatch_a1;
    TownRewardValues choices;
    s32 value;
    u16 *node_flags;
    s16 *state_slot;

    entity = st->entity;
    choices = D_80526448;

    dispatch_a1 = 1;

    if (entity->flags20 & 8) {
        state_slot = &st->state;
        *state_slot = 6;
    }

    value = st->state;
    switch (value) {

    case 0:
    {
        s32 call_a0;
        u32 step_result;
        s32 threshold;

        switch (st->kind) {
        default:
            break;
        case 1:
            dispatch_a1 = 10;
            break;
        case 2:
            dispatch_a1 = 100;
            break;
        }

        call_a0 = entity->field1E;
        call_a0 /= dispatch_a1;
        {
            s32 quotient;
            quotient = call_a0 / 10;
            step_result = quotient * 10;
            threshold = st->threshold;
            quotient = call_a0 - step_result;
            {
                u16 flags;

                if (threshold < quotient) {
                    flags = act->flags & 0xff7f;
                } else {
                    flags = act->flags | 0x80;
                }
                act->flags = flags;
            }
        }
        st->field1D = 0;
        return;
    }

    case 1:
    act->unk_00 = score_sprite_handler_address;
    act->source = score_sprite_initial_value[0];
    act->unk_04 = 0;
    act->frame_ticks = func_80071494() & 3;
    act->flags &= 0xff7f;

    value = st->kind;
    if (value == 0) {
        act->clut += 5;
        st->field1D = 0;
        st->state = 2;
    } else if (value == 1) {
        act->clut -= 5;
        st->field1D = 0;
        st->state = 2;
    } else {
        st->field1D = 0;
        st->state = 2;
    }

case 2:
    func_8003EA54(act);
    mot->x.v += mot->velocity_x;
    mot->y.v += mot->velocity_y;
    mot->z.v += mot->velocity_z;
    mot->velocity_z += 0x30000;
    st->timer--;
    if (st->timer > 0) {
        return;
    }

    mot->z.v = -0x400000;
    mot->velocity_z = ((func_80071494() & 0xff) << 11) - 0x180000;
    st->timer = (func_80071494() & 0xf) + 30;
    st->state = 3;
    return;

    case 3:
    {
        s32 floor;
        s32 z;
        func_8003EA54(act);
        mot->z.v += mot->velocity_z;
        mot->velocity_z += 0x30000;
        z = mot->z.v;
        floor = -0x400000;
        if (z > floor) {
            mot->z.v = floor;
            mot->velocity_z = (-mot->velocity_z) >> 1;
        }
        if (func_80240810(score_bounce_update_address, mot, score_bounce_motion_data, &town_motion_state)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = choices.values[product];
            product = choice * 125;
            scene_value_total = product * 8 + scene_value_total;
            state_slot = &st->state;
            *state_slot = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            return;
        }
        st->timer = 180;
        st->state = 4;
        act->source = score_object_images[st->kind];
        act->clut = 0;
        act->unk_04 = 0;
        act->frame_ticks = 0;
        mot->z.v = floor;
        return;
    }

    case 4:
        if (func_80240810(score_bounce_update_address, mot, score_bounce_motion_data, &town_motion_state)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = choices.values[product];
            product = choice * 125;
            scene_value_total = product * 8 + scene_value_total;
            state_slot = &st->state;
            *state_slot = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            return;
        }
        st->timer = 31;
        st->state = 5;
        return;

    case 5:
    {
        u32 step_result;
        if ((st->timer >> 2) & 1) {
            step_result = act->flags | 0x80;
        } else {
            step_result = act->flags & 0xff7f;
        }
        act->flags = step_result;
        if (func_80240810(score_bounce_update_address, mot, score_bounce_motion_data, &town_motion_state)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = choices.values[product];
            product = choice * 125;
            scene_value_total = product * 8 + scene_value_total;
            state_slot = &st->state;
            *state_slot = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            return;
        }
        state_slot = &st->state;
        *state_slot = 6;
        return;
    }

    case 6:
        func_8023FB18(&st->work[0]);
        node_flags = &NODE_HEADER(st)->flags;
        *node_flags |= 0x8000;
        scene_object_flags |= 0x8000;
        return;

    default:
        return;
    }
}
