#include "common.h"

typedef struct S_800B384C_0 {
    void (*unk_00)(void *);
    u8 pad_04[0xC];
    s32 unk_10;
    u8 pad_14[0x14];
    s32 unk_28;
} S_800B384C_0;   /* arg0 in set_record_base_and_data_pointer; pointer addresses record offset 0x10 */
void advance_five_step_fixed_point_ramp(void *sub_object);

/* Set the record's base and offset values and its data pointer. */
void set_record_base_and_data_pointer(void *record_field, s32 base_value) {
    ((S_800B384C_0 *)((u8 *)record_field - 0x10))->unk_28 = base_value;
    ((S_800B384C_0 *)((u8 *)record_field - 0x10))->unk_10 = (s32) (base_value + 0x20);
    ((S_800B384C_0 *)((u8 *)record_field - 0x10))->unk_00 = &advance_five_step_fixed_point_ramp;
}
