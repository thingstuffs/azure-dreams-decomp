#include "common.h"
typedef s32 M2C_UNK;


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern u8 D_80171E20[];
extern s32 D_8008346C[];
extern s16 D_80083228[5];
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80047784(void *, u8, s32);
extern u8 D_801753E4[];

typedef struct S_801735E8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801735E8_0;   /* base0 in func_801735E8 */

typedef struct S_801735E8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    M2C_UNK * unk_2C;
} S_801735E8_1;   /* arg2 in func_801735E8 */

typedef struct S_801735E8_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801735E8_2;   /* arg3 in func_801735E8 */

typedef struct S_801735E8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801735E8_3;   /* arg1 in func_801735E8 */

void func_801735E8(void *arg0, S_801735E8_3 *arg1, S_801735E8_1 *arg2, S_801735E8_2 *arg3) {
    S_801735E8_0 *base0;
    u16 temp_v0;
    u16 temp_v0_2;
    s32 temp_v1;
    base0 = arg0;

    temp_v1 = base0->unk_9B;
    if (temp_v1 == 1) {
        goto state1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state0;
        }
        goto done;
    }
    if (temp_v1 == 2) {
        goto state2;
    }
    if (temp_v1 == 3) {
        goto state3;
    }
    goto done;

state0:
    if (arg2->unk_14 & 0x8000) {
        base0->unk_9B = 3U;
        arg2->unk_14 = (u16) (arg2->unk_14 | 0x6000);
        func_8009C12C(arg3, arg2, arg3->unk_2A, 1);
        goto done;
    }
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    temp_v0 = base0->unk_9B;
    base0->unk_96 = 0U;
    base0->unk_9B = (u8) (temp_v0 + 1);
    goto done;

state1:
        temp_v0_2 = base0->unk_96 + 1;
        base0->unk_96 = temp_v0_2;
    if ((s16) temp_v0_2 != 4 && !(arg2->unk_14 & 0xE000)) {
        goto done;
    }
    arg2->unk_2C = &D_801753E4;
    func_80047784(arg2, D_801753E4[(((s32) (*D_80083228 + arg3->unk_2A + 0x100) >> 9) & 7)], 0);
    func_800A56E0(0x808);
    temp_v0 = base0->unk_9B;
    base0->unk_96 = 0U;
    base0->unk_9B = (u8) (temp_v0 + 1);
    goto done;

state2:
    temp_v0 = base0->unk_96 + 1;
    base0->unk_96 = temp_v0;
    if ((s16) temp_v0 != 4 && !(arg2->unk_14 & 0xE000)) {
        goto done;
    }
    func_8009C12C(arg3, arg2, arg3->unk_2A, 1);
    temp_v0 = base0->unk_9B;
    base0->unk_96 = 0U;
    base0->unk_9B = (u8) (temp_v0 + 1);
    goto done;

state3:
    if (arg2->unk_14 & 0xE000) {
        func_800AD594(arg3, 0x100);
        base0->unk_8C = D_80171E20;
        *D_8008346C = 0;
        func_800A4ACC(arg3);
        arg3->unk_46 = (u16) (arg3->unk_46 & 0x7FFF);
    }

done:
    return;
}
