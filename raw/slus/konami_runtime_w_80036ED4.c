#include "common.h"

#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80036D4C(s32 arg0, void *arg1, s32 *arg2, s16 arg3,
                          s32 arg4, s32 arg5);
extern void func_80036F24(void *arg0, void *arg1, void *arg2);

void func_80036ED4(void *arg0, void *arg1, s32 *arg2, s16 arg3,
                   s16 arg4, s32 arg5) {
    func_80036D4C((s32)arg0, arg1, arg2, arg3, arg4, arg5);
    func_80036F24((s8 *)arg0 + 0x20,
                  M2C_FIELD(arg0, void **, 0x8),
                  M2C_FIELD(arg0, void **, 0xC));
}
