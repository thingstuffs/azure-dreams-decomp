#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct EffectColor {
    u8 pad[0xC];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

extern u16 D_800257CE[5];
extern s16 D_800257CC[5];
extern s32 D_800814A0;

extern void func_8002491C(void) __attribute__((noreturn));
void func_80024A98(void *);

void func_81880F28(void *arg0, void *arg1) {
    register void *motion ASM_REG("$5") = arg1;
    void *object;
    EffectColor *color;
    s16 state;
    s32 value;

    D_800257CE[0]++;
    state = FIELD(arg0, s16, 0xA);

    if (state == 1) {
        goto state_1;
    }
    if (state >= 2) {
        goto check_state_2;
    }
    if (state == 0) {
        goto state_0;
    }
    func_8002491C();
    return;

check_state_2:
    if (state == 2) {
        goto state_2;
    }
    func_8002491C();
    return;

state_0:
    object = FIELD(arg0, void *, 0);
    FIELD(object, s32, 0x1C) |= 0x10000000;
    FIELD(arg0, u16, 0xA)++;

state_1:
    color = FIELD(FIELD(arg0, void *, 0), EffectColor *, -0x14);

    value = color->red + 1;
    color->red = value;
    if ((u32)(value & 0xFF) >= 0xC1U) {
        color->red = 0xC0;
    }

    value = color->green - 1;
    color->green = value;
    if ((u32)(value & 0xFF) < 0x40U) {
        color->green = 0x40;
    }

    value = color->blue - 1;
    color->blue = value;
    if ((u32)(value & 0xFF) < 0x40U) {
        color->blue = 0x40;
    }

    if (D_800257CC[0] >= 14) {
        goto update_motion;
    }

    FIELD(arg0, u16, 0xA)++;
    func_8002491C();
    return;

state_2:
    color = FIELD(FIELD(arg0, void *, 0), EffectColor *, -0x14);

    value = color->red - 4;
    color->red = value;
    if ((u32)(value & 0xFF) < 0x80U) {
        color->red = 0x80;
    }

    value = color->green + 4;
    color->green = value;
    if ((u32)(value & 0xFF) >= 0x81U) {
        color->green = 0x80;
    }

    value = color->blue + 4;
    color->blue = value;
    if ((u32)(value & 0xFF) >= 0x81U) {
        color->blue = 0x80;
    }

    if (D_800257CC[0] == 0) {
        object = FIELD(arg0, void *, 0);
        FIELD(object, s32, 0x1C) &= ~0x10000000;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

update_motion:
    ASM_KEEP(motion);
    FIELD(motion, s32, 8) += FIELD(motion, s32, 0x14);
    FIELD(motion, s32, 0x14) += -0x80000;
    func_80024A98(motion);
    FIELD(arg0, u16, 0x1C)++;
}
