#include "common.h"
#include "shared/entity_objects.h"
#include "m2c_compat.h"
#include "shared/dungeon_delay_views.h"
#include "town/person/motion.h"

extern void D_800C5BA8(void *state, s32 *coords);
extern s32 town_target_height_offset;

   /* arg1 in move_motion_value_halfway_toward */

typedef struct S_800C5B48_1 {
    u8 pad_00[0x54];
    void (*unk_54)();
    u8 pad_58[0x14];
    u16 unk_6C;
} S_800C5B48_1;   /* arg0 in move_motion_value_halfway_toward */

/* Move the motion value halfway toward the target sum and switch callbacks when the countdown expires. */
void move_motion_value_halfway_toward(S_800C5B48_1 *actor, DelayMotionZ *motion) {
    s32 current_value;
    u16 ticks_left;

    current_value = motion->unk_08;
    motion->unk_08 = (s32) (current_value + ((s32) ((view_reference_entity.z.v + town_target_height_offset) - current_value) / 2));
    ticks_left = actor->unk_6C - 1;
    actor->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        actor->unk_54 = &D_800C5BA8;
    }
}
