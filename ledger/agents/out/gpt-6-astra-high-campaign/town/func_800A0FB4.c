#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

extern M2C_UNK func_80033CD8();
extern M2C_UNK func_80033D08();
extern M2C_UNK func_800478B8();
extern s32 func_800644B8();
extern s32 func_8009D20C(void *, M2C_UNK);
extern M2C_UNK D_80045340;
extern s32 D_800814A0[3];

/* Updates an object's pulse brightness and handles its completion state. */
void func_8009E714(void *object, M2C_UNK context, void *primitive) {
    s32 status_match;
    s16 phase;
    s32 wave;
    s32 wave_step;
    s32 brightness;

    status_match = func_8009D20C(object, context) == 1;
    if (func_8009D20C(object, context) == 1) {
        s8 *active_flag = FIELD(object, s8 **, 0x98);
        if (active_flag != 0) {
            *active_flag = 0;
        }
        func_80033D08(object);
        FIELD(object, u16 *, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }
    if (status_match == 2) {
        func_80033D08(object);
        return;
    }
    func_80033CD8(object, &D_80045340);
    phase = FIELD(object, u16 *, 0x6C) + 0x60;
    FIELD(object, u16 *, 0x6C) = phase;
    wave = func_800644B8(phase);
    wave_step = wave >> 7;
    if (wave < 0) {
        wave_step = (wave + 0x7F) >> 7;
    }
    brightness = (wave_step + 0x20) * 0x30;
    if (brightness < 0) {
        brightness += 0x3F;
    }
    brightness >>= 6;
    FIELD(primitive, s8 *, 0xE) = (s8)brightness;
    FIELD(primitive, s8 *, 0xD) = (s8)brightness;
    FIELD(primitive, s8 *, 0xC) = (s8)brightness;
    if (!(FIELD(object, u16 *, -2) & 0x8000) &&
        FIELD(object, u8 *, 0x4D) == 0x13) {
        func_800478B8(primitive);
    }
}
