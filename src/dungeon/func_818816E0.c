#include "common.h"

typedef struct {
    u8 pad[0x24];
    s16 field24;
} Func818816E0Arg0;

typedef struct {
    s32 field0;
    s32 field4;
} Func818816E0Arg1;

typedef struct {
    u8 pad0[0x0C];
    u8 field0C;
    u8 field0D;
    u8 field0E;
    u8 pad1[0x0D];
    u16 field1C;
    u16 field1E;
} Func818816E0Arg2;

extern u16 D_800257CE[5];
extern s16 D_800257CC[5];
extern s32 D_800814A0[3];
s32 func_800644B8(s32 arg0);
s32 func_80064584(s32 arg0);

/* Moves and fades an effect, marking it inactive when its brightness falls below the cutoff. */
void func_80024EE0(void *effect_data, void *position_data, void *visual_data) {
    Func818816E0Arg0 *effect;
    Func818816E0Arg1 *position;
    register Func818816E0Arg2 *visual;
    u16 decay_value;
    u8 brightness;
    s32 angle;

    visual = (Func818816E0Arg2 *)visual_data;
    effect = (Func818816E0Arg0 *)effect_data;
    position = (Func818816E0Arg1 *)position_data;
    angle = effect->field24 << 8;
    D_800257CE[0] = D_800257CE[0] + 1;
    position->field0 = position->field0 + (func_80064584(angle) * 8);
    position->field4 = position->field4 + (func_800644B8(effect->field24 << 8) * 8);
    brightness = visual->field0E - 2;
    visual->field0E = brightness;
    visual->field0D = brightness;
    visual->field0C = brightness;
    if ((u32)(brightness & 0xFF) < 0x20U) {
        D_800257CC[0] = (s16)((u16)D_800257CC[0] - 1);
        ((u16 *)effect_data)[-1] = (u16)(((u16 *)effect_data)[-1] | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
    decay_value = visual->field1E;
    visual->field1E = (u16)(decay_value - (decay_value >> 7));
    visual->field1C = (u16)(visual->field1C + 8);
}
