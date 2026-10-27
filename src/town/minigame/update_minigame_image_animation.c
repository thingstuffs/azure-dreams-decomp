#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "sdk/libgpu.h"



extern u32 minigame_palette_backup[];
extern u32 D_80024660[];
extern u32 minigame_image_backup[];
extern u32 D_800246C0[];


   /* the 0x2 bytes before arg0 in update_minigame_image_animation, addressed as arg0[-1] */

typedef struct S_80023BCC_0 {
    u8 pad_00[0x5C];
    union { s16 s; u16 u; } unk_5C;   /* accessed as both */
    u16 unk_5E;
} S_80023BCC_0;   /* arg0 in update_minigame_image_animation */

/* Updates image-strip animation and sets completion flags when its timer expires. */
void update_minigame_image_animation(void *anim)
{
    s16 rect[4];
    s16 phase;
    u16 timer;

    rect[2] = 0x10;
    rect[3] = 1;

    switch (((S_80023BCC_0 *)anim)->unk_5C.s) {
    case 0:
        ((S_80023BCC_0 *)anim)->unk_5E = 0x78;
        ((S_80023BCC_0 *)anim)->unk_5C.u++;
        break;
    case 1:
        break;
    default:
        return;
    }

    rect[1] = 0x1D0;
    if ((((S_80023BCC_0 *)anim)->unk_5E >> 1) & 1) {
        u32 *image = D_80024660;

        rect[0] = 0x40;
        LoadImage(rect, image);
        rect[0] = 0x50;
        LoadImage(rect, image - 8);
    } else {
        u32 *image = minigame_palette_backup;

        rect[0] = 0x40;
        LoadImage(rect, image);
        rect[0] = 0x50;
        LoadImage(rect, image + 8);
    }

    rect[1] = 0x1F8;
    phase = (s16)((S_80023BCC_0 *)anim)->unk_5E % 3;
    switch (phase) {
    case 0:
    {
        u32 *image = D_800246C0;

        rect[0] = 0xC0;
        LoadImage(rect, image);
        rect[0] = 0xD0;
        rect[2] = 0x20;
        LoadImage(rect, image - 16);
        break;
    }
    case 1:
    {
        u32 *image = minigame_image_backup;

        rect[0] = 0xE0;
        LoadImage(rect, image);
        rect[0] = 0xC0;
        rect[2] = 0x20;
        LoadImage(rect, image + 8);
        break;
    }
    case 2:
        rect[0] = 0xC0;
        rect[2] = 0x30;
        LoadImage(rect, minigame_image_backup);
        break;
    default:
        break;
    }

    timer = ((S_80023BCC_0 *)anim)->unk_5E - 1;
    ((S_80023BCC_0 *)anim)->unk_5E = timer;
    if ((s16)timer <= 0) {
        ((ObjectStatusPrefix16 *)anim)[-1].flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
