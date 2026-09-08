#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Position {
    s16 pad0;
    s16 x;
    s16 pad4;
    s16 y;
} Position;

extern void func_800C170C(s32 arg0);
extern s32 func_800C2124(void);
extern Position D_80083780;


typedef struct S_800C21F8_0 {
    void (*unk_00)(void);
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
} S_800C21F8_0;   /* arg0 in func_800C21F8 */

s32 func_800C21F8(S_800C21F8_0 *arg0) {
    s32 temp_a0;
    register s32 temp_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 temp_v1 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */

    temp_v0 = arg0->unk_04;
    temp_v1 = D_80083780.x;
    temp_a0 = D_80083780.y;
    temp_v0 -= temp_v1;
    if (temp_v0 < 0) {
        temp_v0 = 0 - temp_v0;
    }
    temp_v1 = arg0->unk_06;
    temp_v0 = (s32)((u32)temp_v0 << 16);
    temp_v1 -= temp_a0;
    temp_a0 = temp_v1;
    if (temp_v1 < 0) {
        temp_a0 = 0 - temp_a0;
    }
    if ((arg0->unk_0C < (temp_v0 >> 16)) ||
        ((s16)temp_a0 > arg0->unk_0E)) {
        func_800C170C(temp_a0);
        arg0->unk_00 = (void (*)(void))func_800C2124;
           /* MATCH pin: retail basic-block layout depends on it */
        return 1;
    }
    return 0;
}

/* MECHANISM: A 24-byte frame and s0-held object preserve the delta live ranges.
   Spelling the second test as temp_a0 > field makes EXPAND issue sll before lh,
   closing the reorder; cdk-G0 supplies the split global base and sibcall tail. */
