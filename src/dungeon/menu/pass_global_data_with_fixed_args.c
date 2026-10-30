#include "common.h"
#include "dungeon/menu.h"

typedef struct {
    u32 words[2];
} __attribute__((packed)) Copy8;

extern u8 D_80089490[9];
extern void MoveImage(void *, s32, s32);

/* Copy a fixed block of menu graphics within video memory. */
void copy_menu_vram_block(void) {
    Copy8 copy;

    copy = *(Copy8 *)D_80089490;
    MoveImage(&copy, 0x1C2, 0x19C);
}
