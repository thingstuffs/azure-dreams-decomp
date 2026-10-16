#include "common.h"
#include "shared/slus_callbacks.h"

typedef s32 M2C_UNK;

typedef struct S_800A782C_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A782C_0_pre;   /* the 0x10 bytes before arg0 in townInitializeTimedScaleObject, addressed as arg0[-1] */

typedef struct S_800A782C_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800A782C_1;   /* arg1 in townInitializeTimedScaleObject */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
void townInitializeRandomizedScaleTimer();
void townClearObjectStatusAndDispatchTarget();
extern M2C_UNK D_800A78AC;
extern M2C_UNK D_800F842C;

/* Initialize the object and reset its state before completing setup. */
void townInitializeTimedScaleObject(void *object, S_800A782C_1 *state, s32 context) {
    ((S_800A782C_0_pre *)object)[-1].unk_00 = &D_800A78AC;
    townClearObjectStatusAndDispatchTarget(object, context, &D_800F842C, 0);
    func_80033CD8(object, func_80045340);
    state->unk_0A = 0;
    townInitializeRandomizedScaleTimer(object, state, context);
}
