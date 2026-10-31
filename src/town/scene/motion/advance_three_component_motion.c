#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/scene/motion.h"


   /* the 0x2 bytes before arg0 in advance_three_component_motion, addressed as arg0[-1] */

typedef struct S_8081508C_1 {
    u8 pad_00[0xE];
    u16 unk_0E;
} S_8081508C_1;   /* arg0 in advance_three_component_motion */


extern s32 scene_object_flags;

/* Advance the three motion components and set completion flags when the countdown expires. */
void advance_three_component_motion(void *timer_state_arg, void *motion_arg) {
    ObjectPosition *motion = motion_arg;
    S_8081508C_1 *timer_state = timer_state_arg;
    u16 ticks_left;

    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
    ticks_left = timer_state->unk_0E - 1;
    timer_state->unk_0E = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)timer_state + -2)) = (u16) (((ObjectStatusPrefix16 *)timer_state)[-1].flags | 0x8000);
        scene_object_flags |= 0x8000;
    }
}
