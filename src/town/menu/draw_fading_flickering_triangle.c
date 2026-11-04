#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_effect_views.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "town/menu.h"
#include "town/menu/fading_triangle_effect.h"
#include "town/menu/flickering_triangle_packet.h"


typedef struct S_800A2690_1 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800A2690_1;   /* source in draw_fading_flickering_triangle */

   /* state in draw_fading_flickering_triangle */

/* Advance the effect lifetime and draw a fading, flickering triangle. */
void draw_fading_flickering_triangle(FadingTriangleEffectBody *effect)
{
    u16 angle;
    s32 base_x;
    u16 base_phase_x;
    u16 base_phase_y;
    u16 ticks_left;
    s16 phase_x;
    s16 phase_y;
    s32 center_x;
    s32 fade_wave;
    s32 wave_x2;
    s32 wave_x4;
    s32 wave_x8;
    s32 wave_y2;
    s32 wave_y4;
    s32 wave_y8;
    s32 biased_wave_y2;
    s32 wave_sum;
    s32 intensity;
    s32 draw_page;
    S_800A2690_1 *params;
    GpuContext *render_state;
    FlickeringTrianglePacket *triangle;
    u8 *draw_packet;

    params = (S_800A2690_1 *)effect->parameters;
    angle = params->unk_02;
    base_x = params->unk_00;
    base_phase_x = params->unk_04;
    ticks_left = effect->ticks_left - 1;
    base_phase_y = params->unk_06;
    center_x = base_x + effect->center_offset + 0xA0;
    effect->ticks_left = ticks_left;
    phase_x = base_phase_x + effect->phase_x_offset;
    phase_y = base_phase_y + effect->phase_y_offset;

    if ((ticks_left << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    } else {
        render_state = (GpuContext *)(*(u8 **)&g_game_work.draw_buffer);
        triangle = (FlickeringTrianglePacket *)render_state->packetCursor;
        render_state->packetCursor = (u8 *)triangle + 0x24;

        fade_wave = rsin(((s16)effect->ticks_left << 11) /
                             effect->fade_period);
        intensity = fade_wave / 16;

        wave_x2 = rsin(phase_x * 2);
        wave_x4 = rsin(phase_x * 4);
        wave_x8 = rsin(phase_x * 8);
        wave_y2 = rsin(phase_y * 2);
        wave_y4 = rsin(phase_y * 4);
        wave_y8 = rsin(phase_y * 8);
        wave_sum = wave_x2 + wave_x4 + wave_x8;
        biased_wave_y2 = wave_y2 + 0x2400;
        wave_sum += biased_wave_y2;
        wave_sum += wave_y4;
        wave_sum += wave_y8;
        wave_sum += 0x2400;

        intensity = (intensity * wave_sum) / 36864;
        intensity =
            (intensity * ((EffectStateWordView *)(effect->parameters))->unk_08) / 4096;
        intensity /= 4;

        triangle->blue1 = intensity;
        triangle->green1 = intensity;
        triangle->red1 = intensity;
        triangle->blue0 = intensity;
        triangle->green0 = intensity;
        triangle->red0 = intensity;
        triangle->blue2 = 0;
        triangle->green2 = 0;
        triangle->red2 = 0;
        SetPolyG3(triangle);
        SetSemiTrans(triangle, 1);

        triangle->x0 = center_x - effect->triangle_width / 32;
        triangle->y0 = 0;
        triangle->x1 = center_x + effect->triangle_width / 32;
        triangle->y1 = 0;
        triangle->x2 =
            center_x - (effect->triangle_width * rsin((s16)angle)) / 4096;
        (*(s16 *)((u8 *)triangle + 0x1A)) =
            (effect->triangle_width * rcos((s16)angle)) / 4096;

        render_state = (GpuContext *)(*(u8 **)&g_game_work.draw_buffer);
        draw_packet = render_state->packetCursor;
        render_state->packetCursor = draw_packet + 0xC;
        draw_page = GetTPage(0, 0, 0x140, 0);
        SetDrawMode(draw_packet, 0, 0, draw_page & 0xFFFF, 0);
        AddPrim(*(u8 **)&g_game_work.draw_buffer + 0xD8, draw_packet);

        AddPrim(*(u8 **)&g_game_work.draw_buffer + 0xD8, triangle);

        render_state = (GpuContext *)(*(u8 **)&g_game_work.draw_buffer);
        draw_packet = render_state->packetCursor;
        render_state->packetCursor = draw_packet + 0xC;
        draw_page = GetTPage(0, 1, 0x140, 0);
        SetDrawMode(draw_packet, 0, 0, draw_page & 0xFFFF, 0);
        AddPrim(*(u8 **)&g_game_work.draw_buffer + 0xD8, draw_packet);
    }
}
