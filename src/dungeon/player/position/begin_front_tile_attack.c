#include "common.h"
#include "shared/entity.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/player/position.h"
#include "dungeon/system.h"
#include "dungeon/item.h"
#include "dungeon/level.h"
typedef struct Ent Ent;

typedef long long s64;
#ifndef NULL
#define NULL 0
#endif

s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
void * find_eligible_actor_at_tile_and_height();
Ent *prepare_directional_attack();

typedef struct S_8008C8BC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    union { s32 i; void * p; } unk_60;   /* accessed as both */
    u8 pad_64[0x24];
    u16 unk_88;
} S_8008C8BC_0;   /* held3 in begin_front_tile_attack */

   /* held2 in begin_front_tile_attack */

typedef struct S_8008C8BC_2 {
    u8 pad_00[0x3186];
    u8 unk_3186;
    u8 pad_3187[0x58D];
    u16 unk_3714;
} S_8008C8BC_2;   /* r4 in begin_front_tile_attack */


   /* state in begin_front_tile_attack */

/* Selects a target in the facing direction and initializes the entity action state. */
s32 begin_front_tile_attack(ActorRecord *body, void *unused, void *position_arg, void *entity_arg) {
    register S_8008C8BC_0 *entity = entity_arg;
    s32 direction;
    u8 *page_or_entity;
    ActorRecord *target;

    direction = ((u16) entity->unk_2A >> 9) & 7;
    if ((check_diagonal_side_height(direction, ((MovingTile *)position_arg)->tile_x, ((MovingTile *)position_arg)->tile_y,
        (s16) (entity->unk_88 - 0x20)) << 0x10) != 0) {
        target = find_eligible_actor_at_tile_and_height(entity, (((MovingTile *)position_arg)->tile_x
            + ((u16 *)dir_step_x)[direction]) & 0xFFFF, (((MovingTile *)position_arg)->tile_y
            + ((u16 *)dir_step_y)[direction]) & 0xFFFF, (s16) entity->unk_88);
        page_or_entity = (u8 *)0x80010000;
        entity->unk_60.p = target;
        if (!(((S_8008C8BC_2 *)page_or_entity)->unk_3714 & 1) && (target != 0)
            && (target->flags14 & 0x4000)
            && (((S_8008C8BC_2 *)page_or_entity)->unk_3186 & 1) && !(entity->unk_1C & 0x410)) {
            entity->unk_60.p = NULL;
            return 0;
        }
        page_or_entity = (u8 *)entity;
        prepare_directional_attack(page_or_entity, position_arg, (s16) entity->unk_2A, 1, 0);
    } else {
        entity->unk_60.p = NULL;
    }
    body->action_id.s = 0x11;
    body->action_phase.s = 0;
    ((PlayerRecord *)body)->actor.unk_8C.word = 0;
    g_dungeon_status.active_actor = entity;
    body->unk_A4.halves.high.s = 0;
    body->action_state_flags = (u16) ((body->action_state_flags | 0x2000) & 0xEFFF);
    g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x400);
    process_unflagged_linked_entries_alt(entity->unk_5C);
    append_packed_action_record(entity, 0x18, 0, 0);
    if (check_action_available_without_nearby_actor() != 0) {
        g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x80);
    }
    body->action_timer.s = 6;
    ((PlayerRecord *)body)->unk_102 = 0;
    return 0;
}
