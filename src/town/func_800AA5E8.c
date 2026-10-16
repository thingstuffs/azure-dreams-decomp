/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/slus_callbacks.h"



typedef struct S_800A7C98_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_800A7C98_0_pre;   

typedef struct S_800A7C98_0 {
    u8 pad_00[0x50];
    s32 unk_50;
} S_800A7C98_0;   

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80033CD8();
extern void townClearObjectStatusAndDispatchTarget();
extern s32 D_800A7DF8;
extern s32 D_800F8F88;

void func_800A7D48(void *object, s32 unused, s32 context) {
    ((S_800A7C98_0_pre *)object)[-1].unk_00 = &D_800A7DF8;
    ((S_800A7C98_0 *)object)->unk_50 = 0;
    townClearObjectStatusAndDispatchTarget(object, context, &D_800F8F88, 0);
    func_80033CD8(object, func_80045340);
}
