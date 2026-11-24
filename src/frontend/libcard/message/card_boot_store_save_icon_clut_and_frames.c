#include "frontend/card/save_image.h"
#include "common.h"
#include "frontend/libcard/message.h"
#include "sdk/libgpu.h"

extern RECT D_800200B8;
extern CardSaveIconPalette D_80027E78[];

/* Copy the selected record into the destination and process three descriptor entries. */
void card_boot_store_save_icon_clut_and_frames(CardSaveImage *save, s32 record_index)
{
    RECT descriptor;
    u32 *entry;
    s32 entry_index;

    descriptor = D_800200B8;
    save->icon_clut = D_80027E78[record_index];
    entry_index = 0;
    entry = (u32 *)(unsigned long)0x80010080;
    descriptor.y += record_index * 0x10;
    do {
        StoreImage(&descriptor, entry);
        descriptor.x += 4;
        entry += 0x20;
    } while (++entry_index < 3);
    DrawSync(0);
}
