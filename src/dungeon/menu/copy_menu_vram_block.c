#include "common.h"
#include "dungeon/menu.h"
#include "sdk/libgpu.h"

extern RECT menu_vram_copy_source_rect;

/* Copy a fixed block of menu graphics within video memory. */
void copy_menu_vram_block(void) {
    RECT copy;

    copy = menu_vram_copy_source_rect;
    MoveImage(&copy, 0x1C2, 0x19C);
}
