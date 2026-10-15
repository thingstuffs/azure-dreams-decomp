#include "common.h"

typedef struct HudCopyRect {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} __attribute__((packed)) HudCopyRect;

extern HudCopyRect D_80089498;
extern s32 func_800673A0(const HudCopyRect *, s32, s32);

/* Copy the recorded rectangle to its fixed HUD buffer position. */
void func_800DBEE8(void)
{
    HudCopyRect rectangle = D_80089498;
    func_800673A0(&rectangle, 0x1C2, 0x19C);
}
