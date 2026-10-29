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
void advance_three_component_motion(void *timer_state, void *motion) {
    u16 ticks_left;

    ((ObjectPosition *)motion)->x.v = (s32) (((ObjectPosition *)motion)->x.v + ((ObjectPosition *)motion)->velocity_x);
    ((ObjectPosition *)motion)->y.v = (s32) (((ObjectPosition *)motion)->y.v + ((ObjectPosition *)motion)->velocity_y);
    ((ObjectPosition *)motion)->z.v = (s32) (((ObjectPosition *)motion)->z.v + ((ObjectPosition *)motion)->velocity_z);
    ticks_left = ((S_8081508C_1 *)timer_state)->unk_0E - 1;
    ((S_8081508C_1 *)timer_state)->unk_0E = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)timer_state + -2)) = (u16) (((ObjectStatusPrefix16 *)timer_state)[-1].flags | 0x8000);
        scene_object_flags |= 0x8000;
    }
}
