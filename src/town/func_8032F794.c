#include "common.h"
#include "m2c_compat.h"

typedef s32 (*M2C_CALLBACK)(void *, s32);

typedef struct S_80019F94_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019F94_1;   /* (temp_s0 + held_arg0->unk_10) in func_80019F94 */


M2C_UNK func_80019EA8();
s32 func_80019FC8() __attribute__((noreturn));
s32 func_8001ADE0();
extern M2C_UNK D_8001C378[];

typedef struct S_80019F94_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
} S_80019F94_0;   /* held_arg0 in func_80019F94 */

s32 func_80019F94(void *arg0) {
    S_80019F94_0 *held_arg0;
    M2C_UNK *global;
    register s32 temp_s0 ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */
    s32 temp_s1;
    register s32 base_value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    held_arg0 = arg0;
    func_80019EA8(held_arg0->unk_14, held_arg0->unk_1A);
    global = (M2C_UNK *)0x80020000;
loop_1:
    global[-3874] = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    temp_s1 = 0;
    ASM_KEEP(temp_s1);   /* MATCH pin: keeps a constant in a register as retail does */
    temp_s0 = temp_s1 * 0x10;
    if ((func_8001ADE0(((S_80019F94_1 *)((temp_s0 + held_arg0->unk_10)))->unk_0C) != 0) || ((*(M2C_CALLBACK *)((u8 *)((M2C_UNK8 *)(temp_s0 + (base_value = held_arg0->unk_10))) + 0))(held_arg0, temp_s1) != 0)) {
        temp_s1++;
        ASM_TAILSLOT_PIN_TIED(temp_s1);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_80019FC8();
    }
    if (global[-3874] == 0) {
        return temp_s1;
    }
    goto loop_1;
}
