#include "common.h"

#define FIELD(base, type, offset) (*(type *)((s8 *)(base) + (offset)))

extern s32 func_80024A5C();
extern void func_80025598() __attribute__((noreturn));
typedef struct Rect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

typedef struct Work {
    Rect rect;
    s16 x;
    s16 y;
} Work;

extern Rect D_80024048;
extern s16 D_80026428;
extern s32 D_800814A0;

void func_80025360(void *arg0, void *arg1, void *arg2)
{
    Work sp18;
    s16 temp_v0;
    s16 temp_v1;
    s16 temp_v1_2;
    register void *obj ASM_REG("$16");
    register void *dest ASM_REG("$17");
    register s32 one ASM_REG("$18");
    register s16 rect_x ASM_REG("$2");
    register u16 mask ASM_REG("$2");
    Rect *data;

    obj = arg0;
    dest = arg2;
    data = &D_80024048;
    sp18.rect = *data;
    ASM_KEEP(obj);
    ASM_KEEP(dest);
    D_80026428 = 1;
    temp_v1 = FIELD(obj, s16, 0);
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            func_80025598();
            return;
        }
        rect_x = 0x340;
        goto block_5;
    }
    FIELD(obj, s16, 0) = (s16)((u16)FIELD(obj, s16, 0) + 1);
    mask = FIELD(dest, u16, 0x14);
    mask &= 0xFF7F;
    FIELD(dest, u16, 0x14) = mask;
    rect_x = 0x340;
    ASM_KEEP(rect_x);
block_5:
    sp18.rect.x = rect_x;
    sp18.rect.y = 0x100;
    sp18.rect.w = 0x60;
    sp18.rect.h = 0x40;
    sp18.x = 0x370;
    sp18.y = 0x120;
    one = 1;
    func_80024A5C(FIELD(obj, s32, 0x48), &sp18.rect, &sp18.x, one, one);
    temp_v1_2 = FIELD(obj, s16, 2);
    if (temp_v1_2 < 0x15) {
        FIELD(dest, s8, 0xE) = (s8)((temp_v1_2 << 7) / 20);
        FIELD(dest, s8, 0xD) = (s8)((FIELD(obj, s16, 2) << 7) / 20);
        FIELD(dest, s8, 0xC) = (s8)((FIELD(obj, s16, 2) << 7) / 20);
    }
    if (FIELD(obj, s16, 2) >= 0x51) {
        FIELD(dest, s8, 0xE) = (s8)(((0x64 - FIELD(obj, s16, 2)) << 7) / 20);
        FIELD(dest, s8, 0xD) = (s8)(((0x64 - FIELD(obj, s16, 2)) << 7) / 20);
        FIELD(dest, s8, 0xC) = (s8)(((0x64 - FIELD(obj, s16, 2)) << 7) / 20);
    }
    temp_v0 = (u16)FIELD(obj, s16, 2) + 1;
    FIELD(obj, s16, 2) = temp_v0;
    if (temp_v0 >= 0x65) {
        FIELD(obj, s16, 2) = 0;
        FIELD(obj, s16, 0) = (s16)((u16)FIELD(obj, s16, 0) + 1);
        FIELD(FIELD(obj, void *, 0x40), s16, 0x9C) = one;
        FIELD(obj, u16, -2) = (u16)(FIELD(obj, u16, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: A 16-byte Work aggregate plus held s0/s1/s2 roles fixes the 0x38 frame and unaligned copy.
   Rerouting to 2.7.2-cdk-G0 colors that copy a2/v1/a0; the zero-arg noreturn call becomes the retail tail j.
   A fixed-v0 rect_x/mask with a state-0-only ASM_KEEP yields both 0x340 loads and the single joined store. */
