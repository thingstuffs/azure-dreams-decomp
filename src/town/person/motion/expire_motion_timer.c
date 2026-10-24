#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
void advance_motion_and_switch_handler(Rec_func_80094268_arg0 *object, EntityRec *motion, void *context);

typedef struct S_800C3FC8_0 {
    u8 pad_00[0x54];
    s32 * unk_54;
    u8 pad_58[0x14];
    u16 unk_6C;
} S_800C3FC8_0;   /* arg0 in expire_motion_timer */


/* Decrements the timer and changes the handler and motion value when it becomes negative. */
void expire_motion_timer(S_800C3FC8_0 *object, ObjectPosition *motion) {
    s16 remaining_ticks;

    remaining_ticks = object->unk_6C - 1;
    object->unk_6C = remaining_ticks;
    if (remaining_ticks < 0) {
        object->unk_54 = &advance_motion_and_switch_handler;
        motion->velocity_z = 0xFFF60000;
    }
}
