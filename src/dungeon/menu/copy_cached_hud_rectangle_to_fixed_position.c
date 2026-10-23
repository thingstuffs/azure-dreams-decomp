#include "common.h"

typedef struct HudCopyRect {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} __attribute__((packed)) HudCopyRect;

extern HudCopyRect D_80089498;
extern s32 MoveImage(const HudCopyRect *, s32, s32);

/* Copy the recorded rectangle to its fixed HUD buffer position. */
void copy_cached_hud_rectangle_to_fixed_position(void)
{
    HudCopyRect rectangle = D_80089498;
    MoveImage(&rectangle, 0x1C2, 0x19C);
}
