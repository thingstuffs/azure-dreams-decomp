#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "sdk/libgpu.h"
#include "sdk/libgpu_types.h"
#include "town/minigame.h"
#include "town/data.h"

extern u32 D_80024660[];
extern u32 D_800246C0[];


   /* the 0x2 bytes before arg0 in update_minigame_image_animation, addressed as arg0[-1] */


/* Updates image-strip animation and sets completion flags when its timer expires. */
void update_minigame_image_animation(MinigameImageAnimationObject *anim)
{
    RECT rect;
    s16 phase;
    u16 timer;

    rect.w = 0x10;
    rect.h = 1;

    switch (anim->state.s) {
    case 0:
        anim->timer = 0x78;
        anim->state.u++;
        break;
    case 1:
        break;
    default:
        return;
    }

    rect.y = 0x1D0;
    if ((anim->timer >> 1) & 1) {
        u32 *image = D_80024660;

        rect.x = 0x40;
        LoadImage(&rect, image);
        rect.x = 0x50;
        LoadImage(&rect, image - 8);
    } else {
        u32 *image = minigame_palette_backup;

        rect.x = 0x40;
        LoadImage(&rect, image);
        rect.x = 0x50;
        LoadImage(&rect, image + 8);
    }

    rect.y = 0x1F8;
    phase = (s16)anim->timer % 3;
    switch (phase) {
    case 0:
    {
        u32 *image = D_800246C0;

        rect.x = 0xC0;
        LoadImage(&rect, image);
        rect.x = 0xD0;
        rect.w = 0x20;
        LoadImage(&rect, image - 16);
        break;
    }
    case 1:
    {
        u32 *image = minigame_image_backup;

        rect.x = 0xE0;
        LoadImage(&rect, image);
        rect.x = 0xC0;
        rect.w = 0x20;
        LoadImage(&rect, image + 8);
        break;
    }
    case 2:
        rect.x = 0xC0;
        rect.w = 0x30;
        LoadImage(&rect, minigame_image_backup);
        break;
    default:
        break;
    }

    timer = anim->timer - 1;
    anim->timer = timer;
    if ((s16)timer <= 0) {
        ((ObjectStatusPrefix16 *)anim)[-1].flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
