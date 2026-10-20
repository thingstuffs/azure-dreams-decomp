#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_818C2F10_0_pre {
    u16 unk_00;
} S_818C2F10_0_pre;   /* the 0x2 bytes before arg0 in update_vertical_drift_effect, addressed as arg0[-1] */

typedef struct S_818C2F10_0 {
    void * unk_00;
    u16 unk_04;
} S_818C2F10_0;   /* arg0 in update_vertical_drift_effect */

typedef struct S_818C2F10_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_818C2F10_1;

typedef struct S_818C2F10_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_818C2F10_2;   /* arg1 in update_vertical_drift_effect */

extern void func_800478B8(void *entity);                      /* extern */

/* Increment linked counters, reduce the stored value, and propagate status flags. */
void update_vertical_drift_effect(void *entry, S_818C2F10_2 *value_state, SpriteFrameState *status) {
    S_818C2F10_1 *linked_counts;

    linked_counts = ((S_818C2F10_0 *)entry)->unk_00;
    linked_counts->unk_0C = (u16) (linked_counts->unk_0C + 1);
    ((S_818C2F10_0 *)entry)->unk_04 = (u16) (((S_818C2F10_0 *)entry)->unk_04 + 1);
    value_state->unk_08 = (s32) (value_state->unk_08 + 0xFFF60000);
    func_800478B8(status);
    if (status->flags & 0x6000) {
        ((S_818C2F10_0_pre *)entry)[-1].unk_00 = (u16) (((S_818C2F10_0_pre *)entry)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
