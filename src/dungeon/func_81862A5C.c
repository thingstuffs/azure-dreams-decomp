#include "modules/dungeon_ovl_188298c.h"

void spawn_jittered_type_212_effect(s32 owner, void *source)
{
    s32 roll;
    void *render;
    int white;
    void *obj;
    obj = func_8003FC64(0x212);
    if (obj != 0) {
        *((s32 *) (((s8 *) obj) + 0x20)) = owner;
        *((M2C_UNK **) (((s8 *) obj) + 0x10)) = (void *)advance_fading_effect;
        render = *((void **) (((s8 *) obj) + 0xC));
        *((s8 *) (((s8 *) obj) + 0x24)) = 0;
        white = 0x80;
        *((s8 *) (((s8 *) render) + 0xE)) = white;
        *((s8 *) (((s8 *) render) + 0xD)) = white;
        *((s8 *) (((s8 *) render) + 0xC)) = white;
        func_8003DB94(render, D_800DEDB0, 0);
        *((s16 *) (((s8 *) render) + 0x1E)) = 0x1000;
        *((s16 *) (((s8 *) render) + 0x1C)) = 0x1000;
        *((s16 *) (((s8 *) render) + 0x12)) = 0x7E0B;
        *((u16 *) (((s8 *) render) + 0x10)) = (u16) ((*((u16 *) (((s8 *) render) + 0x10))) | 0x60);
        *((u16 *) (((s8 *) render) + 0x14)) = (u16) ((*((u16 *) (((s8 *) render) + 0x14))) | 0x10C);
        func_8004491C(obj, func_80045340);
        render = *((void **) (((s8 *) obj) + 8));
        rand();
        *((u16 *) (((s8 *) render) + 2)) = (u16) (*((u16 *) (((s8 *) source) + 2)));
        *((u16 *) (((s8 *) render) + 6)) = (u16) (*((u16 *) (((s8 *) source) + 6)));
        roll = rand();
        *((s16 *) (((s8 *) render) + 0xA)) = (s16) (((*((u16 *) (((s8 *) source) + 0xA))) - 0x40) - (roll % 16));
    }
}
