/* Relink of matched dungeon/func_80AF3470; every changed retail word is a paired relocation. */
#define D_80170874 D_80158874
#include "modules/dungeon_resource10_slot0.h"
extern s32 func_800644B8(s32);

void func_8015CC70(void *effect, void *motion, void *render)
{
    R10_80174C70_LocalVector direction;
    R10_80174C70_LocalTable directions;
    long render_or_step = (long)render;
    s32 phase_angle;
    s32 phase_offset;
    u8 brightness;
    u32 frame;

    directions = (*(R10_80174C70_LocalTable *)&D_80158874);

    frame = (u32)((R10_80174C70_S_80174C70_0 *)effect)->unk_1A.s;
    switch (frame) {
    case 0:
    case 1:
    case 2:
    case 3:
        brightness = ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0E + 0x18;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0E = brightness;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0D = brightness;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0C = brightness;

    case 4:
        ((R10_80174C70_S_80174C70_0 *)effect)->unk_62 = 0x20;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.s = 0xA00;
        break;

    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 16:
    case 15:
        ((R10_80174C70_S_80174C70_0 *)effect)->unk_62 = 0x18;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u += 0x180;
        break;

    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
        brightness = ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0E - 0xE;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0E = brightness;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0D = brightness;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_0C = brightness;
        ((R10_80174C70_S_80174C70_0 *)effect)->unk_62 = 0x18;
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u += 0x30;
        break;

    case 26:
        (*(u16 *)((u8 *)effect + (-2))) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
        return;
    }

    ((R10_80174C70_S_80174C70_0 *)effect)->unk_1A.u++;

    if (((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u >= 0x1000) {
        ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u -= 0x1000;
    }

    phase_angle = ((R10_80174C70_S_80174C70_1 *)((void *)render_or_step))->unk_1A.u;
    phase_offset = phase_angle - 0x400;
    phase_angle = phase_offset;
    if ((s16)phase_offset < 0) {
        phase_angle = phase_offset + 0x1000;
    }
    {
        s16 normalized_phase = phase_angle;
        s32 sine = func_80064584(normalized_phase);
        s32 sine_radius = ((R10_80174C70_S_80174C70_0 *)effect)->unk_62;
        s32 sine_product = sine_radius * sine;
        s32 cosine_angle = normalized_phase;

        render_or_step = sine_product << 4;
        phase_offset = func_800644B8(cosine_angle);
    }

    {
        u8 *direction_ptr = (u8 *)&directions;
        s32 heading_x = ((R10_80174C70_S_80174C70_0 *)effect)->unk_18;
        s32 radius = ((R10_80174C70_S_80174C70_0 *)effect)->unk_62;

        direction.x = (*(u16 *)((u8 *)direction_ptr + (((heading_x - 0x400) >> 7) & 0x1C)));

        {
            s32 cosine_product = radius * phase_offset;
            s32 heading_y = ((R10_80174C70_S_80174C70_0 *)effect)->unk_18;

            direction_ptr += ((heading_y - 0x400) >> 7) & 0x1C;
            direction.y = (*(u16 *)((u8 *)direction_ptr + (2)));

            {
                s32 height_step = cosine_product << 4;

                ((R10_80174C70_S_80174C70_2 *)motion)->unk_08 += height_step;
            }
        }
    }
    {
        s32 axis_step = direction.x;
        s32 axis_product = axis_step * render_or_step;

        axis_step = axis_product >> 4;
        ((R10_80174C70_S_80174C70_2 *)motion)->unk_0C = axis_step;
    }
    {
        s32 axis_step = direction.y;
        s32 axis_product = axis_step * render_or_step;

        ((R10_80174C70_S_80174C70_2 *)motion)->unk_10 = axis_product >> 4;
    }
    ((R10_80174C70_S_80174C70_2 *)motion)->unk_00 += ((R10_80174C70_S_80174C70_2 *)motion)->unk_0C;
    ((R10_80174C70_S_80174C70_2 *)motion)->unk_04 += ((R10_80174C70_S_80174C70_2 *)motion)->unk_10;

    return;
}
