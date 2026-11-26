#include "shared/gpu_packets.h"
#include "dungeon/effect/sprite/render_rotated_effect_quads.h"
#include "common.h"
#include "dungeon/menu.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"

typedef struct Inner {
    u8 unk0[3];
    u8 type;
    s32 val4;
    s16 val8;
    s16 valA;
} Inner;


// Append a single-dot tile at the offset map position with the given color and submit it.
void append_map_dot_tile(s32 x, s32 y, void *color_data, void *submissionTarget)
{
    s32 *entryValue = color_data;
    s32 maskedY = y & 0xFFFF;
    s32 adjustedY = maskedY + 0xC0;
    GpuContext *state = g_game_work.draw_buffer;
    Inner *entry = state->packetCursor;
    s32 adjustedX = x + 0x300;

    state->packetCursor = entry + 1;
    entry->type = 2;
    entry->val8 = (s16)adjustedX;
    if (state != upper_draw_context) {
        adjustedY = maskedY - 0x20;
    }
    entry->valA = (s16)adjustedY;
    entry->val4 = *entryValue;
    AddPrim(submissionTarget, entry);
}
