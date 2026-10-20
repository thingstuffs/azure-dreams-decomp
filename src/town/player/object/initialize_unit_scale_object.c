#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8009CD18_arg1.h"

typedef struct S_800A6E1C_0 {
    s32 * unk_00;
    u8 pad_04[0x5C];
    s32 * unk_60;
} S_800A6E1C_0;   /* arg0 in initialize_unit_scale_object; pointer addresses record offset 0x10 */


struct Rec_D_800CFCB4; void configure_the_set_mode_n_3(struct Rec_D_800CFCB4 *, s32, s32);  /* extern */
void initialize_object_transform_and_state(s32, void *, s32);             /* extern */
extern M2C_UNK D_800A6CF0;
extern M2C_UNK D_800A6EA4;
extern M2C_UNK D_800D0DC0;

/* Initializes object callbacks and state, then sets unit scale. */
void initialize_unit_scale_object(void *object, s32 init_param, Rec_func_8009CD18_arg1 *transform) {
    ((S_800A6E1C_0 *)((u8 *)object - 0x10))->unk_00 = &D_800A6CF0;
    ((S_800A6E1C_0 *)((u8 *)object - 0x10))->unk_60 = &D_800A6EA4;
    initialize_object_transform_and_state((s32)(object), transform, 0xA);
    configure_the_set_mode_n_3(object, init_param, (s32)(&D_800D0DC0));
    transform->unk_20 = 0x1000;
    transform->unk_1E = 0x1000;
    transform->unk_1C = 0x1000;
    transform->unk_16 = 0;
}
