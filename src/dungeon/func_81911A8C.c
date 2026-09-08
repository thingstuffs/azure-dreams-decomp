#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_81911A8C_0_pre {
    u16 unk_00;
} S_81911A8C_0_pre;   /* the 0x2 bytes before arg0 in func_81911A8C, addressed as arg0[-1] */

typedef struct S_81911A8C_0 {
    void * unk_00;
} S_81911A8C_0;   /* arg0 in func_81911A8C */

typedef struct S_81911A8C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81911A8C_1;   /* temp_v1 in func_81911A8C */

typedef struct S_81911A8C_2 {
    union { void * s; s32 u; } unk_00;   /* accessed as both */
} S_81911A8C_2;   /* &D_80083160 in func_81911A8C */

typedef struct S_81911A8C_3 {
    u8 pad_00[0x4];
    u8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 unk_07;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} S_81911A8C_3;   /* temp_s0 in func_81911A8C */

typedef struct S_81911A8C_4 {
    u8 pad_00[0x5];
    s8 unk_05;
} S_81911A8C_4;   /* arg2 in func_81911A8C */

typedef struct S_81911A8C_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_81911A8C_5;   /* ((S_81911A8C_2 *)(&D_80083160))->unk_00.s in func_81911A8C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_8006658C();
M2C_UNK func_800667A8();
extern M2C_UNK D_800814A0;
extern M2C_UNK D_80083160;

/* Draw a full-screen color overlay and mark the effect complete when its countdown ends. */
void func_81911A8C(void *effect, void *unused, void *fade_state) {
    s8 green_blue;
    s8 frames_left;
    void *overlay;
    void *effect_state;

    effect_state = ((S_81911A8C_0 *)effect)->unk_00;
    ((S_81911A8C_1 *)effect_state)->unk_14 = (u16) (((S_81911A8C_1 *)effect_state)->unk_14 + 1);
    overlay = ((S_81911A8C_5 *)(((S_81911A8C_2 *)(&D_80083160))->unk_00.s))->unk_8D0;
    ((S_81911A8C_5 *)(((S_81911A8C_2 *)(&D_80083160))->unk_00.s))->unk_8D0 = (void *) (overlay + 0x10);
    ((S_81911A8C_3 *)overlay)->unk_0C = 0x140;
    ((S_81911A8C_3 *)overlay)->unk_0E = 0xE0;
    ((S_81911A8C_3 *)overlay)->unk_08 = 0;
    ((S_81911A8C_3 *)overlay)->unk_0A = 0;
    ((S_81911A8C_3 *)overlay)->unk_04 = 0xC0;
    green_blue = -0x40 - (((S_81911A8C_4 *)fade_state)->unk_05 * 0xC);
    ((S_81911A8C_3 *)overlay)->unk_06 = green_blue;
    ((S_81911A8C_3 *)overlay)->unk_05 = green_blue;
    func_800667A8(overlay);
    ((S_81911A8C_3 *)overlay)->unk_07 = (u8) (((S_81911A8C_3 *)overlay)->unk_07 | 2);
    func_8006658C(((S_81911A8C_2 *)(&D_80083160))->unk_00.u + 0xB0, overlay);
    frames_left = (u8) ((S_81911A8C_4 *)fade_state)->unk_05 - 1;
    ((S_81911A8C_4 *)fade_state)->unk_05 = frames_left;
    if ((frames_left << 0x18) == 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_81911A8C_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
