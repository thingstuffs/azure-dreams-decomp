#include "common.h"

#include "common.h"

typedef s8 s8_local;

#define FIELD(base, type, offset) (*(type)((s8_local *)(base) + (offset)))

extern void func_80036D4C(s32, void *, s32 *, s16, s32, s32);
extern void func_80037090(void *, void *, void *);

void func_80037030(void *arg0, void *arg1, s32 *arg2, s16 arg3, s16 arg4, s32 arg5) {
    void *call_arg0;
    void *call_arg1;
    void *call_arg2;

    func_80036D4C((s32)arg0, arg1, arg2, arg3, arg4, arg5);
    call_arg0 = (s8_local *)arg0 + 0x20;
    call_arg1 = FIELD(arg0, void **, 0x08);
    call_arg2 = FIELD(arg0, void **, 0x0C);
    FIELD(arg0, void **, 0x10) = (void *)&func_80037090;
    FIELD(call_arg2, s32 *, 0x0C) = 0;
    func_80037090(call_arg0, call_arg1, call_arg2);
}
