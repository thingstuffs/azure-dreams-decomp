#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

#include "records/Rec_func_80094268_arg0.h"

void initialize_object_entries(void *state, s8 *output, s32 *entries);
void func_800CB570(Rec_func_80094268_arg0 *record, s32 forward_arg1, s32 forward_arg2);
extern M2C_UNK D_800D694C;

typedef struct S_800CB5DC_0 {
    u8 pad_00[0x54];
    s32 * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
    u8 pad_64[0x8];
    s16 unk_6C;
} S_800CB5DC_0;   /* arg0 in initialize_object_with_ten_tick_counter */

/* Initialize the object's state, clear its slot flag, and set its counter to ten. */
void initialize_object_with_ten_tick_counter(void *object, s32 unused, s8 *context) {
    initialize_object_entries(object, context, &D_800D694C);
    object_index_slots[((S_800CB5DC_0 *)object)->unk_60].unk_00 = 0;
    ((S_800CB5DC_0 *)object)->unk_54 = &func_800CB570;
    ((S_800CB5DC_0 *)object)->unk_6C = 0xA;
}
