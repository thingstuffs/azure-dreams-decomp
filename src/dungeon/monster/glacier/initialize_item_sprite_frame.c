#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"

extern void select_sprite_entry(void *, s32, s32);
extern u8 D_801760B4;

/* Initializes display state and selects a sprite frame from the combined facing angles. */
void initialize_item_sprite_frame(void *object, void *unused, SpriteFrameState *sprite, void *orientationSource) {
    *((s8 *)object + 0x9A) = 0x10;
    *((s8 *)object + 0x9B) = 0;
    sprite->scale_x = 0x1400;
    sprite->scale_y = 0xC00;
    sprite->frameTable = &D_801760B4;
    select_sprite_entry(
        sprite,
        *(&D_801760B4 + (((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)orientationSource + 0x2A) + 0x100) >> 9) & 7)),
        0);
}
