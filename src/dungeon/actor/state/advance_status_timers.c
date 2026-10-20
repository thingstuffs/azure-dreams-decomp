#include "common.h"

typedef struct S_800A4ACC_0 {
    u8 pad_00[0x2C];
    s8 unk_2C;
    s8 unk_2D;
} S_800A4ACC_0;

typedef struct S_800A4ACC_1 {
    s32 unk_00;
} S_800A4ACC_1;   /* arg0 in advance_status_timers; pointer addresses record offset 0x18 */

extern void end_status_effect_message();
extern void apply_capped_damage_and_hit_effect();

/* Advance four status timers toward zero and clear expired statuses. */
s32 advance_status_timers(void *record) {
    s32 slot_index;
    s8 status;
    s8 duration;
    u8 expired_status;
    slot_index = 3;
    do {
        status = ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2C;
        if (status != 0) {
            if (status == 5) {
                apply_capped_damage_and_hit_effect(record, ((S_800A4ACC_1 *)((u8 *)record - 0x18))->unk_00);
            }
            duration = ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D;
            if (duration != 0) {
                if (duration > 0) {
                    ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D =
                    (s8)((u8)((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D - 1);
                } else if (duration < 0) {
                    ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D =
                    (s8)((u8)((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D + 1);
                }
                if (((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2D == 0) {
                    expired_status = (u8)((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2C;
                    ((S_800A4ACC_0 *)(record + slot_index * 2))->unk_2C = 0;
                    end_status_effect_message(record, (s8)expired_status);
                }
            }
        }
        slot_index -= 1;
    } while (slot_index >= 0);
}
