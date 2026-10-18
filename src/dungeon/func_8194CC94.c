#include "modules/dungeon_ovl_7e6b7800.h"

void allocate_effect_and_initialize_sprite(s32 effect_data, s32 effect_param, s32 render_param)
{
    int color;
    void *effect;
    void *state;
    void *sprite;
    effect = func_8003FD64(0x12, ((s32 *)&D_80083498.next));
    if (effect != 0) {
        *((s32 **) (((s8 *) effect) + 0x10)) = &D_800240F0;
        color = 0x80;
        state = effect + 0x20;
        *((s16 *) (((s8 *) state) + 0xC)) = 0;
        *((s16 *) (((s8 *) state) + 0xE)) = 0;
        *((s32 *) (((s8 *) effect) + 0x20)) = effect_data;
        *((s32 **) (((s8 *) state) + 4)) = ((s32 *)&D_80083498.next);
        *((s32 *) (((s8 *) state) + 8)) = effect_param;
        sprite = *((void **) (((s8 *) effect) + 0xC));
        *((s8 *) (((s8 *) sprite) + 0xE)) = color;
        *((s8 *) (((s8 *) sprite) + 0xD)) = color;
        *((s8 *) (((s8 *) sprite) + 0xC)) = color;
        *((s16 *) (((s8 *) sprite) + 0x1E)) = 0x1000;
        *((s16 *) (((s8 *) sprite) + 0x1C)) = 0x1000;
        *((s16 *) (((s8 *) sprite) + 0x12)) = 0x7E00;
        *((s32 *) (((s8 *) sprite) + 8)) = render_param;
        *((u16 *) (((s8 *) sprite) + 0x10)) = (u16) ((*((u16 *) (((s8 *) sprite) + 0x10))) | 0x20);
        *((u16 *) (((s8 *) sprite) + 0x14)) = (u16) ((*((u16 *) (((s8 *) sprite) + 0x14))) | 0x10C);
    }
}
