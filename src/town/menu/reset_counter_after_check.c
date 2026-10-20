#include "script_symbols.h"
#include "common.h"

#include "engine/object/test_resident_bitmap_bit_api.h"                         /* extern */
void accumulate_effect_step(void *updateState, s32 unused1, s32 unused2, void *accumulatorState);

typedef struct S_800A6EA4_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x3C];
    s16 unk_90;
} S_800A6EA4_0;   /* arg0 in reset_counter_after_check_99 */

/* Reset the object counter and select its next state when check 0x99 succeeds. */
void reset_counter_after_check_99(S_800A6EA4_0 *object) {
    if (test_resident_bitmap_bit(F_bookshelf_fall) != 0) {
        object->unk_90 = 0;
        object->unk_50 = &accumulate_effect_step;
    }
}
