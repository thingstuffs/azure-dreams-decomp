#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8009CD18_arg1.h"

typedef struct S_800A6DA0_0 {
    void (*unk_00)(void *, void *, void *);
    u8 pad_04[0x5C];
    s32 unk_60;
} S_800A6DA0_0;   /* arg0 in initialize_scaled_effect_object; pointer addresses record offset 0x10 */


struct Rec_D_800CFCB4; void configure_the_set_mode_n_3(struct Rec_D_800CFCB4 *, s32, s32);  /* extern */
void initialize_object_transform_and_state(s32, void *, s32);             /* extern */
void retire_object_on_check_or_callback(void *object, void *input, void *context);
extern M2C_UNK D_800D0DA8;

/* Initializes the object and sets its transform scale to 0xC00 on all axes. */
void initialize_scaled_effect_object(void *object, s32 context, Rec_func_8009CD18_arg1 *transform) {
    ((S_800A6DA0_0 *)((u8 *)object - 0x10))->unk_00 = &retire_object_on_check_or_callback;
    ((S_800A6DA0_0 *)((u8 *)object - 0x10))->unk_60 = 0;
    initialize_object_transform_and_state((s32)(object), transform, 0x48);
    configure_the_set_mode_n_3(object, context, (s32)(&D_800D0DA8));
    transform->unk_20 = 0xC00;
    transform->unk_1E = 0xC00;
    transform->unk_1C = 0xC00;
}
