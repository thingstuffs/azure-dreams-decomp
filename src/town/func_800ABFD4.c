#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A9734_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x5C];
    s32 unk_60;
} S_800A9734_0;   /* arg0 in initialize_record_with_defaults; pointer addresses record offset 0x10 */

typedef struct S_800A9734_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A9734_1;   /* arg1 in initialize_record_with_defaults */

#define M2C_BREAK() 0
#define M2C_SYNC() 0

void configure_the_set_mode_n_3();
extern M2C_UNK D_800A6CF0;
extern M2C_UNK D_800D0E60;

/* Initializes the record and context using the default data. */
void initialize_record_with_defaults(void *record_data, S_800A9734_1 *context) {
    ((S_800A9734_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800A6CF0;
    ((S_800A9734_0 *)((u8 *)record_data - 0x10))->unk_60 = 0;
    configure_the_set_mode_n_3(record_data, context, &D_800D0E60);
    context->unk_08 = 0;
}
