#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_status.h"

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


void func_80044A50(void *);
void func_8004491C(void *, void *);

/* Restores neutral color, then counts down and finalizes the effect. */
s32 func_800ACE34(StructArg0 *object_arg, s32 unused, StructArg2 *effect_arg) {
    StructArg0 *object = object_arg;
    StructArg2 *effect = effect_arg;
    u8 phase = object->unk9B;
    u8 red;
    u8 green;
    s32 green_step;
    u8 blue;
    s32 blue_step;
    u16 effect_count;
    StructArg0 *owner;

    switch (phase) {
    case 0:
        red = effect->unk0C;
        effect->unk0F++;
        unused = 0x80 - red;
        unused = unused / *(volatile u8 *)&effect->unk0F;
        green = effect->unk0D;
        green_step = 0x80 - green;
        green_step = green_step / *(u8 *)&effect->unk0F;
        blue = effect->unk0E;
        blue_step = 0x80 - blue;
        blue_step = blue_step / *(volatile u8 *)&effect->unk0F;
        red += unused;
        effect->unk0C = red;
        green += green_step;
        effect->unk0D = green;
        blue += blue_step;
        effect->unk0E = blue;
        if (*(u8 *)&effect->unk0F >= 8) {
            effect->unk0E = 0x80;
            effect->unk0D = 0x80;
            effect->unk0C = 0x80;
            object->unk9B++;
        }
        return 0;
    case 1:
        effect->unk0F--;
        if (effect->unk0F != 0) {
            return 0;
        }
        owner = (StructArg0 *)((u8 *)object - 0x20);
        func_80044A50(owner);
        effect->unk12 += 0x80;
        effect->unk14 &= 0xFFF3;
        func_8004491C(owner, func_80045340);
        effect_count = ((u16)dungeonStatus.unk_0A);
        effect_count--;
        dungeonStatus.unk_0A = effect_count;
        return 1;
    default:
        return 0;
    }
}
