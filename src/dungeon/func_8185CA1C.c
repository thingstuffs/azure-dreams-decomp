#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_8002418C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEDB0[3];

/* Creates and initializes an effect with a randomized offset from the source position. */
void func_8185CA1C(s32 effect_param, void *source_pos)
{
    s32 random_offset;
    void *sprite;
    int color;
    void *effect_pos;
    void *effect;

    effect = func_8003FC64(0x212);
    if (effect != 0)
    {
        *((M2C_UNK **)(((s8 *)effect) + 0x10)) = &D_8002418C;
        sprite = *((void **)(((s8 *)effect) + 0xC));
        *((s32 *)(((s8 *)effect) + 0x20)) = effect_param;
        color = 0x80;
        *((s8 *)(((s8 *)sprite) + 0xE)) = color;
        *((s8 *)(((s8 *)sprite) + 0xD)) = color;
        *((s8 *)(((s8 *)sprite) + 0xC)) = color;
        func_8003DB94(sprite, D_800DEDB0, 0);
        *((s16 *)(((s8 *)sprite) + 0x1E)) = 0x1800;
        *((s16 *)(((s8 *)sprite) + 0x1C)) = 0x1800;
        *((s16 *)(((s8 *)sprite) + 0x12)) = 0x7E0B;
        *((u16 *)(((s8 *)sprite) + 0x10)) =
            (u16)(*((u16 *)(((s8 *)sprite) + 0x10)) | 0x60);
        *((u16 *)(((s8 *)sprite) + 0x14)) =
            (u16)(*((u16 *)(((s8 *)sprite) + 0x14)) | 0x10C);
        func_8004491C(effect, &D_80045340);
        effect_pos = *((void **)(((s8 *)effect) + 8));
        rand();
        *((u16 *)(((s8 *)effect_pos) + 2)) =
            (u16)(*((u16 *)(((s8 *)source_pos) + 2)));
        *((u16 *)(((s8 *)effect_pos) + 6)) =
            (u16)(*((u16 *)(((s8 *)source_pos) + 6)));
        random_offset = rand();
        *((s16 *)(((s8 *)effect_pos) + 0xA)) =
            (s16)((*((u16 *)(((s8 *)source_pos) + 0xA)) - 0x20) -
                  (random_offset % 16));
    }
}
