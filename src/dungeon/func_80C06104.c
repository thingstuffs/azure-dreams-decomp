/* Relink of matched dungeon/func_80BEE104; every changed retail word is a paired relocation. */
#define dungeonCreateAngledSourceEffect func_8015B904
#define dungeonUpdateExpandingSpiralEffect D_8015B738
#include "modules/dungeon_resource16_slot0.h"
extern s32 func_800644B8(s32);
extern s32 rand(void);

void func_8015B904(
    s32 unused_0, R16_80173904_S_80173904_3 *origin, s32 unused_2, s32 unused_3, s16 angle, u16 depth_offset)
{
    void *object;
    R16_80173904_S_80173904_0 *state;
    R16_80173904_S_80173904_2 *display;
    R16_80173904_S_80173904_4 *transform;
    s16 wrapped_angle;

    object = func_8003FC64(0x212);
    wrapped_angle = angle;
    if (object != NULL) {
        state = (R16_80173904_S_80173904_0 *)((u8 *)object + 0x20);
        state->unk_1A = 0x14;
        state->unk_20 = 0x14;
        state->unk_1E = angle;
        ((R16_80173904_S_80173904_1 *)object)->unk_10 = ((void *)dungeonUpdateExpandingSpiralEffect);
        func_8004491C(object, func_80045340);

        display = ((R16_80173904_S_80173904_1 *)object)->unk_0C;
        display->unk_10 = 0x60;
        display->unk_14 |= 0xC;
        if (rand() & 1) {
            display->unk_14 |= 1;
        }

        transform = ((R16_80173904_S_80173904_1 *)object)->unk_08;
        state->unk_40 = origin->unk_00;
        state->unk_44 = origin->unk_04;
        while (wrapped_angle >= 0x1001) {
            wrapped_angle -= 0x1000;
        }

        transform->unk_00 = state->unk_40 + ((state->unk_20 * func_80064584(wrapped_angle)) << 4);
        transform->unk_04 = state->unk_44 + ((state->unk_20 * func_800644B8(wrapped_angle)) << 4);
        transform->unk_0A = origin->unk_0A + depth_offset;

        display = ((R16_80173904_S_80173904_1 *)object)->unk_0C;
        display->unk_1E = 0x1000;
        display->unk_1C = 0x1000;
        display->unk_0C = 0x40;
        display->unk_0E = 0x40;
        display->unk_0D = 0xC0;
        state->unk_00 = display->unk_0C;
        state->unk_01 = display->unk_0D;
        state->unk_02 = display->unk_0E;
        func_8003DB94(display, ((u8 *)D_800DEC70), 0);
        display->unk_12 = 0x7DCF;
        display->unk_14 |= 0x100;
    }
}
