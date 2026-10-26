#include "common.h"
#include "engine/scene.h"
#include "sdk/libgpu.h"

/* GsWORK-like graphics-environment block: DRAWENV-shaped header (0x00-0x5B,
 * padded to 0x5C in this build) + DISPENV-shaped header (0x5C-0x6F), followed
 * by a huge OT/primitive packet buffer (not modelled -- accessed only via raw
 * pointer offsets from the base in this function). Two full copies exist for
 * double buffering: D_801C9E40 (buffer 0) and D_801DA714 (buffer 1), exactly
 * 0x108D4 bytes apart (see initialize_hardware_and_game_state's `p + 0x108D4` toggle). */
typedef struct { s16 x, y, w, h; } EnvironmentRect;
extern EnvironmentRect lower_draw_context; /* Clip RECT prefix of the second environment buffer. */
extern s32 lower_background_flag[3];          /* buffer-1-adjacent flag; >8B decl forces hi/lo */

/* Initialise double-buffered draw/display environments for a 320x224 screen with background clearing. */
void init_double_buffered_gpu_environments(void)
{
    u8 *env_base = upper_draw_context;
    s32 origin = 0;
    s32 draw_height = 0xE0;
    s32 disp_height = 0xF0;

    SetDefDrawEnv(env_base, origin, origin, 0x140, draw_height);
    SetDefDrawEnv(&lower_draw_context, origin, draw_height, 0x140, draw_height);
    SetDefDispEnv(env_base + 0x5C, origin, draw_height, 0x140, disp_height);
    SetDefDispEnv((u8 *)&lower_draw_context + 0x5C, origin, origin, 0x140, disp_height);

    *(s16 *)(env_base + 0x1093A) = 0xC;
    *(s16 *)(env_base + 0x66) = 0xC;
    *(s16 *)(env_base + 0x1093E) = draw_height;
    *(s16 *)(env_base + 0x6A) = draw_height;

    lower_background_flag[0] = 1;
    *(s32 *)(env_base + 0x18) = 1;
}
