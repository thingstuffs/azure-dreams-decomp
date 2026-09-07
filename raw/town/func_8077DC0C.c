#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80016464(void) __attribute__((noreturn));
extern void func_80017670(s32);
extern void *D_80016000;
extern M2C_UNK D_8001601C;
extern M2C_UNK D_8001605E;
extern M2C_UNK D_800162A4;
extern M2C_UNK *D_80017760;

void func_8077DC0C(void) {
    u8 *temp_a2;
    void *state;
    s32 event;
    register void *dispatch_value ASM_REG("$2");
    register void *dispatch_base ASM_REG("$3");

    state = D_80016000;
    D_80017760 = &D_800162A4;
    temp_a2 = M2C_FIELD(state, s32 *, 0x40) + (M2C_FIELD(state, s32 *, 8) * 8);
    if (*temp_a2 != 0) {
        dispatch_value = (void *)0x80010000;
        ASM_KEEP(dispatch_value);
        dispatch_base = M2C_FIELD(state, void **, 0x1C);
        ASM_USE(dispatch_base);
        dispatch_value = (u8 *)dispatch_value + 0x605E;
        ASM_TAILSLOT_PIN(dispatch_value);
        func_80016464();
    }
    ASM_CLOBBER("$2");
    dispatch_value = (void *)0x80010000;
    ASM_KEEP(dispatch_value);
    dispatch_base = M2C_FIELD(state, void **, 0x1C);
    dispatch_value = (u8 *)dispatch_value + 0x601C;
    M2C_FIELD(dispatch_base, M2C_UNK **, 0x40) = dispatch_value;
    event = 0x7E;
    *temp_a2 = (*temp_a2 + 1) & 1;
    func_80017670(event);
    func_80017670(0x7F);
}
