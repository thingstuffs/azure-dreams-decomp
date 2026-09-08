#include "common.h"

extern s32 D_80083E98[];
extern s32 D_8002644C[];
extern s32 D_800263C0[];

s32 func_80022138(void);
s32 func_80022160(void);
void func_800264D8(void *arg0);
void func_80026494(void *arg0);

/* Selects a state table or handler based on the context and current status. */
void func_8002651C(void *context) {
    if (D_80083E98[*(s32 *)((s8 *)context + 0x2C) << 5] != 0) {
        *(s32 **)((s8 *)context - 0x10) = D_8002644C;
        return;
    }
    if (func_80022138() >= 3) {
        *(s32 **)((s8 *)context - 0x10) = D_800263C0;
        return;
    }
    if (func_80022160() != 0) {
        func_80026494(context);
        return;
    }
    func_800264D8(context);
}
