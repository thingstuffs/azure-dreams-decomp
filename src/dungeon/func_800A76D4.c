#include "common.h"

typedef struct {
    u8 pad[0x9B];
    u8 unk9B;
} StructArg0;

typedef struct {
    u8 pad[0xC];
    u8 unk0C;
    u8 unk0D;
    u8 unk0E;
    u8 unk0F;
    u8 pad10[2];
    u16 unk12;
    u16 unk14;
} StructArg2;

typedef struct {
    u8 pad[0xA];
    u16 unk0A;
    u8 pad2[4];
} StructD80083460;

extern u8 D_80045340[0x10];
extern StructD80083460 D_80083460;

void func_80044A50(void *);
void func_8004491C(void *, void *);

/* Restores neutral color, then counts down and finalizes the effect. */
s32 func_800ACE34(StructArg0 *object_arg, s32 unused, StructArg2 *effect_arg) {
    register StructArg0 *object ASM_REG("$16") = object_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    StructArg2 *effect = effect_arg;
    u8 phase = object->unk9B;
    u8 red;
    u8 green;
    register s32 green_step ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 blue;
    s32 blue_step;
    u16 effect_count;

    if (phase == 0) goto restore_color;
    if (phase == 1) goto countdown;
    return 0;

restore_color:
    red = effect->unk0C;
    effect->unk0F++;
    unused = 0x80 - red;
    unused = unused / *(volatile u8 *)&effect->unk0F;
    green = effect->unk0D;
    green_step = 0x80 - green;
    green_step = green_step / *(volatile u8 *)&effect->unk0F;
    blue = effect->unk0E;
    blue_step = 0x80 - blue;
    blue_step = blue_step / *(volatile u8 *)&effect->unk0F;
    red += unused;
    effect->unk0C = red;
    green += green_step;
    effect->unk0D = green;
    blue += blue_step;
    effect->unk0E = blue;
    if (*(volatile u8 *)&effect->unk0F >= 8) {
        effect->unk0E = 0x80;
        effect->unk0D = 0x80;
        effect->unk0C = 0x80;
        object->unk9B++;
    }
    return 0;

countdown:
    effect->unk0F--;
    if (effect->unk0F != 0) {
        return 0;
    }
    object = (StructArg0 *)((u8 *)object - 0x20);
    func_80044A50(object);
    effect->unk12 += 0x80;
    effect->unk14 &= 0xFFF3;
    func_8004491C(object, D_80045340);
    effect_count = D_80083460.unk0A;
    effect_count--;
    D_80083460.unk0A = effect_count;
    return 1;
}
