#include "common.h"
#include "town/scene/collection.h"
#include "shared/entity.h"
#include "shared/minigame_body.h"
#include "shared/vector.h"
#include "town/scene/effect.h"
#include "sdk/libc.h"
#include "town/scene/animation.h"
#include "town/data.h"
#include "town/scene/score_sprite_data.h"
#include "town/devkit/old_minigame_imports.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
struct SpawnSeed;

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8052F2C8_3 {
    u8 pad_00[0x8];
    void * unk_08;
    union { u8 u8; void * p32; } unk_0C;   /* accessed as both */
    void * unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    void * unk_20;
    s32 unk_24;
} S_8052F2C8_3;   /* work in animate_rising_effect_object */

extern void create_object_position_configures_color(s32 color, s32 x, s32 y, s32 z);
extern u32 D_80095AAC;
extern u8 D_8028E17C[];
extern u8 D_8028E188[];
extern void D_8052F8C4();

/* Per-frame step for the town scene object: dispatch its mode and update the sprite it draws. */
void animate_rising_effect_object(RisingEffectObject *obj, ObjectPosition *state_in, SpriteFrameState *incoming) {
    register SpriteFrameState *sprite;
    register RisingEffectObject *obj_held = obj;
    register ObjectPosition *state_held = state_in;
    ObjectNodeHeader *child;
    RisingScoreChild *payload;
    s16 state;
    s16 mode;
    s16 timer;
    s32 timer0;
    s32 timer_end;
    s32 step;
    s32 sum;
    s32 sum3;
    s32 count;
    s32 count4;
    s32 x;
    s32 rnd;
    s32 x4;
    s32 color4;
    s32 work_value;
    s16 scale;
    u16 kind;
    register RisingScorePanel *root;
    TownScoreCounterView *root_obj;
    ObjectPosition *position;
    TownScoreCounterView *data0;
    TownScoreCounterView *data1;
    TownScoreCounterView *spawn_data;
    SpriteFrameState *child_sprite;
    u32 *money;

    /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: town/func_808146C8). */
    do {
        root = obj_held->root;
    } while (0);
    root->flags |= 1;
    root_obj = root->score;
    sprite = incoming;

    if (root->progress == 9) {
        mode = obj_held->mode.s;
        if (mode == 1 && state_held->x.v <= 0x04DFFFFF) {
            state = root->column;
            switch (state) {
            case 0:
                sprite->color.c.r = 0xFF;
                count = 3;
                do {
                    spawn_offset_seed_effect((struct SpawnSeed *)state_held);
                    count--;
                } while (count >= 0);
                break;
            case 1:
                sprite->flags |= 0xC;
                count = 2;
                do {
                    spawn_scattered_seed_effect((struct SpawnSeed *)state_held);
                    count--;
                } while (count >= 0);
                break;
            case 2:
                timer = sprite->scale_y + 0x200;
                sprite->scale_y = timer;
                sprite->scale_x = timer;
                break;
            }
        }
    }

    switch (obj_held->mode.s) {
    case 0:
        if (obj_held->timer == 0x10) {
            root->flags |= 4;
        } else {
            root->flags &= 0xFFFB;
        }
        timer0 = (u16)obj_held->timer - 1;
        obj_held->timer = timer0;
        if ((timer0 << 16) > 0) {
            break;
        }
        func_80058F88(0x518);
        data0 = root->score;
        data0->completed++;
        obj_held->mode.s = 1;
        sprite->flags &= 0xFF7F;
        break;

    case 1:
        step = obj_held->velocity_x + obj_held->accel_x;
        obj_held->velocity_x = step;
        sum = state_held->x.v + obj_held->velocity_x;
        state_held->x.v = sum;
        if (sum <= 0x0427FFFF) {
            obj_held->timer = 6;
            money = &D_80095AAC;
            if (*(u8 *)money >= 9U) {
                *money += 0xFFF7F7F8;
            }
            sprite->flags |= 0x80;
            func_80058F88(0x506);
            obj_held->mode.s = 2;
            break;
        }
        {
            s32 current_y;
            s32 delta;
            s32 target_y;
            s32 *target_y_addr;

            target_y_addr = &town_motion_state.y.v;
            target_y = *target_y_addr;
            current_y = state_held->y.v;
            delta = target_y - current_y;
            delta = abs(delta);
            if (delta > 0x200000) {
                break;
            }
        }
        if (sum > 0x043FFFFF) {
            break;
        }
        if (obj_held->flags & 4) {
            break;
        }

        kind = root_obj->counter - 3;
        if (kind < 3U) {
            func_80058F88(0x513);
            obj_held->velocity_x = 0x180000;
            obj_held->mode.s = 3;
            obj_held->flags |= 4;
            data1 = root->score;
            root->progress++;
            data1->score += 2;
            if (root->progress == 10) {
                data1 = root->score;
                data1->score += 10;
            }
            break;
        }
        if (kind >= 7U) {
            break;
        }

        func_80058F88(0x510);
        obj_held->flags |= 4;
        spawn_data = root->score;
        count = 1;
        spawn_data->score++;
        scale = 0x1000;
        do {
            child = func_800373DC(0x136);
            if (child != NULL) {
                child->update_callback = D_8052F8C4;
                func_8003BC18(child, score_sprite_draw_callback_address);
                position = child->position;
                child_sprite = child->sprite;
                position->x.v = state_held->x.v;
                position->y.v = state_held->y.v;
                position->z.v = state_held->z.v;
                work_value = obj_held->velocity_x;
                payload = NODE_BODY(child);
                payload->panel = root;
                payload->step_x = work_value;
                child_sprite->scale_y = scale;
                child_sprite->scale_x = scale;
                if (count != 0) {
                    child_sprite->source = D_8028E188;
                    position->velocity_y = 0x80000;
                } else {
                    child_sprite->source = D_8028E17C;
                    position->velocity_y = 0xFFF80000;
                }
                child_sprite->unk_04 = 0;
                child_sprite->frame_ticks = 0;
                child_sprite->color.word = 0x808080;
            }
            count--;
        } while (count >= 0);
        obj_held->mode.u = 0xFF;
        break;

    case 2:
        count = 7;
        do {
            count--;
            x = (((func_80071494() & 0xFF) - 0x80) << 14) + state_held->x.v;
            rnd = func_80071494();
            create_object_position_configures_color(0, x, state_held->y.v + 0x80000,
                          ((rnd % 80) << 16) + 0xFFB00000);
        } while (count >= 0);
        timer_end = (u16)obj_held->timer - 1;
        obj_held->timer = timer_end;
        if ((timer_end << 16) <= 0) {
            obj_held->mode.u = 0xFF;
        }
        break;

    case 3:
        root->flags |= 2;
        sum3 = state_held->x.v + obj_held->velocity_x;
        state_held->x.v = sum3;
        if (sum3 > 0x055FFFFF) {
            obj_held->timer = 5;
            func_80058F88(0x50C);
            obj_held->mode.s = 4;
        }
        break;

    case 4:
        root->flags |= 2;
        for (count4 = 7; count4 >= 0; count4--) {
            x4 = (((func_80071494() & 0xFF) - 0x80) << 14) + 0x05600000;
            color4 = ((func_80071494() & 0x3F) << 16) | 0xFFC00000;
            create_object_position_configures_color(0, x4, state_held->y.v + 0x80000, color4);
        }

        timer_end = (u16)obj_held->timer - 1;
        obj_held->timer = timer_end;
        if ((timer_end << 16) <= 0) {
            obj_held->mode.u = 0xFF;
        }
        break;

    case 0xFF:
        root->flags &= 0xFFFE;
        {
            u16 *flags = &NODE_HEADER(obj_held)->flags;
            *flags |= 0x8000;
        }
        scene_object_flags |= 0x8000;
        break;

    default:
        break;
    }
}
