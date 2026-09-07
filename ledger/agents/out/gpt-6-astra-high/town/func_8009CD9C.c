#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80033CD8();
extern M2C_UNK func_80098928();
extern u8 D_80082660[];
extern M2C_UNK D_800970FC;

typedef struct S_8009A4FC_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A4FC_0;   /* arg0 in func_8009A4FC */

/* Processes the object, clears its indexed flag, and invokes the next handler. */
void func_8009A4FC(S_8009A4FC_0 *object, M2C_UNK forwardedArg1, M2C_UNK forwardedArg2) {
    func_80033CD8(object, &D_800970FC);
    D_80082660[object->unk_40 * 8] = 0;
    func_80098928(object, forwardedArg1, forwardedArg2);
}
