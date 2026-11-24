#include "common.h"
#include "dungeon/menu.h"
#include "sdk/libgpu.h"

extern u8 D_80089490[9];

/* Copy a fixed block of menu graphics within video memory. */
void copy_menu_vram_block(void) {
    RECT copy;

    copy = *(RECT *)D_80089490;
    MoveImage(&copy, 0x1C2, 0x19C);
}
