#include "common.h"
#include "shared/town_state.h"
#include "town/scene/animation.h"



typedef struct Motion {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct Actor {
    void *handler;
    u8 mode;
    u8 variant;
    u8 pad06[2];
    s32 value;
    u8 pad0C[6];
    u16 height;
    u16 flags;
} Actor;

typedef struct Entity {
    u8 pad00[0x1e];
    s16 field1E;
    u16 flags20;
} Entity;

typedef struct State {
    s16 state;
    s16 timer;
    Entity *entity;
    u8 work[0x15];
    u8 field1D;
    u8 pad1E[0x36];
    s16 kind;
    s16 threshold;
} State;

extern TownRewardValues D_80526448;
extern s32 score_object_images[];
extern u8 score_bounce_update_address[];
extern u8 score_bounce_motion_data[];
extern u8 town_motion_state[];
extern u8 score_sprite_handler_address[];
extern s32 score_sprite_initial_value[3];
extern s32 scene_value_total;
extern s32 scene_object_flags;

extern s32 func_80071494(void);
extern void func_8003EA54(Actor *);
extern s32 func_80240810(void *, Motion *, void *, void *);
extern void func_8023FB18(void *);

/* Bounces a pickup, applies its reward on a successful position test, and handles blinking and removal. */
void animate_bouncing_score_object(State *st, Motion *mot, Actor *actor)
{
    Actor *act = actor;
    Entity *entity;
    s16 dispatch_a1;
    TownRewardValues choices;
    s32 value;
    u32 result_v0;

    entity = st->entity;
    choices = D_80526448;

    dispatch_a1 = 1;

    if (entity->flags20 & 8) {
        st->state = 6;
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
    act->handler = score_sprite_handler_address;
    act->value = score_sprite_initial_value[0];
    act->mode = 0;
    act->variant = func_80071494() & 3;
    act->flags &= 0xff7f;

    value = st->kind;
    if (value == 0) {
        act->height += 5;
        st->field1D = 0;
        st->state = 2;
    } else if (value == 1) {
        act->height -= 5;
        st->field1D = 0;
        st->state = 2;
    } else {
        st->field1D = 0;
        st->state = 2;
    }

case 2:
    func_8003EA54(act);
    mot->x += mot->dx;
    mot->y += mot->dy;
    mot->z += mot->dz;
    mot->dz += 0x30000;
    st->timer--;
    if (st->timer > 0) {
        return;
    }

    mot->z = -0x400000;
    mot->dz = ((func_80071494() & 0xff) << 11) - 0x180000;
    st->timer = (func_80071494() & 0xf) + 30;
    st->state = 3;
    return;

    case 3:
    {
        s32 floor;
        s32 z;
        func_8003EA54(act);
        mot->z += mot->dz;
        mot->dz += 0x30000;
        z = mot->z;
        floor = -0x400000;
        if (z > floor) {
            mot->z = floor;
            mot->dz = (-mot->dz) >> 1;
        }
        if (func_80240810(score_bounce_update_address, mot, score_bounce_motion_data, town_motion_state)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = ((s32 *)&choices)[product];
            product = choice * 125;
            scene_value_total = product * 8 + scene_value_total;
            (*(s16 *)((u8 *)st + 0)) = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            return;
        }
        st->timer = 180;
        st->state = 4;
        act->value = score_object_images[st->kind];
        act->height = 0;
        act->mode = 0;
        act->variant = 0;
        mot->z = floor;
        return;
    }

    case 4:
        if (func_80240810(score_bounce_update_address, mot, score_bounce_motion_data, town_motion_state)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = ((s32 *)&choices)[product];
            product = choice * 125;
            scene_value_total = product * 8 + scene_value_total;
            (*(s16 *)((u8 *)st + 0)) = 6;
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
        if (func_80240810(score_bounce_update_address, mot, score_bounce_motion_data, town_motion_state)) {
            s32 product;
            s32 choice;
            product = st->kind;
            choice = ((s32 *)&choices)[product];
            product = choice * 125;
            scene_value_total = product * 8 + scene_value_total;
            (*(s16 *)((u8 *)st + 0)) = 6;
        }
        st->timer--;
        if (st->timer > 0) {
            return;
        }
        st->state = 6;
        return;
    }

    case 6:
        func_8023FB18(&st->work[0]);
        *(u16 *)((u8 *)st - 2) |= 0x8000;
        scene_object_flags |= 0x8000;
        return;

    default:
        return;
    }
}
