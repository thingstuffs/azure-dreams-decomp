#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/dungeon_moving_views.h"
typedef struct Ent Ent;

typedef long long s64;
#ifndef NULL
#define NULL 0
#endif


void process_unflagged_linked_entries_alt();
s32 check_diagonal_side_height();
s32 find_eligible_actor_at_tile_and_height();
Ent *prepare_directional_attack();
void append_packed_action_record();
s32 check_action_available_without_nearby_actor();


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

typedef struct S_8008C8BC_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8008C8BC_3;

typedef struct S_8008C8BC_4 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    s16 unk_A6;
    u8 pad_A8[0x5A];
    s8 unk_102;
} S_8008C8BC_4;   /* held0 in begin_front_tile_attack */

typedef struct S_8008C8BC_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_8008C8BC_5;   /* state in begin_front_tile_attack */

/* Selects a target in the facing direction and initializes the entity action state. */
s32 begin_front_tile_attack(void *actor_state_arg, void *unused, void *position_arg, void *entity_arg) {
    register void *entity = entity_arg;
    s32 direction;
    u8 *page_or_entity;
    s32 target;

    direction = ((u16) ((S_8008C8BC_0 *)entity)->unk_2A >> 9) & 7;
    if ((check_diagonal_side_height(direction, ((MovingTile *)position_arg)->unk_24, ((MovingTile *)position_arg)->unk_25,
        (s16) (((S_8008C8BC_0 *)entity)->unk_88 - 0x20)) << 0x10) != 0) {
        target = find_eligible_actor_at_tile_and_height(entity, (((MovingTile *)position_arg)->unk_24
            + ((u16 *)dir_step_x)[direction]) & 0xFFFF, (((MovingTile *)position_arg)->unk_25
            + ((u16 *)dir_step_y)[direction]) & 0xFFFF, (s16) ((S_8008C8BC_0 *)entity)->unk_88);
        page_or_entity = (u8 *)0x80010000;
        ((S_8008C8BC_0 *)entity)->unk_60.i = target;
        if (!(((S_8008C8BC_2 *)page_or_entity)->unk_3714 & 1) && (target != 0)
            && (((S_8008C8BC_3 *)target)->unk_14 & 0x4000)
            && (((S_8008C8BC_2 *)page_or_entity)->unk_3186 & 1) && !(((S_8008C8BC_0 *)entity)->unk_1C & 0x410)) {
            ((S_8008C8BC_0 *)entity)->unk_60.p = NULL;
            return 0;
        }
        page_or_entity = (u8 *)entity;
        prepare_directional_attack(page_or_entity, position_arg, (s16) ((S_8008C8BC_0 *)entity)->unk_2A, 1, 0);
    } else {
        ((S_8008C8BC_0 *)entity)->unk_60.p = NULL;
    }
    ((S_8008C8BC_4 *)actor_state_arg)->unk_9A = 0x11;
    ((S_8008C8BC_4 *)actor_state_arg)->unk_9B = 0;
    ((S_8008C8BC_4 *)actor_state_arg)->unk_8C = 0;
    g_dungeon_status.active_actor = entity;
    ((S_8008C8BC_4 *)actor_state_arg)->unk_A6 = 0;
    ((S_8008C8BC_4 *)actor_state_arg)->unk_98 = (u16) ((((S_8008C8BC_4 *)actor_state_arg)->unk_98 | 0x2000) & 0xEFFF);
    g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x400);
    process_unflagged_linked_entries_alt(((S_8008C8BC_0 *)entity)->unk_5C);
    append_packed_action_record(entity, 0x18, 0, 0);
    if (check_action_available_without_nearby_actor() != 0) {
        g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x80);
    }
    ((S_8008C8BC_4 *)actor_state_arg)->unk_96 = 6;
    ((S_8008C8BC_4 *)actor_state_arg)->unk_102 = 0;
    return 0;
}
