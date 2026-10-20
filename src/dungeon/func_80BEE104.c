#include "modules/dungeon_resource16_slot0.h"
#include "shared/sprite_frame_state.h"

void create_angled_source_effect(
    s32 unused_0, R16_80173904_S_80173904_3 *origin, s32 unused_2, s32 unused_3, s16 angle, u16 depth_offset)
{
    void *object;
    R16_80173904_S_80173904_0 *state;
    SpriteFrameState *display;
    R16_80173904_S_80173904_4 *transform;
    s16 wrapped_angle;

    object = func_8003FC64(0x212);
    wrapped_angle = angle;
    if (object != NULL) {
        state = (R16_80173904_S_80173904_0 *)((u8 *)object + 0x20);
        state->unk_1A = 0x14;
        state->unk_20 = 0x14;
        state->unk_1E = angle;
        ((R16_80173904_S_80173904_1 *)object)->unk_10 = ((void *)update_expanding_spiral_effect);
        register_node(object, project_sprite_chain);

        display = ((R16_80173904_S_80173904_1 *)object)->unk_0C;
        display->tpage_abr = 0x60;
        display->flags |= 0xC;
        if (rand() & 1) {
            display->flags |= 1;
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
        display->scale_y = 0x1000;
        display->scale_x = 0x1000;
        display->color.c.r = 0x40;
        display->color.c.b = 0x40;
        display->color.c.g = 0xC0;
        state->unk_00 = display->color.c.r;
        state->unk_01 = display->color.c.g;
        state->unk_02 = display->color.c.b;
        func_8003DB94(display, ((u8 *)D_800DEC70), 0);
        display->clut = 0x7DCF;
        display->flags |= 0x100;
    }
}
