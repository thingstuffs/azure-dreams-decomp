#include "common.h"
#include "shared/game_work.h"
#include "shared/vector.h"


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

extern s16 input_angle_with_offset(s32, s16);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern void func_800652AC(IntVector3 *, IntVector3 *, IntVector3 *);

/* Moves the actor perpendicular to the selected direction unless the step changes sides. */
void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(Actor *actor)
{
    IntVector3 direction;
    IntVector3 step;
    IntVector3 position;
    IntVector3 side_result;
    s16 direction_index;
    s32 initial_side;
    s32 fixed_coord;
    IntVector3 *direction_ptr;
    IntVector3 *position_ptr;
    IntVector3 *call_result;

    direction_index = input_angle_with_offset(g_game_work.buttons, g_game_work.view.camera_rotation.parts.viewAngle);
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
        step.x = direction.y << 5;
        step.y = (-direction.x) << 5;
    } else {
        step.x = (-direction.y) << 5;
        step.y = direction.x << 5;
    }

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
