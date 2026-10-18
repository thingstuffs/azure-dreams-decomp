#include "common.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

typedef struct S_800A782C_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A782C_0_pre;   /* the 0x10 bytes before arg0 in initialize_timed_scale_object, addressed as arg0[-1] */

typedef struct S_800A782C_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800A782C_1;   /* arg1 in initialize_timed_scale_object */



M2C_UNK func_80033CD8();
void initialize_randomized_scale_timer();
void clear_object_status_and_dispatch_target();
extern M2C_UNK D_800A78AC;
extern M2C_UNK D_800F842C;

/* Initialize the object and reset its state before completing setup. */
void initialize_timed_scale_object(void *object, S_800A782C_1 *state, s32 context) {
    ((S_800A782C_0_pre *)object)[-1].unk_00 = &D_800A78AC;
    clear_object_status_and_dispatch_target(object, context, &D_800F842C, 0);
    func_80033CD8(object, func_80045340);
    state->unk_0A = 0;
    initialize_randomized_scale_timer(object, state, context);
}
