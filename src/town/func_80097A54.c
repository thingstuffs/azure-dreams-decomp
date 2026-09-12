#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    u8 pad[0xC];
    s32 x;
    s32 y;
} Actor;

typedef struct {
    u8 pad0[8];
    s32 field8;
    u8 padC[0xBC];
    s16 fieldC8;
} TownState;

extern TownState D_80083160;
extern s16 func_80094BC8(s32, s16);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_800652AC(Vec3 *, Vec3 *, Vec3 *);

/* Moves the actor perpendicular to the selected direction unless the step changes sides. */
void func_800951B4(Actor *actor)
{
    Vec3 direction;
    volatile Vec3 step;
    Vec3 position;
    Vec3 side_result;
    s16 direction_index;
    s32 initial_side;
    s32 fixed_coord;
    s32 step_x;
    s32 step_y;
    TownState *town;
    Vec3 *direction_ptr;
    Vec3 *position_ptr;
    Vec3 *call_result;

    town = &D_80083160;
    direction_index = func_80094BC8(town->field8, town->fieldC8);
    if (direction_index == -1) {
        return;
    }

    direction.x = func_800644B8(direction_index);
    direction.y = func_80064584(direction_index);
    direction.z = 0;

    fixed_coord = actor->x;
    if (fixed_coord < 0) {
        fixed_coord += 0xFFF;
    }
    position.x = fixed_coord >> 12;

    direction_ptr = &direction;
    fixed_coord = actor->y;
    if (fixed_coord < 0) {
        fixed_coord += 0xFFF;
    }
    position_ptr = &position;
    call_result = &side_result;
    position.y = fixed_coord >> 12;
    position.z = 0;

    func_800652AC(direction_ptr, position_ptr, call_result);
    initial_side = side_result.z;

    if (initial_side >= 0) {
        s32 dir_x;
        s32 dir_y;

        dir_y = direction.y;
        dir_x = direction.x;
        step_x = dir_y << 5;
        step_y = -dir_x;
    } else {
        s32 dir_x;
        s32 dir_y;

        dir_y = direction.y;
        dir_x = direction.x;
        step_x = (-dir_y) << 5;
        step_y = dir_x;
    }
    step_y <<= 5;
    step.x = step_x;
    step.y = step_y;

    fixed_coord = actor->x + step.x;
    if (fixed_coord < 0) {
        fixed_coord += 0xFFF;
    }
    position.x = fixed_coord >> 12;

    direction_ptr = &direction;
    fixed_coord = actor->y + step.y;
    if (fixed_coord < 0) {
        fixed_coord += 0xFFF;
    }
    position_ptr = &position;
    call_result = &side_result;
    position.y = fixed_coord >> 12;
    position.z = 0;

    func_800652AC(direction_ptr, position_ptr, call_result);
    if (initial_side >= 0) {
        if (side_result.z < 0) {
            return;
        }
    } else if (side_result.z >= 0) {
        return;
    }

    actor->x += step.x;
    actor->y += step.y;
}
