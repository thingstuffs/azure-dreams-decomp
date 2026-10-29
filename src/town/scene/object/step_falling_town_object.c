#include "common.h"
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_links.h"
#include "town/paired_indicators.h"
#include "town/scene/object.h"

/* Work passed with the node's motion and sprite parts. The callback integrates
 * and bounces the position, then awards the value selected by kind. */
typedef struct FallingTownWork {
    IndicatorOwner *owner;
    union { s16 s; u16 u; } state;
    union { s16 s; u16 u; } timer;
    u8 unk_08[0x15];
    s8 unk_1D;
    u8 pad_1E[0x36];
    s16 kind;
} FallingTownWork;


typedef struct {
    s32 v[3];
} Copy12;

extern void func_8003EA54();
extern s32 func_80071494(void);
extern void func_8023FB18();
extern s32 func_80240810();

extern s32 scene_value_total;
extern s32 scene_object_flags;
extern u8 town_motion_state[16];
extern u8 score_bounce_motion_data[16];
extern Copy12 D_80526760;
extern u8 falling_object_update_address[16];
extern s32 D_805301C0[4];

/* Per-frame step for the falling town object: integrate its motion and bounce it when it reaches the ground. */
void step_falling_town_object(FallingTownWork *obj, ObjectPosition *motion, SpriteFrameState *part) {
    Copy12 values;
    s32 *valuep;
    s32 object_value;
    s16 state;
    s32 timer1;
    s32 timer3;
    s32 timer4;
    s32 call_result;

    values = D_80526760;
    valuep = values.v;

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;

    obj->owner->blink_flags |= 2;
    state = obj->state.s;

    switch (state) {
    case 0:
        func_8003EA54(part);
        motion->velocity_z += 0x40000;
        obj->unk_1D = 0;
        if (motion->z.v < 0) {
            return;
        }
        motion->z.v = 0;
        obj->timer.u = 15;
        motion->velocity_x = ((func_80071494() % 448) - 128) << 12;
        motion->velocity_y = ((func_80071494() % 160) + 64) << 12;
        motion->velocity_z = -0x100000;
        obj->state.u++;
        return;
    case 1:
        func_8003EA54(part);
        motion->velocity_z += 0x40000;
        timer1 = obj->timer.u - 1;
        obj->timer.u = timer1;
        if (motion->z.v < 0) {
            return;
        }
        if ((s16)timer1 > 0) {
            motion->z.v = 0;
            motion->velocity_z = -motion->velocity_z;
            return;
        }
        motion->z.v = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->velocity_z = ((func_80071494() & 0xFF) << 11) + 0xFFEB0000;
        obj->timer.u = (func_80071494() & 0xF) + 30;
        obj->state.u++;
        return;
    case 2:
        func_8003EA54(part);
        motion->velocity_z += 0x30000;
        obj->timer.u--;
        if (motion->z.v >= 0) {
            motion->z.v = 0;
            if (obj->timer.s < 0) {
                object_value = D_805301C0[obj->kind];
                part->clut = 0;
                part->unk_04 = 0;
                part->frame_ticks = 0;
                part->source = object_value;
                motion->velocity_z = 0;
                obj->timer.u = 150;
                obj->state.u++;
            } else {
                motion->velocity_z = -motion->velocity_z >> 1;
            }
        }
        call_result = func_80240810(falling_object_update_address, motion, score_bounce_motion_data, town_motion_state);
        if (call_result != 0) {
            scene_value_total = values.v[obj->kind] * 1000 + scene_value_total;
            U16_AT(obj, 4) = 255;
            return;
        }
        return;
    case 3:
        timer3 = obj->timer.u;
        timer3--;
        obj->timer.u = timer3;
        if ((s16)timer3 < 0) {
            obj->timer.u = 31;
            obj->state.u++;
        }
        call_result = func_80240810(falling_object_update_address, motion, score_bounce_motion_data, town_motion_state);
        if (call_result != 0) {
            scene_value_total = valuep[obj->kind] * 1000 + scene_value_total;
            U16_AT(obj, 4) = 255;
            return;
        }
        return;
    case 4:
        if (func_80240810(falling_object_update_address, motion, score_bounce_motion_data, town_motion_state) != 0) {
            scene_value_total = valuep[obj->kind] * 1000 + scene_value_total;
            S16_AT(obj, 4) = 255;
        }
        if ((obj->timer.u >> 2) & 1) {
            part->flags |= 0x80;
        } else {
            part->flags &= 0xFF7F;
        }
        timer4 = obj->timer.u;
        timer4--;
        obj->timer.u = timer4;
        if ((s16)timer4 > 0) {
            return;
        }
        obj->state.u = 255;
        return;
    case 255:
        func_8023FB18(obj->unk_08);
        U16_AT(obj, -2) |= 0x8000;
        scene_object_flags |= 0x8000;
        return;
    }
}
