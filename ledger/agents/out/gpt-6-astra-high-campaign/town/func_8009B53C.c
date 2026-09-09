#include "common.h"

extern void func_80098C40(s32 arg0, s32 arg1, s32 arg2);
extern s8 D_80082668;

/* Forward the values to func_80098C40 and clear D_80082668. */
void func_80098C9C(s32 primary_value, s32 secondary_value, s32 context_value) {
    func_80098C40(primary_value, secondary_value, context_value);
    D_80082668 = 0;
}
