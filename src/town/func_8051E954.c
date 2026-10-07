#include "common.h"
#include "m2c_compat.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct S_8051E954_3 {
    u8 pad_00[0x208];
    M2C_UNK (*unk_208)(M2C_UNK);
} S_8051E954_3;   /* (*(void **)((u8 *)temp_v1 + 0x20)) in func_8051E954 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_80019158;

typedef struct S_8051E954_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8051E954_0;   /* temp_s0 in func_8051E954 */

/* Builds and submits a three-word command sequence from the low 16 bits of the input. */
void func_8051E954(s32 command_value) {
    s32 *command_words;
    Rec_D_80016000 *context;

    command_value &= 0xFFFF;
    command_value |= 0x06800000;
    D_80019158 = command_value;
    command_value &= 0xFFFF;
    command_value |= 0x05000000;
    command_words = &D_80019158;
    ((S_8051E954_0 *)command_words)->unk_04 = command_value;
    command_value &= 0xFFFF;
    command_value |= 0xFF000000;
    context = D_80016000;
    ((S_8051E954_0 *)command_words)->unk_08 = command_value;
    ((S_8051E954_3 *)((context->unk_20)))->unk_208(0);
    ((M2C_UNK (*) (s32 *))D_80016000->unk_20->callback_224)(command_words);
}
