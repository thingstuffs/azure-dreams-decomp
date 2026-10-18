#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void initialize_object_entries();          /* extern */
void finish_countdown_and_set_flags(void *object, s32 *position);
extern M2C_UNK D_800D6268;


typedef struct S_800C8FF0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800C8FF0_1;   /* arg1 in decrement_entity_timer_updating_motion */

/* Decrement the entity's timer, updating motion until the next state begins. */
void decrement_entity_timer_updating_motion(Rec_func_80094268_arg0 *entity, S_800C8FF0_1 *motion, s32 context) {
    u16 ticks_left;
    s32 transition_context;

    ticks_left = entity->unk_6C.as_u16 - 1;
    entity->unk_6C.as_u16 = ticks_left;
    transition_context = context;
    if ((s16) ticks_left < 0) {
        initialize_object_entries(entity, transition_context, &D_800D6268);
        entity->unk_6C.as_u16 = 3U;
        entity->unk_50.as_pm = &finish_countdown_and_set_flags;
        entity->unk_72.as_s16 = 0xC00;
        return;
    }
    entity->unk_72.as_s16 = 0x800;
    motion->unk_04 = (s32) (motion->unk_04 + 0xFFEAAAAB);
}
