#include "common.h"

typedef s32 M2C_UNK;
typedef struct {
    s32 words[4];
} __attribute__((packed)) Copy16;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

extern void func_80064BC0(void *, s32 *);

void func_80025FB0(void *arg0, void *arg1) {
    s32 stack[4];
    s32 halfword;

    *(Copy16 *)arg0 = *(Copy16 *)arg1;
    halfword = M2C_FIELD(arg1, s16 *, 0x10);
    
    M2C_FIELD(arg0, s16 *, 0x10) = halfword;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s8 *, 0x12);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s8 *, 0x13);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(arg1, s8 *, 0x14);
    if (M2C_FIELD(arg1, s8 *, 0x15) == 0) {
        stack[2] = 0;
        stack[1] = 0;
        stack[0] = 0;
        func_80064BC0(arg0, stack);
    }
}

/* MECHANISM: The packed 16-byte assignment produces the retail lwl/lwr and swl/swr copy.
   The callee's true two-argument ABI leaves the copy's $a2 dead and restores the load-delay nop.
   A named signed halfword plus ASM_KEEP preserves full-width liveness and selects lh before sh. */
