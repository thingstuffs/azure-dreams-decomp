#include "common.h"
#include "m2c_compat.h"
#include "shared/types3a_types.h"

typedef struct S_800A9734_0 {
    s32 * unk_00;
    u8 pad_04[0x5C];
    s32 unk_60;
} S_800A9734_0;   /* arg0 in initialize_record_with_defaults; pointer addresses record offset 0x10 */

   /* arg1 in initialize_record_with_defaults */


void configure_the_set_mode_n_3();
void retire_object_on_check_or_callback(void *object, void *input, void *context);
extern M2C_UNK D_800D0E60;

/* Initializes the record and context using the default data. */
void initialize_record_with_defaults(void *record_data, EffectStateWordView *context) {
    ((S_800A9734_0 *)((u8 *)record_data - 0x10))->unk_00 = &retire_object_on_check_or_callback;
    ((S_800A9734_0 *)((u8 *)record_data - 0x10))->unk_60 = 0;
    configure_the_set_mode_n_3(record_data, context, &D_800D0E60);
    context->unk_08 = 0;
}
