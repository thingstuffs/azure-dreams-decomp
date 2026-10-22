#include "common.h"
#include "shared/object_flags.h"
#include "records/Rec_func_800B15B8_arg0.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in decay_shop_state_and_cleanup, addressed as arg0[-1] */


typedef struct S_800B1664_1 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800B1664_1;

typedef struct S_800B1664_2 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800B1664_2;

typedef struct S_800B1664_4 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800B1664_4;   /* ((Rec_func_800B15B8_arg0 *)arg0)->unk_C0 in decay_shop_state_and_cleanup */
void release_null_terminated_entries(u16 **entries);
void reset_five_shop_slots();

/* Halve a state value, decrement another, and trigger cleanup below the threshold. */
void decay_shop_state_and_cleanup(void *object) {
    u16 decay_value;
    s32 decay_shifted;
    S_800B1664_1 *decay_state;
    S_800B1664_2 *counter_state;

    decay_state = ((Rec_func_800B15B8_arg0 *)object)->unk_C0;
    decay_value = decay_state->unk_06;
    decay_shifted = decay_value << 0x10;
    decay_state->unk_06 = (u16) (decay_value - ((s32) ((decay_shifted >> 0x10) + ((u32) decay_shifted >> 0x1F)) >> 1));
    counter_state = ((Rec_func_800B15B8_arg0 *)object)->unk_C0;
    counter_state->unk_04 = (u16) (counter_state->unk_04 - 0x100);
    if ((s16) ((S_800B1664_4 *)(((Rec_func_800B15B8_arg0 *)object)->unk_C0))->unk_06 < 0x11) {
        release_null_terminated_entries(object + 0xD0);
        reset_five_shop_slots(object);
        ((ObjectRetirementFlags *)object)[-1].unk_00 = (u16) (((ObjectRetirementFlags *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
