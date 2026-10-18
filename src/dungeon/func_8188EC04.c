#include "common.h"

extern s32 try_trigger_target_record_effect(s32, s32);
extern s32 set_or_clear_actor_status_slot(s32, s32, s32);
extern void adjust_source_value_and_finalize(s32, void *);
extern u8 D_800E1D28[9];

/* Conditionally apply D_800E1D28 to the target after checking a scaled low-byte value. */
void apply_conditional_target_effect(s32 target, s32 packedValue) {
    u8 savedPackedValue = packedValue;
    if (try_trigger_target_record_effect(target, 4) == 0) {
        u32 lowByteQuarter = savedPackedValue;
        lowByteQuarter >>= 2;
        if ((set_or_clear_actor_status_slot(target, 0x17, lowByteQuarter + 2) << 16) != 0) {
            adjust_source_value_and_finalize(target, D_800E1D28);
        }
    }
}
