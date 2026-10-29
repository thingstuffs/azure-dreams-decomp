#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"

typedef struct S_8051E954_3 {
    u8 pad_00[0x208];
    s32 (*unk_208)(s32);
} S_8051E954_3;


extern s32 D_80019158;

typedef struct S_8051E954_0 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_8051E954_0;

/* Builds and submits a three-word command sequence from the low 16 bits of the input. */
void submit_three_word_command(s32 command_value) {
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
    context = town_scene_root;
    ((S_8051E954_0 *)command_words)->unk_08 = command_value;
    ((S_8051E954_3 *)((context->services)))->unk_208(0);
    ((s32 (*) (s32 *))town_scene_root->services->callback_224)(command_words);
}
