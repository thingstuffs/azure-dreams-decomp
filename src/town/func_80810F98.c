#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8052BC28() __attribute__((noreturn));
extern s32 D_80084D5C;

s32 func_80810F98(void *arg0)
{
    s16 state;
    register s32 call_arg ASM_REG("$4");
    void *object;

    state = FIELD(arg0, s16, 0);
    object = FIELD(arg0, void *, 4);
    call_arg = state;
    if (state == 0) {
        goto state_0;
    }
    call_arg = 0xFFF70000;
    if (state == 1) {
        goto state_1;
    }
    return func_8052BC28(call_arg, arg0);

state_0: {
        ASM_KEEP(call_arg);
        if (FIELD(object, u16, 0xC) & 2) {
            register s32 result ASM_REG("$2");
            result = call_arg + 1;
            FIELD(arg0, s16, 0) = result;
            return func_8052BC28(call_arg, arg0);
        }
        return call_arg + 1;
    }
state_1: {
        register s32 result ASM_REG("$2");
        call_arg |= 0xF7F8;
        result = FIELD(arg0, s32, 8) + call_arg;
        FIELD(arg0, s32, 8) = result;
        if (result <= 0x80808) {
            FIELD(arg0, u16, -2) |= 0x8000;
            result = D_80084D5C | 0x8000;
            D_80084D5C = result;
        }
        return result;
    }
}
