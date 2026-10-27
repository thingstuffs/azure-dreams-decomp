#include "common.h"
#include "shared/position_views.h"
#include "town/player/coordinates.h"
#include "shared/game_work.h"
#include "shared/vector.h"




typedef struct {
    u8 pad0[8];
    s32 field8;
    u8 padC[0xBC];
    s16 fieldC8;
} TownState;

extern s16 input_angle_with_offset(s32, s16);
extern s32 rsin(s32);
extern s32 rcos(s32);
extern void func_800652AC(IntVector3 *, IntVector3 *, IntVector3 *);

/*
 * Forms a perpendicular step of sine/cosine times 32 from the held input direction and applies it
 * only when the side-test sign is unchanged after movement.
 */
void move_the_actor_perpendicular_selected_direction_unless_step_changes_sides(void *position_data)
{
    MotionDeltaView *actor = position_data;
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

    direction.x = rsin(direction_index);
    direction.y = rcos(direction_index);
    direction.z = 0;

    fixed_coord = actor->velocity_x;
    if (fixed_coord < 0) {
        fixed_coord += 0xFFF;
    }
    position.x = fixed_coord >> 12;

    direction_ptr = &direction;
    fixed_coord = actor->velocity_y;
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

    fixed_coord = actor->velocity_x + step.x;
    if (fixed_coord < 0) {
        fixed_coord += 0xFFF;
    }
    position.x = fixed_coord >> 12;

    direction_ptr = &direction;
    fixed_coord = actor->velocity_y + step.y;
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

    actor->velocity_x += step.x;
    actor->velocity_y += step.y;
}
