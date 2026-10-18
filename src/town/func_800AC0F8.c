#include "common.h"

typedef struct S_800A9858_0 {
    s32 * unk_00;
    u8 pad_04[0x5C];
    s32 * unk_60;
} S_800A9858_0;   /* arg0 in initialize_variant_record_pointers_and_clear_state; pointer addresses record offset 0x10 */

typedef struct S_800A9858_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A9858_1;   /* arg1 in initialize_variant_record_pointers_and_clear_state */
void set_resident_flag_when_item_present(u16 *record);
void retire_object_on_check_or_callback(void *object, void *input, void *context);

/* Initialize the record's pointers and clear the associated state field. */
void initialize_variant_record_pointers_and_clear_state(void *record_data, S_800A9858_1 *state) {
    ((S_800A9858_0 *)((u8 *)record_data - 0x10))->unk_00 = &retire_object_on_check_or_callback;
    ((S_800A9858_0 *)((u8 *)record_data - 0x10))->unk_60 = &set_resident_flag_when_item_present;
    state->unk_08 = 0;
}
