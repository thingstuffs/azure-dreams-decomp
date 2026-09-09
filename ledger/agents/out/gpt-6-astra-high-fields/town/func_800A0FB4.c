#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_func_8009E714_0 {
    u8 pad_00[0x4D];
    u8 unk_4D;
    u8 pad_4E[0x1E];
    u16 unk_6C;
    u8 pad_6E[0x2A];
    void *unk_98;
} S_func_8009E714_0;

typedef struct S_func_8009E714_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_func_8009E714_1;

typedef struct S_func_8009E714_2 {
    u16 unk_00;
} S_func_8009E714_2;

extern M2C_UNK func_80033CD8();
extern M2C_UNK func_80033D08();
extern M2C_UNK func_800478B8();
extern s32 func_800644B8();
extern s32 func_8009D20C(void *, M2C_UNK);
extern M2C_UNK D_80045340;
extern s32 D_800814A0[3];

/* Updates an object's pulse brightness and handles its completion state. */
void func_8009E714(S_func_8009E714_0 *object, M2C_UNK context, S_func_8009E714_1 *primitive) {
    s32 status_match;
    s16 phase;
    s32 wave;
    s32 wave_step;
    s32 brightness;

    status_match = func_8009D20C(object, context) == 1;
    if (func_8009D20C(object, context) == 1) {
        s8 *active_flag = object->unk_98;
        if (active_flag != 0) {
            *active_flag = 0;
        }
        func_80033D08(object);
        ((S_func_8009E714_2 *)object)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }
    if (status_match == 2) {
        func_80033D08(object);
        return;
    }
    func_80033CD8(object, &D_80045340);
    phase = object->unk_6C + 0x60;
    object->unk_6C = phase;
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
    primitive->unk_0E = (s8)brightness;
    primitive->unk_0D = (s8)brightness;
    primitive->unk_0C = (s8)brightness;
    if (!(((S_func_8009E714_2 *)object)[-1].unk_00 & 0x8000) &&
        object->unk_4D == 0x13) {
        func_800478B8(primitive);
    }
}
