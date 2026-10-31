#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "dungeon/monster/glacier.h"

extern void select_sprite_entry(void *, s32, s32);
extern u8 D_801760B4;

/* Initializes display state and selects a sprite frame from the combined facing angles. */
void initialize_item_sprite_frame(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    body->action_id.s = 0x10;
    body->action_phase.s = 0;
    sprite->scale_x = 0x1400;
    sprite->scale_y = 0xC00;
    sprite->frameTable = &D_801760B4;
    select_sprite_entry(
        sprite,
        *(&D_801760B4 + (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
        0);
}
