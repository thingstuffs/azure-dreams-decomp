#include "common.h"
#include "records/Rec_D_80016000.h"





typedef struct S_8051E954_3 {
    u8 pad_00[0x208];
    M2C_UNK (*unk_208)(M2C_UNK);
} S_8051E954_3;   /* (*(void **)((u8 *)temp_v1 + 0x20)) in func_8051E954 */

typedef struct S_8051E954_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8051E954_4;   /* ((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v in func_8051E954 */

typedef struct S_8051E954_5 {
    u8 pad_00[0x224];
    M2C_UNK (*unk_224)(s32 *);
} S_8051E954_5;   /* ((S_8051E954_4 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20 in func_8051E954 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;
extern s32 D_80019158;

typedef struct S_8051E954_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8051E954_0;   /* temp_s0 in func_8051E954 */


/* Builds and submits a three-word command sequence from the low 16 bits of the input. */
void func_8051E954(s32 command_value) {
    register s32 *command_words ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *context;
    s32 first_command;
    s32 second_command;

    first_command = (command_value & 0xFFFF) | 0x06800000;
    D_80019158 = first_command;
    second_command = (first_command & 0xFFFF) | 0x05000000;
    command_words = &D_80019158;
    ((S_8051E954_0 *)command_words)->unk_04 = second_command;
    command_value = (second_command & 0xFFFF) | 0xFF000000;
    context = ((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v;
    ((S_8051E954_0 *)command_words)->unk_08 = command_value;
    ((S_8051E954_3 *)((*(void **)((u8 *)context + 0x20))))->unk_208(0);
    ((S_8051E954_5 *)(((S_8051E954_4 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20))->unk_224(command_words);
}
