#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80404EA0();
extern M2C_UNK func_804053A0();
extern void func_8040552C() __attribute__((noreturn));
extern u8 D_8009DDD8[];

void func_802EE4E8(void *arg0) {
    if (*(s32 *)(D_8009DDD8 + (M2C_FIELD(arg0, s32 *, 0x7C) << 7)) != 0) {
        func_80404EA0();
        func_8040552C();
        return;
    }
    func_804053A0();
}
