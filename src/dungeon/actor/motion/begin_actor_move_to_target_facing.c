#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/entity.h"
#include "dungeon/actor/motion.h"




typedef struct S_800AA888_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800AA888_4;   /* the target actor read through ActorRecord.target in begin_actor_move_to_target_facing */



extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);


/* Reset action state, update the tile, and refresh entity flags and data. */
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 tile_x;
    u8 tile_y;
    s32 update_mask;

    body->action_id = 0xB;
    body->action_phase = 0;
    body->unk_8C.handler = 0;
    tile_x = sprite->tile_x;
    tile_y = sprite->tile_y;
    update_mask = 0x3000;
    if (actor->flags1C & ACTOR_PLAYER_SIDE) {
        update_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(tile_x, tile_y, update_mask);
    body->action_state_flags = (u16)(body->action_state_flags | 8);
    actor->flags1C = (s32)(actor->flags1C & 0xFFFBFFFF);
    body->action_timer = 0;
    actor->movement_facing = (u16)((S_800AA888_4 *)actor->target)->unk_2A;
}
