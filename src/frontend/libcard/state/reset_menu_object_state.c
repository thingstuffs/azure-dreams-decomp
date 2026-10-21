#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard/state.h"

typedef struct S_800274A8_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800274A8_0;

typedef struct S_800274A8_1 {
    s32 unk_00;
    u8 pad_04[0x38];
    s32 unk_3C;
} S_800274A8_1;   /* arg0 in reset_menu_object_state_2; pointer addresses record offset 0x10 */


/* cfail-repair: tf7-phase1-cache-v3 */
/* Clear flag 0x2000 and restore the saved field when the flag is set. */
void reset_menu_object_state_2(void *record_part) {
    u16 flags;
    S_800274A8_0 *base_record;

    base_record = record_part - 0x20;
    flags = base_record->unk_1E;
    if (flags & 0x2000) {
        base_record->unk_1E = (u16) (flags & 0xDFFF);
        ((S_800274A8_1 *)((u8 *)record_part - 0x10))->unk_00 = (s32) ((S_800274A8_1 *)((u8 *)record_part
            - 0x10))->unk_3C;
    }
}
