#include "common.h"
#include "m2c_compat.h"
#include "town/person/state.h"

extern void D_800AAC64(void *object, s32 context, s32 update_param, void *color_data);

typedef struct S_800AAE00_0 {
    u8 pad_00[0x15];
    s8 unk_15;
} S_800AAE00_0;   /* arg1 in set_person_status_and_code */

typedef struct S_800AAE00_1 {
    u8 pad_00[0x50];
    void (*unk_50)();
    u8 pad_54[0x18];
    s16 unk_6C;
} S_800AAE00_1;   /* arg0 in set_person_status_and_code */

/* Set the status flag and initialize the context's data pointer and code. */
void set_person_status_and_code(S_800AAE00_1 *context, S_800AAE00_0 *status) {
    status->unk_15 = 1;
    context->unk_50 = &D_800AAC64;
    context->unk_6C = 0x15;
}
