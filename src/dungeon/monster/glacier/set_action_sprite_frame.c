#include "engine/graphics/select_sprite_entry_api.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "dungeon/monster/glacier.h"

extern u8 D_801760B4;

/* Initializes display state and selects a sprite frame from the combined facing angles. */
void set_action_sprite_frame(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    body->action_id = 0x10;
    body->action_phase = 0;
    sprite->scale_x = 0x1400;
    sprite->scale_y = 0xC00;
    sprite->frameTable = &D_801760B4;
    select_sprite_entry(
        sprite,
        *(&D_801760B4 + (((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
        0);
}
