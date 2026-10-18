#include "common.h"
#include "m2c_compat.h"

extern void configure_the_set_mode_n_1();
extern M2C_UNK D_800C26C0[3];
extern void *D_800D4F88[3];

typedef struct S_800C2664_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x38];
    s16 unk_8C;
    s16 unk_8E;
    u8 pad_90[0x4];
    u8 unk_94;
} S_800C2664_0;   /* arg0 in initialize_transform_object_values */

/* Initialize the object values to 0x40, apply its indexed setup, and assign its table. */
void initialize_transform_object_values(S_800C2664_0 *object, s32 setup_context, s32 unused) {
    object->unk_8C = 0x40;
    object->unk_8E = 0x40;
    configure_the_set_mode_n_1(object, setup_context, *(object->unk_94 + D_800D4F88));
    object->unk_50 = D_800C26C0;
}
