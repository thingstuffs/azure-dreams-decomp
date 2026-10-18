#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"

void process_paired_arrays_until_terminator(void);                            /* extern */
extern M2C_UNK D_800C0C28;

typedef struct S_800C0C48_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800C0C48_0;

/* Run setup, assign the retrieved object handler when present, and return -1. */
s32 run_setup_and_get_object_handler(s32 context, s32 value, s32 options) {
    S_800C0C48_0 *object;

    process_paired_arrays_until_terminator();
    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = &D_800C0C28;
    }
    return -1;
}
