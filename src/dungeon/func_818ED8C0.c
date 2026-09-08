#include "common.h"
#include "m2c_compat.h"

typedef struct S_800250C0_0 {
    u16 unk_00;
    u8 pad_02[0x2];
    s16 unk_04;
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    u8 pad_0E[0x12];
    s16 unk_20;
    u8 pad_22[0x8];
    u8 unk_2A;
    u8 unk_2B;
} S_800250C0_0;   /* arg0 in func_800250C0; pointer addresses record offset 0x2 */

typedef struct S_800250C0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800250C0_1;   /* arg2 in func_800250C0 */


extern s16 D_80026428[];
extern s32 D_800814A0[3];
extern void *D_80024008[];

/* Updates an effect's grayscale intensity and animation frame, marking it finished at the end of its lifetime. */
void func_800250C0(void *effect, s32 age, S_800250C0_1 *color, s32 fade_ticks) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    void **jump_table;
    s32 frame_count;
    s32 fade_scaled;
    s32 intensity;

    age = ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_06;
    fade_ticks = ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_0C;
    D_80026428[0] = 1;
    if (age < fade_ticks) {
        fade_scaled = age * 3;
        goto set_intensity;
    }
    frame_count = ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_04;
    frame_count -= age;
    fade_scaled = frame_count * 3;
set_intensity:
    intensity = (fade_scaled * 0x10) / fade_ticks;
    color->unk_0E = (s8) intensity;
    color->unk_0D = (s8) intensity;
    color->unk_0C = (s8) intensity;
    frame_count = ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_20;
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_06 = (s16) ((u16) ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_06 + 1);
    if ((u32) frame_count >= 8U) {
        goto check_lifetime;
    }
    jump_table = D_80024008;
    (void)jt_keep; goto *jump_table[(u32)(frame_count)];
jt_c0:
jt_c1:
jt_c2:
jt_c4:
jt_c5:
jt_c6:
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_20 = (s16) ((u16) ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_20 + 1);
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2A = (u8) (((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2A + 0x10);
    goto check_lifetime;
jt_c3:
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_20 = (s16) ((u16) ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_20 + 1);
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2A = (u8) (((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2A - 0x30);
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2B = (u8) (((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2B + 0x20);
    goto check_lifetime;
jt_c7:
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_20 = 0;
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2A = (u8) (((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2A - 0x30);
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2B = (u8) (((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_2B - 0x20);
check_lifetime:
    if (((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_06 < ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_04) {
        goto done;
    }
    ((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_00 = (u16) (((S_800250C0_0 *)((u8 *)effect - 0x2))->unk_00 | 0x8000);
    D_800814A0[0] = D_800814A0[0] | 0x8000;
done:
    return;
}
