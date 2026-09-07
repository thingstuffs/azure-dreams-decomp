#include "common.h"



typedef s32 M2C_UNK;
typedef struct {
    s32 words[4];
} __attribute__((packed)) Copy16;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_UNALIGNED32(expr) (expr)

extern void func_80064BC0(void *, s32 *);

typedef struct S_80025FB0_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    s8 unk_12;
    s8 unk_13;
    s8 unk_14;
    s8 unk_15;
} S_80025FB0_0;   /* arg1 in func_80025FB0 */

typedef struct S_80025FB0_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
} S_80025FB0_1;   /* arg0 in func_80025FB0 */

void func_80025FB0(S_80025FB0_1 *arg0, S_80025FB0_0 *arg1) {
    s32 stack[4];
    s32 halfword;

    *(Copy16 *)arg0 = *(Copy16 *)arg1;
    halfword = arg1->unk_10;
    
    arg0->unk_10 = halfword;
    arg0->unk_14 = (s32) arg1->unk_12;
    arg0->unk_18 = (s32) arg1->unk_13;
    arg0->unk_1C = (s32) arg1->unk_14;
    if (arg1->unk_15 == 0) {
        stack[2] = 0;
        stack[1] = 0;
        stack[0] = 0;
        func_80064BC0(arg0, stack);
    }
}

/* MECHANISM: The packed 16-byte assignment produces the retail lwl/lwr and swl/swr copy.
   The callee's true two-argument ABI leaves the copy's $a2 dead and restores the load-delay nop.
   A named signed halfword plus ASM_KEEP preserves full-width liveness and selects lh before sh. */
