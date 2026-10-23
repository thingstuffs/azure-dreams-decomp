#include "common.h"
#include "dungeon/effect/shade.h"

#include "dungeon/effect/screen.h"
extern s32 set_or_clear_actor_status_slot(void *, s32, s32);
extern void adjust_source_value_and_finalize(void *, void *);
extern u8 D_800E1D28[9];

/* Conditionally apply D_800E1D28 to the target after checking a scaled low-byte value. */
void apply_conditional_target_effect(void *target, s32 packedValue, void *record) {
    u8 savedPackedValue = packedValue;
    if (try_trigger_target_record_effect(target, 4, record) == 0) {
        u32 lowByteQuarter = savedPackedValue;
        lowByteQuarter >>= 2;
        /*
         * Original bug: set_or_clear_actor_status_slot returns a slot index (0..3), or -1 on
         * failure. Testing it as nonzero misreports slot 0 as failure and -1 as success.
         * Slot-0 success loses its message; rejected insertion prints success.
         * try_apply_confusion_status uses the nonnegative success test.
         */
        if ((set_or_clear_actor_status_slot(target, 0x17, lowByteQuarter + 2) << 16) != 0) {
            adjust_source_value_and_finalize(target, D_800E1D28);
        }
    }
}
