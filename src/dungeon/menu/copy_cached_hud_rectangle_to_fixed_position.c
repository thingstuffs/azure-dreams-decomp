#include "common.h"
#include "dungeon/menu.h"
#include "sdk/libgpu.h"

extern RECT hud_vram_copy_source_rect;

/* Copy the recorded rectangle to its fixed HUD buffer position. */
void copy_cached_hud_rectangle_to_fixed_position(void)
{
    RECT rectangle = hud_vram_copy_source_rect;
    MoveImage(&rectangle, 0x1C2, 0x19C);
}
