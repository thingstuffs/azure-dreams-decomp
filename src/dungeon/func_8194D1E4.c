#include "modules/dungeon_ovl_7e6b7800.h"

void allocate_effect_with_endpoints(s32 object_value, void *start_pos, void *end_pos, s16 setting, Row_8194D1E4_FourWords params_a,
    Row_8194D1E4_FourWords params_b, Row_8194D1E4_Packed8 packed_params) {
    s32 start_x;
    s32 start_y;
    s32 start_z;
    s32 word_0;
    s32 word_1;
    s32 word_2;
    s32 word_3;
    void *state;
    void *object;

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = object + 0x20;
        (*(s32 **)((u8 *)object + 0x10)) = &D_80024918;
        (*(s32 *)((u8 *)object + 0x20)) = object_value;
        ((Row_8194D1E4_S_800249E4_0 *)state)->unk_74 = 0;
        ((Row_8194D1E4_S_800249E4_0 *)state)->unk_76 = setting;
        start_x = (*(s32 *)((u8 *)start_pos + 0));
        (*(s32 *)((u8 *)state + 0x1C)) = start_x;
        (*(s32 *)((u8 *)state + 0x34)) = start_x;
        start_y = (*(s32 *)((u8 *)start_pos + 4));
        (*(s32 *)((u8 *)state + 0x20)) = start_y;
        (*(s32 *)((u8 *)state + 0x38)) = start_y;
        start_z = (*(s32 *)((u8 *)start_pos + 8));
        (*(s32 *)((u8 *)state + 0x24)) = start_z;
        (*(s32 *)((u8 *)state + 0x3C)) = start_z;
        (*(s32 *)((u8 *)state + 4)) = (s32) (*(s32 *)((u8 *)end_pos + 0));
        (*(s32 *)((u8 *)state + 8)) = (s32) (*(s32 *)((u8 *)end_pos + 4));
        (*(s32 *)((u8 *)state + 0xC)) = (s32) (*(s32 *)((u8 *)end_pos + 8));
        (*(s32 *)((u8 *)state + 0x40)) = (s32) ((s32) ((*(s32 *)((u8 *)end_pos + 0)) - (*(s32 *)((u8 *)start_pos + 0)))
            >> 3);
        (*(s32 *)((u8 *)state + 0x44)) = (s32) ((s32) ((*(s32 *)((u8 *)end_pos + 4)) - (*(s32 *)((u8 *)start_pos + 4)))
            >> 3);
        (*(s32 *)((u8 *)state + 0x48)) = (s32) ((s32) ((*(s32 *)((u8 *)end_pos + 8)) - (*(s32 *)((u8 *)start_pos + 8)))
            >> 3);
        word_0 = params_a.words[0];
        word_1 = params_a.words[1];
        word_2 = params_a.words[2];
        word_3 = params_a.words[3];
        (*(s32 *)((u8 *)object + 0x6C)) = word_0;
        (*(s32 *)((u8 *)object + 0x70)) = word_1;
        (*(s32 *)((u8 *)object + 0x74)) = word_2;
        (*(s32 *)((u8 *)object + 0x78)) = word_3;
        word_0 = params_b.words[0];
        word_1 = params_b.words[1];
        word_2 = params_b.words[2];
        word_3 = params_b.words[3];
        (*(s32 *)((u8 *)object + 0x7C)) = word_0;
        (*(s32 *)((u8 *)object + 0x80)) = word_1;
        (*(s32 *)((u8 *)object + 0x84)) = word_2;
        (*(s32 *)((u8 *)object + 0x88)) = word_3;
        *(Row_8194D1E4_Packed8 *)((u8 *)object + 0x8C) = packed_params;
    }
}

/* MECHANISM: Two 16-byte plus one packed 8-byte by-value args preserve the 0x28/s0-s3 hold set.
   Scalarized copy bursts color through v0,v1,a0,a1 while the allocation result is held in a2.
   A derived sp base with ASM_KEEP prevents packed tail loads folding from lwl/lwr pairs into lw;
   the paired tail source reads then also eliminate both downstream branch-displacement drifts. */
