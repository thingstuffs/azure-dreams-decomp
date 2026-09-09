#include "common.h"
#include "m2c_compat.h"

typedef s32 (*M2C_CALLBACK)(void *, s32);

typedef struct S_80019F94_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019F94_1;   /* (temp_s0 + held_arg0->unk_10) in func_80019F94 */


M2C_UNK func_80019EA8();
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
    register s32 temp_s0 ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 temp_s1;
    register s32 base_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    held_arg0 = arg0;
    func_80019EA8(held_arg0->unk_14, held_arg0->unk_1A);
    global = (M2C_UNK *)0x80020000;
loop_1:
    global[-3874] = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_s1 = 0;
    ASM_KEEP(temp_s1);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    for (;;) {
        temp_s0 = temp_s1 * 0x10;
        if ((func_8001ADE0(((S_80019F94_1 *)((temp_s0 + held_arg0->unk_10)))->unk_0C) != 0) || ((*(M2C_CALLBACK *)((u8 *)((M2C_UNK8 *)(temp_s0 + (base_value = held_arg0->unk_10))) + 0))(held_arg0, temp_s1) != 0)) {
            temp_s1++;
            continue;
        }
        break;
    }
    if (global[-3874] == 0) {
        return temp_s1;
    }
    goto loop_1;
}
