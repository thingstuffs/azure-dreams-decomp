#include "common.h"
#include "town/scene/collection.h"
#include "sdk/libc.h"
#include "town/scene/animation.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "town/devkit/old_minigame_imports.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} PackedRect;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} NaturalRect;

typedef union {
    PackedRect packed;
    NaturalRect natural;
} RectUnion;

typedef struct {
    RectUnion rect;
    u8 pad[16];
} LocalRecord;

extern s16 D_80132AF2;
extern PackedRect D_80526470;
extern u8 D_8053067C[];






typedef struct S_8080EEC4_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    s16 unk_18;
    u16 unk_1A;
    u8 pad_1C[0x6];
    s16 unk_22;
    s16 unk_24;
} S_8080EEC4_3;   /* work in animate_collection_center_sprite */

/* Per-frame camera/approach step: measure the distance to the target, then run the six-state approach machine. */
void animate_collection_center_sprite(CollectionCenterControlBody *ctrl, ObjectPosition *setup, SpriteFrameState *view)
{
    LocalRecord local;
    S_8080EEC4_3 *work;
    s32 dx;
    s32 dy;
    s32 dx_square;
    s32 dy_square;
    s32 distance;
    s32 step;
    s16 step_copy;
    s32 case_value;
    s32 case_value_2;
    s32 case_value_3;
    s32 case_x;
    s32 case_delta;
    s32 value;
    s32 limit;
    s32 x;
    s32 state;
    s32 old_angle;
    s32 copied;
    s32 early_far;
    s32 case5_old;
    s32 case5_next;

    dx = (town_motion_state.x.v - 0x03600000) >> 16;
    dy = (collection_target_y - 0x03600000) >> 16;
    work = (S_8080EEC4_3 *)ctrl->work;
    old_angle = view->angle_z;
    local.rect.packed = D_80526470;
    dx_square = dx * dx;
    dy_square = dy * dy;
    distance = func_8006AB90(dx_square + dy_square);
    copied = setup->z.v;
    (*(s32 *)((u8 *)ctrl + (0x60))) = copied;

    if (distance < (collection_target_y > 0x035FFFFF ? 0xB9 : 0xC1)) {
        if (D_80132AF2 >= setup->z.w.i) {
            town_motion_state.x.v = ctrl->previous_x;
            collection_target_y = ctrl->previous_y;
        }
        (*(s32 *)((u8 *)ctrl + (0x58))) = town_motion_state.x.v;
        ctrl->unk_5C = collection_target_y;
        if (distance < 0x80) {
            ctrl->unk_62 -= (0x80 - distance) >> 1;
        }
    
    } else {
        early_far = distance < 0xD1;
        if (early_far) {
            if (D_80132AF2 >= setup->z.w.i) {
                town_motion_state.x.v = ctrl->previous_x;
                collection_target_y = ctrl->previous_y;
            }
    
            {
                s32 dx_abs;
                s32 dy_abs;
                dx_abs = abs(dx);
                dy_abs = dy;
                dy_abs = abs(dy_abs);
                if (dx_abs > dy_abs || collection_target_y <= 0x033FFFFF) {
                    ctrl->unk_5C = collection_target_y;
                    if (dx > 0) {
                        ctrl->unk_58 = town_motion_state.x.v - 0x00280000;
                    } else {
                        ctrl->unk_58 = town_motion_state.x.v + 0x00280000;
                    }
                } else {
                    ctrl->unk_58 = town_motion_state.x.v;
                    if (dy > 0) {
                        ctrl->unk_5C = collection_target_y - 0x00280000;
                    } else {
                        ctrl->unk_5C = collection_target_y + 0x00280000;
                    }
                }
            }
        } else {
            ctrl->unk_58 = 0x03600000;
            ctrl->unk_5C = 0x03600000;
        }
    
    }

    (*(s32 *)((u8 *)ctrl + (4))) = town_motion_state.x.v;
    ctrl->previous_y = collection_target_y;

    value = work->unk_14 /
        ((work->unk_22 << 8) + 0x300);
    case_delta = (3 - work->unk_22) << 5;
    case_x = value + 0x40;
    step = case_delta + case_x;

    state = ctrl->phase;
    switch (state) {

    case 0:
        case_x = view->color.c.b;
        case_delta = 0x80 - case_x;
        case_x = *(volatile u8 *)&view->color.c.b + (case_delta >> 1);
        view->color.c.b = case_x;
        view->color.c.g = case_x;
        view->color.c.r = case_x;
        ctrl->unk_6C = 0x00080000;
        break;

    case 1:
        case_value = (s16)ctrl->phase_value;
        case_value += (case_value + 0x10) >> 4;
        ctrl->phase_value = case_value;
        if (step < (s16)case_value) {
            ctrl->phase_value = step;
            ctrl->phase = 2;
        }
        view->angle_z += (u16)ctrl->phase_value;
        break;

    case 2:
        case_value_2 = view->angle_z;
        case_value_2 += step;
        view->angle_z = case_value_2;
        step_copy = step;
        if (distance >= 0xA1 && collection_target_y > 0x03600000 &&
            work->unk_18 == 5) {
            ctrl->phase_value = step_copy;
            ctrl->phase = 3;
            break;
        }
        break;

    case 3:
        dx = view->angle_z & 0x7FF;
        dy = 0x155;
        if (dx >= 0x6AB) {
            work->unk_24 = 0;
        } else {
            distance = 4;
            limit = 0x554;
            while (1) {
                if (dx < limit) {
                    distance--;
                    if (distance >= 0) {
                        limit -= dy;
                        continue;
                    }
                }
                break;
            }
            work->unk_24 = (distance & 1) ? 1 : 2;
        }
        work->unk_1A = 0;
    case 4:
        dx = work->unk_22 == 2 ? 6 : 5;
        value = (s16)ctrl->phase_value;
        value -= value >> dx;
        ctrl->phase_value = value;
        view->angle_z += value;
        work->unk_1A += (u16)ctrl->phase_value;
        if ((s16)ctrl->phase_value < (1 << dx)) {
            ctrl->stop_ticks = 0;
            ctrl->phase = 5;
            break;
        }
        break;

    case 5:
        view->angle_z += (u16)ctrl->phase_value;
        work->unk_1A += (u16)ctrl->phase_value;
        case_value_3 = ctrl->stop_ticks + 1;
        ctrl->stop_ticks = case_value_3;
        if ((case_value_3 & 3) == 0) {
            ctrl->phase_value = (u16)(ctrl->phase_value - 2);
        }
        if ((s16)ctrl->phase_value < 4) {
            ctrl->phase = 0;
            break;
        }
        break;

    case 6:
        ctrl->phase = 7;
        ctrl->phase_value = 0;
    case 7:
        dx = 0;
        dy = 0x7A;
        do {
            local.rect.natural.x = dy;
            local.rect.natural.w = 6;
            x = ((s16)(u16)ctrl->phase_value >> 1) + dx;
            func_8006E854(&local, D_8053067C + ((x % 3) << 5));
            dy += 0x10;
            dx++;
            if (dx >= 3) {
                break;
            }
        } while (1);
        case5_old = (u16)ctrl->phase_value;
        case5_next = case5_old + 1;
        ctrl->phase_value = (u16)case5_next;
        if ((s16)case5_old >= 0xC6) {
            ctrl->phase = 0;
        }
    }

    view->angle_z &= 0xFFF;
    if ((old_angle >> 8) !=
        (view->angle_z >> 8)) {
        func_80058F88(0x701);
    }
}
