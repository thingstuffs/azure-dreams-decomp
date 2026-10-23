#include "common.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"


typedef struct S_80026B00_1 {
    u16 unk_00;
    u8 pad_02[0xE];
    u16 unk_10;
} S_80026B00_1;   /* arg0 in advance_scene_motion_until_timeout; pointer addresses record offset 0x2 */


/* Advance the position and flag the record and global state when its timer expires. */
void advance_scene_motion_until_timeout(void *record_data, ObjectPosition *motion) {
    u16 ticks_left;

    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
    ticks_left = ((S_80026B00_1 *)((u8 *)record_data - 0x2))->unk_10 - 1;
    ((S_80026B00_1 *)((u8 *)record_data - 0x2))->unk_10 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_80026B00_1 *)((u8 *)record_data - 0x2))->unk_00 = (u16) (((S_80026B00_1 *)((u8 *)record_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
